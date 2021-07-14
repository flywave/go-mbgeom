#pragma once


#include <mapbox/feature.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/wagyu/wagyu.hpp>
#include <mapbox/geojson.hpp>
#include <mapbox/geojsonvt.hpp>
#include <mapbox/cheap_ruler.hpp>

#ifdef __cplusplus
extern "C" {
#endif

struct _mapbox_box_t {
  mapbox::geometry::box<double> box;
};

struct _mapbox_value_t {
  mapbox::feature::value val;
};

struct _mapbox_property_map_t {
  mapbox::feature::property_map prop;
};

struct _mapbox_identifier_t {
  mapbox::feature::identifier id;
};

struct _mapbox_point_t {
  mapbox::geometry::point<double> pt;
};

struct _mapbox_line_string_t {
  mapbox::geometry::line_string<double> ls;
};

struct _mapbox_linear_ring_t {
  mapbox::geometry::linear_ring<double> lr;
};

struct _mapbox_polygon_t {
  mapbox::geometry::polygon<double> poly;
};

struct _mapbox_multi_point_t {
  mapbox::geometry::multi_point<double> mp;
};

struct _mapbox_multi_line_string_t {
  mapbox::geometry::multi_line_string<double> mls;
};

struct _mapbox_multi_polygon_t {
  mapbox::geometry::multi_polygon<double> mp;
};

struct _mapbox_geometry_collection_t {
  mapbox::geometry::geometry_collection<double> gc;
};

struct _mapbox_geometry_t {
  mapbox::geometry::geometry<double> geom;
};

struct _mapbox_feature_t {
  mapbox::feature::feature<double> feat;
};

struct _mapbox_feature_collection_t {
  mapbox::feature::feature_collection<double> fc;
};

struct _mapbox_wagyu_t {
  mapbox::geometry::wagyu::wagyu<double> ctx;
};

struct _mapbox_geojson_t {
  mapbox::geojson::geojson json;
};

#ifdef __cplusplus
}
#endif
