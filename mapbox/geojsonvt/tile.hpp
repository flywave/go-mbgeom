#pragma once

#include <algorithm>
#include <cmath>
#include <mapbox/geojsonvt/types.hpp>

namespace mapbox {
namespace geojsonvt {

struct Tile {
  mapbox::feature::feature_collection<int16_t> features;
  mapbox::feature::feature_collection<double> source_features;
  uint32_t num_points = 0;
  uint32_t num_simplified = 0;
};

namespace detail {

class InternalTile {
public:
  const uint16_t extent;
  const uint8_t z;
  const uint32_t x;
  const uint32_t y;

  const double z2;
  const double tolerance;
  const double sq_tolerance;
  const bool lineMetrics;

  vt_features source_features;
  mapbox::geometry::box<double> bbox = {{2, 1}, {-1, 0}};

  Tile tile;

  InternalTile(const vt_features &source, const uint8_t z_, const uint32_t x_,
               const uint32_t y_, const uint16_t extent_,
               const double tolerance_, const bool lineMetrics_)
      : extent(extent_), z(z_), x(x_), y(y_), z2(std::pow(2, z)),
        tolerance(tolerance_), sq_tolerance(tolerance_ * tolerance_),
        lineMetrics(lineMetrics_) {

    tile.features.reserve(source.size());
    tile.source_features.reserve(source.size());
    for (const auto &feature : source) {
      const auto &geom = feature.geometry;
      assert(feature.properties);
      const auto &props = feature.properties;
      const auto &id = feature.id;

      tile.num_points += feature.num_points;

      vt_geometry::visit(geom, [&](const auto &g) {
        // `this->` is a workaround for
        // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=61636
        this->addFeature(g, *props, id);
      });

      bbox.min.x = std::min(feature.bbox.min.x, bbox.min.x);
      bbox.min.y = std::min(feature.bbox.min.y, bbox.min.y);
      bbox.max.x = std::max(feature.bbox.max.x, bbox.max.x);
      bbox.max.y = std::max(feature.bbox.max.y, bbox.max.y);
    }
  }

private:
  void addFeature(const vt_empty &empty, const property_map &props,
                  const identifier &id) {
    tile.features.emplace_back(transform(empty), props, id);
    tile.source_features.emplace_back(reproject(empty), props, id);
  }

  void addFeature(const vt_point &point, const property_map &props,
                  const identifier &id) {
    tile.features.emplace_back(transform(point), props, id);
    tile.source_features.emplace_back(reproject(point), props, id);
  }

  void addFeature(const vt_line_string &line, const property_map &props,
                  const identifier &id) {
    const auto new_line = transform(line);
    if (!new_line.empty()) {
      if (lineMetrics) {
        property_map newProps = props;
        newProps.emplace(std::make_pair<std::string, value>(
            "mapbox_clip_start", line.segStart / line.dist));
        newProps.emplace(std::make_pair<std::string, value>(
            "mapbox_clip_end", line.segEnd / line.dist));
        tile.features.emplace_back(std::move(new_line), std::move(newProps),
                                   id);
      } else
        tile.features.emplace_back(std::move(new_line), props, id);
    }
    tile.source_features.emplace_back(reproject(line), props, id);
  }

  void addFeature(const vt_polygon &polygon, const property_map &props,
                  const identifier &id) {
    const auto new_polygon = transform(polygon);
    if (!new_polygon.empty())
      tile.features.emplace_back(std::move(new_polygon), props, id);
    tile.source_features.emplace_back(reproject(polygon), props, id);
  }

  void addFeature(const vt_geometry_collection &collection,
                  const property_map &props, const identifier &id) {
    for (const auto &geom : collection) {
      vt_geometry::visit(geom, [&](const auto &g) {
        // `this->` is a workaround for
        // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=61636
        this->addFeature(g, props, id);
      });
    }
  }

  template <class T>
  void addFeature(const T &multi, const property_map &props,
                  const identifier &id) {
    const auto new_multi = transform(multi);

    switch (new_multi.size()) {
    case 0:
      break;
    case 1:
      tile.features.emplace_back(std::move(new_multi[0]), props, id);
      break;
    default:
      tile.features.emplace_back(std::move(new_multi), props, id);
      break;
    }

    tile.source_features.emplace_back(reproject(multi), props, id);
  }

  mapbox::geometry::empty reproject(const vt_empty &empty) { return empty; }

  double sinh_(double x) { return (exp(x) - exp(-x)) / 2; }

  mapbox::geometry::point<double> reproject(const vt_point &p) {
    double lon = 360 * p.x / z2 - 180;
    double lat = 180 / M_PI * atan(sinh_(M_PI * (1 - 2 * p.y / z2)));
    return {lon, lat};
  }

  mapbox::geometry::multi_point<double>
  reproject(const vt_multi_point &points) {
    mapbox::geometry::multi_point<double> result;
    result.reserve(points.size());
    for (const auto &p : points) {
      result.emplace_back(reproject(p));
    }
    return result;
  }

  mapbox::geometry::line_string<double> reproject(const vt_line_string &line) {
    mapbox::geometry::line_string<double> result;
    if (line.dist > tolerance) {
      result.reserve(line.size());
      for (const auto &p : line) {
        result.emplace_back(reproject(p));
      }
    }
    return result;
  }

  mapbox::geometry::linear_ring<double> reproject(const vt_linear_ring &ring) {
    mapbox::geometry::linear_ring<double> result;
    if (ring.area > sq_tolerance) {
      result.reserve(ring.size());
      for (const auto &p : ring) {
        result.emplace_back(reproject(p));
      }
    }
    return result;
  }

  mapbox::geometry::multi_line_string<double>
  reproject(const vt_multi_line_string &lines) {
    mapbox::geometry::multi_line_string<double> result;
    result.reserve(lines.size());
    for (const auto &line : lines) {
      result.emplace_back(reproject(line));
    }
    return result;
  }

  mapbox::geometry::polygon<double> reproject(const vt_polygon &rings) {
    mapbox::geometry::polygon<double> result;
    result.reserve(rings.size());
    for (const auto &ring : rings) {
      result.emplace_back(reproject(ring));
    }
    return result;
  }

  mapbox::geometry::multi_polygon<double>
  reproject(const vt_multi_polygon &polygons) {
    mapbox::geometry::multi_polygon<double> result;
    result.reserve(polygons.size());
    for (const auto &polygon : polygons) {
      const auto p = reproject(polygon);
      if (!p.empty())
        result.emplace_back(std::move(p));
    }
    return result;
  }

  mapbox::geometry::empty transform(const vt_empty &empty) { return empty; }

  mapbox::geometry::point<int16_t> transform(const vt_point &p) {
    ++tile.num_simplified;
    return {static_cast<int16_t>(::round((p.x * z2 - x) * extent)),
            static_cast<int16_t>(::round((p.y * z2 - y) * extent))};
  }

  mapbox::geometry::multi_point<int16_t>
  transform(const vt_multi_point &points) {
    mapbox::geometry::multi_point<int16_t> result;
    result.reserve(points.size());
    for (const auto &p : points) {
      result.emplace_back(transform(p));
    }
    return result;
  }

  mapbox::geometry::line_string<int16_t> transform(const vt_line_string &line) {
    mapbox::geometry::line_string<int16_t> result;
    if (line.dist > tolerance) {
      result.reserve(line.size());
      for (const auto &p : line) {
        if (p.z > sq_tolerance)
          result.emplace_back(transform(p));
      }
    }
    return result;
  }

  mapbox::geometry::linear_ring<int16_t> transform(const vt_linear_ring &ring) {
    mapbox::geometry::linear_ring<int16_t> result;
    if (ring.area > sq_tolerance) {
      result.reserve(ring.size());
      for (const auto &p : ring) {
        if (p.z > sq_tolerance)
          result.emplace_back(transform(p));
      }
    }
    return result;
  }

  mapbox::geometry::multi_line_string<int16_t>
  transform(const vt_multi_line_string &lines) {
    mapbox::geometry::multi_line_string<int16_t> result;
    result.reserve(lines.size());
    for (const auto &line : lines) {
      if (line.dist > tolerance)
        result.emplace_back(transform(line));
    }
    return result;
  }

  mapbox::geometry::polygon<int16_t> transform(const vt_polygon &rings) {
    mapbox::geometry::polygon<int16_t> result;
    result.reserve(rings.size());
    for (const auto &ring : rings) {
      if (ring.area > sq_tolerance)
        result.emplace_back(transform(ring));
    }
    return result;
  }

  mapbox::geometry::multi_polygon<int16_t>
  transform(const vt_multi_polygon &polygons) {
    mapbox::geometry::multi_polygon<int16_t> result;
    result.reserve(polygons.size());
    for (const auto &polygon : polygons) {
      const auto p = transform(polygon);
      if (!p.empty())
        result.emplace_back(std::move(p));
    }
    return result;
  }
};

} // namespace detail
} // namespace geojsonvt
} // namespace mapbox
