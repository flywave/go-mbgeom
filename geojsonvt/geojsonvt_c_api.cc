#include "geojsonvt_c_api.h"
#include "geom_c_api_impl.hh"

#include <string.h>

#include <mapbox/cheap_ruler.hpp>
#include <mapbox/feature.hpp>
#include <mapbox/geojson.hpp>
#include <mapbox/geojsonvt.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/wagyu/wagyu.hpp>

#ifdef __cplusplus
extern "C" {
#endif

struct _geojsonvt_box_t {
  mapbox::geometry::box<int16_t> box;
};

struct _geojsonvt_value_t {
  mapbox::feature::value val;
};

struct _geojsonvt_property_map_t {
  mapbox::feature::property_map prop;
};

struct _geojsonvt_identifier_t {
  mapbox::feature::identifier id;
};

struct _geojsonvt_point_t {
  mapbox::geometry::point<int16_t> pt;
};

struct _geojsonvt_line_string_t {
  mapbox::geometry::line_string<int16_t> ls;
};

struct _geojsonvt_linear_ring_t {
  mapbox::geometry::linear_ring<int16_t> lr;
};

struct _geojsonvt_polygon_t {
  mapbox::geometry::polygon<int16_t> poly;
};

struct _geojsonvt_multi_point_t {
  mapbox::geometry::multi_point<int16_t> mp;
};

struct _geojsonvt_multi_line_string_t {
  mapbox::geometry::multi_line_string<int16_t> mls;
};

struct _geojsonvt_multi_polygon_t {
  mapbox::geometry::multi_polygon<int16_t> mp;
};

struct _geojsonvt_geometry_collection_t {
  mapbox::geometry::geometry_collection<int16_t> gc;
};

struct _geojsonvt_geometry_t {
  mapbox::geometry::geometry<int16_t> geom;
};

struct _geojsonvt_feature_t {
  mapbox::feature::feature<int16_t> feat;
};

struct _geojsonvt_feature_collection_t {
  mapbox::feature::feature_collection<int16_t> fc;
};

struct _geojsonvt_wagyu_t {
  mapbox::geometry::wagyu::wagyu<int16_t> ctx;
};

struct _geojsonvt_geojson_t {
  mapbox::geojson::geojson json;
};

struct _geojsonvt_tile_t {
  mapbox::geojsonvt::Tile t;
};

struct _geojsonvt_t {
  mapbox::geojsonvt::GeoJSONVT vt;
};

geojsonvt_box_t *geojsonvt_box_new(geojsonvt_point_t *min,
                                   geojsonvt_point_t *max) {
  return new geojsonvt_box_t{mapbox::geometry::box<int16_t>{min->pt, max->pt}};
}

void geojsonvt_box_free(geojsonvt_box_t *box) { delete box; }

geojsonvt_point_t *geojsonvt_box_get_min(geojsonvt_box_t *box) {
  return new geojsonvt_point_t{box->box.min};
}

geojsonvt_point_t *geojsonvt_box_get_max(geojsonvt_box_t *box) {
  return new geojsonvt_point_t{box->box.max};
}

geojsonvt_box_t *geojsonvt_box_envelope(geojsonvt_geometry_t *geom) {
  return new geojsonvt_box_t{mapbox::geometry::envelope(geom->geom)};
}

geojsonvt_point_t *geojsonvt_point_new(int16_t x, int16_t y) {
  return new geojsonvt_point_t{mapbox::geometry::point<int16_t>{x, y}};
}

void geojsonvt_point_free(geojsonvt_point_t *pt) { delete pt; }

int16_t geojsonvt_point_get_x(geojsonvt_point_t *pt) { return pt->pt.x; }

int16_t geojsonvt_point_get_y(geojsonvt_point_t *pt) { return pt->pt.y; }

void geojsonvt_point_get_xy(geojsonvt_point_t *pt, int16_t *x, int16_t *y) {
  *x = pt->pt.x;
  *y = pt->pt.y;
}

void geojsonvt_point_set_xy(geojsonvt_point_t *pt, int16_t x, int16_t y) {
  pt->pt.x = x;
  pt->pt.y = y;
}

geojsonvt_geometry_t *geojsonvt_point_to_geometry(geojsonvt_point_t *pt) {
  return new geojsonvt_geometry_t{mapbox::geometry::geometry<int16_t>{pt->pt}};
}

bool geojsonvt_point_equal(geojsonvt_point_t *geom1, geojsonvt_point_t *geom2) {
  return geom1->pt == geom2->pt;
}

geojsonvt_line_string_t *geojsonvt_line_string_new(int16_t *xy,
                                                   int pointcount) {
  mapbox::geometry::line_string<int16_t> ls;
  ls.reserve(pointcount);
  for (int i = 0; i < pointcount; i++) {
    ls.emplace_back(mapbox::geometry::point<int16_t>{xy[i * 2], xy[i * 2 + 1]});
  }
  return new geojsonvt_line_string_t{std::move(ls)};
}

void geojsonvt_line_string_free(geojsonvt_line_string_t *ls) { delete ls; }

int geojsonvt_line_string_get_points_count(geojsonvt_line_string_t *ls) {
  return ls->ls.size();
}

void geojsonvt_line_string_update_point(geojsonvt_line_string_t *pt, int i,
                                        int16_t x, int16_t y) {
  if (i < pt->ls.size()) {
    pt->ls[i].x = x;
    pt->ls[i].y = y;
  }
}

geojsonvt_point_t *geojsonvt_line_string_get_point(geojsonvt_line_string_t *pt,
                                                   int i) {
  auto p = pt->ls[i];
  return new geojsonvt_point_t{mapbox::geometry::point<int16_t>{p.x, p.y}};
}

void geojsonvt_line_string_append_point(geojsonvt_line_string_t *pt, int16_t x,
                                        int16_t y) {
  pt->ls.emplace_back(mapbox::geometry::point<int16_t>{x, y});
}

void geojsonvt_line_string_get_point_xy(geojsonvt_line_string_t *pt, int i,
                                        int16_t *x, int16_t *y) {
  auto p = pt->ls[i];
  *x = p.x;
  *y = p.y;
}

geojsonvt_geometry_t *
geojsonvt_line_string_to_geometry(geojsonvt_line_string_t *pt) {
  return new geojsonvt_geometry_t{mapbox::geometry::geometry<int16_t>{pt->ls}};
}

bool geojsonvt_line_string_equal(geojsonvt_line_string_t *geom1,
                                 geojsonvt_line_string_t *geom2) {
  return geom1->ls == geom2->ls;
}

geojsonvt_multi_point_t *geojsonvt_multi_point_new(int16_t *xy,
                                                   int pointcount) {
  mapbox::geometry::multi_point<int16_t> ls;
  ls.reserve(pointcount);
  for (int i = 0; i < pointcount; i++) {
    ls.emplace_back(mapbox::geometry::point<int16_t>{xy[i * 2], xy[i * 2 + 1]});
  }
  return new geojsonvt_multi_point_t{std::move(ls)};
}

void geojsonvt_multi_point_free(geojsonvt_multi_point_t *ls) { delete ls; }

int geojsonvt_multi_point_get_points_count(geojsonvt_multi_point_t *ls) {
  return ls->mp.size();
}

geojsonvt_point_t *geojsonvt_multi_point_get_point(geojsonvt_multi_point_t *pt,
                                                   int i) {
  auto p = pt->mp[i];
  return new geojsonvt_point_t{mapbox::geometry::point<int16_t>{p.x, p.y}};
}

geojsonvt_geometry_t *
geojsonvt_multi_point_to_geometry(geojsonvt_multi_point_t *pt) {
  return new geojsonvt_geometry_t{mapbox::geometry::geometry<int16_t>{pt->mp}};
}

void geojsonvt_multi_point_update_point(geojsonvt_multi_point_t *pt, int i,
                                        int16_t x, int16_t y) {
  if (i < pt->mp.size()) {
    pt->mp[i].x = x;
    pt->mp[i].y = y;
  }
}

void geojsonvt_multi_point_append_point(geojsonvt_multi_point_t *pt, int16_t x,
                                        int16_t y) {
  pt->mp.emplace_back(mapbox::geometry::point<int16_t>{x, y});
}

bool geojsonvt_multi_point_equal(geojsonvt_multi_point_t *geom1,
                                 geojsonvt_multi_point_t *geom2) {
  return geom1->mp == geom2->mp;
}

void geojsonvt_multi_point_get_point_xy(geojsonvt_multi_point_t *pt, int i,
                                        int16_t *x, int16_t *y) {
  auto p = pt->mp[i];
  *x = p.x;
  *y = p.y;
}

geojsonvt_linear_ring_t *geojsonvt_linear_ring_new(int16_t *xy,
                                                   int pointcount) {
  mapbox::geometry::linear_ring<int16_t> ls;
  ls.reserve(pointcount);
  for (int i = 0; i < pointcount; i++) {
    ls.emplace_back(mapbox::geometry::point<int16_t>{xy[i * 2], xy[i * 2 + 1]});
  }
  return new geojsonvt_linear_ring_t{std::move(ls)};
}

void geojsonvt_linear_ring_free(geojsonvt_linear_ring_t *ls) { delete ls; }

int geojsonvt_linear_ring_get_points_count(geojsonvt_linear_ring_t *ls) {
  return ls->lr.size();
}

void geojsonvt_linear_ring_update_point(geojsonvt_linear_ring_t *pt, int i,
                                        int16_t x, int16_t y) {
  if (i < pt->lr.size()) {
    pt->lr[i].x = x;
    pt->lr[i].y = y;
  }
}

geojsonvt_point_t *geojsonvt_linear_ring_get_point(geojsonvt_linear_ring_t *pt,
                                                   int i) {
  auto p = pt->lr[i];
  return new geojsonvt_point_t{mapbox::geometry::point<int16_t>{p.x, p.y}};
}

void geojsonvt_linear_ring_get_point_xy(geojsonvt_linear_ring_t *pt, int i,
                                        int16_t *x, int16_t *y) {
  auto p = pt->lr[i];
  *x = p.x;
  *y = p.y;
}

void geojsonvt_linear_ring_append_point(geojsonvt_linear_ring_t *pt, int16_t x,
                                        int16_t y) {
  pt->lr.emplace_back(mapbox::geometry::point<int16_t>{x, y});
}

bool geojsonvt_linear_ring_equal(geojsonvt_linear_ring_t *geom1,
                                 geojsonvt_linear_ring_t *geom2) {
  return geom1->lr == geom2->lr;
}

geojsonvt_polygon_t *geojsonvt_polygon_new(geojsonvt_linear_ring_t **rings,
                                           int ringcount) {
  mapbox::geometry::polygon<int16_t> polys;
  polys.reserve(ringcount);
  for (int i = 0; i < ringcount; i++) {
    polys.emplace_back(rings[i]->lr);
  }
  return new geojsonvt_polygon_t{polys};
}

void geojsonvt_polygon_free(geojsonvt_polygon_t *pt) { delete pt; }

geojsonvt_geometry_t *geojsonvt_polygon_to_geometry(geojsonvt_polygon_t *pt) {
  return new geojsonvt_geometry_t{
      mapbox::geometry::geometry<int16_t>{pt->poly}};
}

void geojsonvt_polygon_set_exterior(geojsonvt_polygon_t *pt,
                                    geojsonvt_linear_ring_t *ring) {
  if (!pt->poly.empty()) {
    pt->poly[0] = ring->lr;
  } else {
    pt->poly.emplace_back(ring->lr);
  }
}

geojsonvt_linear_ring_t *
geojsonvt_polygon_get_exterior(geojsonvt_polygon_t *pt) {
  if (!pt->poly.empty()) {
    return new geojsonvt_linear_ring_t{pt->poly[0]};
  }
  return nullptr;
}

int geojsonvt_polygon_get_interior_count(geojsonvt_polygon_t *pt) {
  return pt->poly.size() - 1;
}

geojsonvt_linear_ring_t *geojsonvt_polygon_get_interior(geojsonvt_polygon_t *pt,
                                                        int i) {
  if (pt->poly.size() > 1) {
    return new geojsonvt_linear_ring_t{pt->poly[i + 1]};
  }
  return nullptr;
}

void geojsonvt_polygon_update_interior_ring(geojsonvt_polygon_t *pt, int i,
                                            geojsonvt_linear_ring_t *ring) {
  if (i < pt->poly.size() - 1) {
    pt->poly[i + 1] = ring->lr;
  }
}

void geojsonvt_polygon_append_interior_ring(geojsonvt_polygon_t *pt,
                                            geojsonvt_linear_ring_t *ring) {
  pt->poly.emplace_back(ring->lr);
}

bool geojsonvt_polygon_equal(geojsonvt_polygon_t *geom1,
                             geojsonvt_polygon_t *geom2) {
  return geom1->poly == geom2->poly;
}

geojsonvt_multi_line_string_t *
geojsonvt_multi_line_string_new(geojsonvt_line_string_t **lines,
                                int ringcount) {
  mapbox::geometry::multi_line_string<int16_t> mls;
  mls.reserve(ringcount);
  for (int i = 0; i < ringcount; i++) {
    mls.emplace_back(lines[i]->ls);
  }
  return new geojsonvt_multi_line_string_t{mls};
}

void geojsonvt_multi_line_string_free(geojsonvt_multi_line_string_t *pt) {
  delete pt;
}

void geojsonvt_multi_line_string_append(geojsonvt_multi_line_string_t *pt,
                                        geojsonvt_line_string_t *line) {
  pt->mls.emplace_back(line->ls);
}

void geojsonvt_multi_line_string_update(geojsonvt_multi_line_string_t *pt,
                                        int i, geojsonvt_line_string_t *line) {
  if (i < pt->mls.size()) {
    pt->mls[i] = line->ls;
  }
}

int geojsonvt_multi_line_get_count(geojsonvt_multi_line_string_t *pt) {
  return pt->mls.size();
}

geojsonvt_line_string_t *
geojsonvt_multi_line_string_get(geojsonvt_multi_line_string_t *pt, int i) {
  return new geojsonvt_line_string_t{pt->mls[i]};
}

geojsonvt_geometry_t *
geojsonvt_multi_line_string_to_geometry(geojsonvt_multi_line_string_t *pt) {
  return new geojsonvt_geometry_t{mapbox::geometry::geometry<int16_t>{pt->mls}};
}

bool geojsonvt_multi_line_string_equal(geojsonvt_multi_line_string_t *geom1,
                                       geojsonvt_multi_line_string_t *geom2) {
  return geom1->mls == geom2->mls;
}

geojsonvt_multi_polygon_t *
geojsonvt_multi_polygon_new(geojsonvt_polygon_t **polys, int polycount) {
  mapbox::geometry::multi_polygon<int16_t> mls;
  mls.reserve(polycount);
  for (int i = 0; i < polycount; i++) {
    mls.emplace_back(polys[i]->poly);
  }
  return new geojsonvt_multi_polygon_t{mls};
}

void geojsonvt_multi_polygon_free(geojsonvt_multi_polygon_t *pt) { delete pt; }

void geojsonvt_multi_polygon_append(geojsonvt_multi_polygon_t *pt,
                                    geojsonvt_polygon_t *poly) {
  pt->mp.emplace_back(poly->poly);
}

void geojsonvt_multi_polygon_update(geojsonvt_multi_polygon_t *pt, int i,
                                    geojsonvt_polygon_t *line) {
  if (i < pt->mp.size()) {
    pt->mp[i] = line->poly;
  }
}

int geojsonvt_multi_polygon_get_count(geojsonvt_multi_polygon_t *pt) {
  return pt->mp.size();
}

geojsonvt_polygon_t *geojsonvt_multi_polygon_get(geojsonvt_multi_polygon_t *pt,
                                                 int i) {
  return new geojsonvt_polygon_t{pt->mp[i]};
}

geojsonvt_geometry_t *
geojsonvt_multi_polygon_to_geometry(geojsonvt_multi_polygon_t *pt) {
  return new geojsonvt_geometry_t{mapbox::geometry::geometry<int16_t>{pt->mp}};
}

bool geojsonvt_multi_polygon_equal(geojsonvt_multi_polygon_t *geom1,
                                   geojsonvt_multi_polygon_t *geom2) {
  return geom1->mp == geom2->mp;
}

void geojsonvt_geometry_free(geojsonvt_geometry_t *geom) { delete geom; }

_Bool geojsonvt_geometry_empty(geojsonvt_geometry_t *geom) {
  return geom->geom.valid();
}

_Bool geojsonvt_geometry_is_point(geojsonvt_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::point<int16_t>>();
}

_Bool geojsonvt_geometry_is_line_string(geojsonvt_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::line_string<int16_t>>();
}

_Bool geojsonvt_geometry_is_polygon(geojsonvt_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::polygon<int16_t>>();
}

_Bool geojsonvt_geometry_is_multi_point(geojsonvt_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::multi_point<int16_t>>();
}

_Bool geojsonvt_geometry_is_multi_line_string(geojsonvt_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::multi_line_string<int16_t>>();
}

_Bool geojsonvt_geometry_is_multi_polygon(geojsonvt_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::multi_polygon<int16_t>>();
}

geojsonvt_point_t *geojsonvt_geometry_cast_point(geojsonvt_geometry_t *geom) {
  if (geojsonvt_geometry_is_point(geom)) {
    return new geojsonvt_point_t{
        geom->geom.get<mapbox::geometry::point<int16_t>>()};
  }
  return nullptr;
}

geojsonvt_line_string_t *
geojsonvt_geometry_cast_line_string(geojsonvt_geometry_t *geom) {
  if (geojsonvt_geometry_is_line_string(geom)) {
    return new geojsonvt_line_string_t{
        geom->geom.get<mapbox::geometry::line_string<int16_t>>()};
  }
  return nullptr;
}

geojsonvt_polygon_t *
geojsonvt_geometry_cast_polygon(geojsonvt_geometry_t *geom) {
  if (geojsonvt_geometry_is_polygon(geom)) {
    return new geojsonvt_polygon_t{
        geom->geom.get<mapbox::geometry::polygon<int16_t>>()};
  }
  return nullptr;
}

geojsonvt_multi_point_t *
geojsonvt_geometry_cast_multi_point(geojsonvt_geometry_t *geom) {
  if (geojsonvt_geometry_is_multi_point(geom)) {
    return new geojsonvt_multi_point_t{
        geom->geom.get<mapbox::geometry::multi_point<int16_t>>()};
  }
  return nullptr;
}

geojsonvt_multi_line_string_t *
geojsonvt_geometry_cast_multi_line_string(geojsonvt_geometry_t *geom) {
  if (geojsonvt_geometry_is_multi_line_string(geom)) {
    return new geojsonvt_multi_line_string_t{
        geom->geom.get<mapbox::geometry::multi_line_string<int16_t>>()};
  }
  return nullptr;
}

geojsonvt_multi_polygon_t *
geojsonvt_geometry_cast_multi_polygon(geojsonvt_geometry_t *geom) {
  if (geojsonvt_geometry_is_multi_polygon(geom)) {
    return new geojsonvt_multi_polygon_t{
        geom->geom.get<mapbox::geometry::multi_polygon<int16_t>>()};
  }
  return nullptr;
}

bool geojsonvt_geometry_equal(geojsonvt_geometry_t *geom1,
                              geojsonvt_geometry_t *geom2) {
  return geom1->geom == geom2->geom;
}

geojsonvt_geometry_collection_t *geojsonvt_geometry_collection_new() {
  return new geojsonvt_geometry_collection_t{};
}

void geojsonvt_geometry_collection_free(geojsonvt_geometry_collection_t *geom) {
  delete geom;
}

_Bool geojsonvt_geometry_collection_empty(geojsonvt_geometry_collection_t *gc) {
  return gc->gc.empty();
}

void geojsonvt_geometry_collection_append(geojsonvt_geometry_collection_t *gc,
                                          geojsonvt_geometry_t *geom) {
  gc->gc.emplace_back(geom->geom);
}

void geojsonvt_geometry_collection_update(geojsonvt_geometry_collection_t *gc,
                                          int i, geojsonvt_geometry_t *geom) {
  if (i < gc->gc.size()) {
    gc->gc[i] = geom->geom;
  }
}

int geojsonvt_geometry_collection_get_count(
    geojsonvt_geometry_collection_t *gc) {
  return gc->gc.size();
}

geojsonvt_geometry_t *
geojsonvt_geometry_collection_get(geojsonvt_geometry_collection_t *gc, int i) {
  if (i < gc->gc.size()) {
    return new geojsonvt_geometry_t{gc->gc[i]};
  }
  return nullptr;
}

geojsonvt_value_t *geojsonvt_value_new() {
  return new geojsonvt_value_t{
      mapbox::feature::value{mapbox::feature::null_value}};
}

void geojsonvt_value_free(geojsonvt_value_t *val) { delete val; }

geojsonvt_value_t *geojsonvt_value_from_bool(_Bool v) {
  return new geojsonvt_value_t{mapbox::feature::value{v}};
}

geojsonvt_value_t *geojsonvt_value_from_uint(uint64_t v) {
  return new geojsonvt_value_t{mapbox::feature::value{v}};
}

geojsonvt_value_t *geojsonvt_value_from_int(int64_t v) {
  return new geojsonvt_value_t{mapbox::feature::value{v}};
}

geojsonvt_value_t *geojsonvt_value_from_double(double v) {
  return new geojsonvt_value_t{mapbox::feature::value{v}};
}

geojsonvt_value_t *geojsonvt_value_from_string(const char *v) {
  return new geojsonvt_value_t{mapbox::feature::value{std::string(v)}};
}

geojsonvt_value_t *geojsonvt_value_from_values(geojsonvt_value_t **vs,
                                               int valuecount) {
  std::vector<mapbox::feature::value> v;
  v.reserve(valuecount);
  for (int i = 0; i < valuecount; i++) {
    v.emplace_back(vs[i]->val);
  }
  return new geojsonvt_value_t{mapbox::feature::value{v}};
}

geojsonvt_value_t *geojsonvt_value_from_keyvalues(const char **ks,
                                                  geojsonvt_value_t **vs,
                                                  int valuecount) {
  std::unordered_map<std::string, mapbox::feature::value> v;
  for (int i = 0; i < valuecount; i++) {
    v.emplace(ks[i], vs[i]->val);
  }
  return new geojsonvt_value_t{mapbox::feature::value{v}};
}

_Bool geojsonvt_value_is_empty(geojsonvt_value_t *geom) {
  return !geom->val.valid();
}

_Bool geojsonvt_value_is_null(geojsonvt_value_t *geom) {
  return geom->val.is<mapbox::feature::null_value_t>();
}

_Bool geojsonvt_value_is_bool(geojsonvt_value_t *geom) {
  return geom->val.is<bool>();
}

_Bool geojsonvt_value_is_uint(geojsonvt_value_t *geom) {
  return geom->val.is<uint64_t>();
}

_Bool geojsonvt_value_is_int(geojsonvt_value_t *geom) {
  return geom->val.is<int64_t>();
}

_Bool geojsonvt_value_is_double(geojsonvt_value_t *geom) {
  return geom->val.is<double>();
}

_Bool geojsonvt_value_is_string(geojsonvt_value_t *geom) {
  return geom->val.is<std::string>();
}

_Bool geojsonvt_value_is_vector(geojsonvt_value_t *geom) {
  return geom->val.is<std::shared_ptr<std::vector<mapbox::feature::value>>>();
}

_Bool geojsonvt_value_is_map(geojsonvt_value_t *geom) {
  return geom->val.is<std::shared_ptr<
      std::unordered_map<std::string, mapbox::feature::value>>>();
}

_Bool geojsonvt_value_cast_bool(geojsonvt_value_t *geom) {
  return geom->val.get<bool>();
}

uint64_t geojsonvt_value_cast_uint(geojsonvt_value_t *geom) {
  return geom->val.get<uint64_t>();
}

int64_t geojsonvt_value_cast_int(geojsonvt_value_t *geom) {
  return geom->val.get<int64_t>();
}

double geojsonvt_value_cast_double(geojsonvt_value_t *geom) {
  return geom->val.get<double>();
}

char *geojsonvt_value_cast_string(geojsonvt_value_t *geom) {
  auto str = geom->val.get<std::string>();
  return strdup(str.c_str());
}

geojsonvt_value_t **geojsonvt_value_cast_vector(geojsonvt_value_t *geom,
                                                int *count) {
  auto wvec =
      geom->val.get<std::shared_ptr<std::vector<mapbox::feature::value>>>();
  auto &vec = *wvec;
  geojsonvt_value_t **ret = new geojsonvt_value_t *[vec.size()];
  *count = vec.size();
  for (int i = 0; i < vec.size(); i++) {
    ret[i] = new geojsonvt_value_t{vec[i]};
  }
  return ret;
}

void geojsonvt_values_free(geojsonvt_value_t **vs) { delete[] vs; }

geojsonvt_property_map_t *geojsonvt_value_cast_map(geojsonvt_value_t *geom) {
  auto wmap = geom->val.get<std::shared_ptr<
      std::unordered_map<std::string, mapbox::feature::value>>>();
  return new geojsonvt_property_map_t{*wmap};
}

geojsonvt_property_map_t *geojsonvt_property_map_new() {
  return new geojsonvt_property_map_t{};
}

void geojsonvt_property_map_free(geojsonvt_property_map_t *val) { delete val; }

geojsonvt_value_t *geojsonvt_property_map_get(geojsonvt_property_map_t *val,
                                              const char *key) {
  if (geojsonvt_property_map_has(val, key)) {
    return new geojsonvt_value_t{val->prop[key]};
  }
  return geojsonvt_value_new();
}

void geojsonvt_property_map_set(geojsonvt_property_map_t *val, const char *key,
                                geojsonvt_value_t *v) {
  val->prop[key] = v->val;
}

_Bool geojsonvt_property_map_has(geojsonvt_property_map_t *val,
                                 const char *key) {
  if (val->prop.find(key) == val->prop.end()) {
    return false;
  }
  return true;
}

_Bool geojsonvt_property_map_empty(geojsonvt_property_map_t *val) {
  return val->prop.empty();
}

char **geojsonvt_property_map_keys(geojsonvt_property_map_t *val, int *count) {
  *count = val->prop.size();
  char **keys = new char *[*count];
  int i = 0;
  for (auto rp : val->prop) {
    keys[i] = strdup(rp.first.c_str());
  }
  return keys;
}

void geojsonvt_property_map_free_keys(char **keys, int count) {
  for (int i = 0; i < count; i++) {
    free(keys[i]);
  }
  delete[] keys;
}

int geojsonvt_property_map_count(geojsonvt_property_map_t *val) {
  return val->prop.size();
}

geojsonvt_identifier_t *geojsonvt_identifier_from_uint(uint64_t v) {
  return new geojsonvt_identifier_t{v};
}

geojsonvt_identifier_t *geojsonvt_identifier_from_int(int64_t v) {
  return new geojsonvt_identifier_t{v};
}

geojsonvt_identifier_t *geojsonvt_identifier_from_double(double v) {
  return new geojsonvt_identifier_t{v};
}

geojsonvt_identifier_t *geojsonvt_identifier_from_string(const char *v) {
  return new geojsonvt_identifier_t{std::string(v)};
}

void geojsonvt_identifier_free(geojsonvt_identifier_t *val) { delete val; }

_Bool geojsonvt_identifier_is_uint(geojsonvt_identifier_t *geom) {
  return geom->id.is<uint64_t>();
}

_Bool geojsonvt_identifier_is_int(geojsonvt_identifier_t *geom) {
  return geom->id.is<int64_t>();
}

_Bool geojsonvt_identifier_is_double(geojsonvt_identifier_t *geom) {
  return geom->id.is<double>();
}

_Bool geojsonvt_identifier_is_string(geojsonvt_identifier_t *geom) {
  return geom->id.is<std::string>();
}

uint64_t geojsonvt_identifier_cast_uint(geojsonvt_identifier_t *geom) {
  return geom->id.get<uint64_t>();
}

int64_t geojsonvt_identifier_cast_int(geojsonvt_identifier_t *geom) {
  return geom->id.get<int64_t>();
}

double geojsonvt_identifier_cast_double(geojsonvt_identifier_t *geom) {
  return geom->id.get<double>();
}

char *geojsonvt_identifier_cast_string(geojsonvt_identifier_t *geom) {
  auto str = geom->id.get<std::string>();
  return strdup(str.c_str());
}

geojsonvt_feature_t *geojsonvt_feature_new(geojsonvt_geometry_t *geom) {
  return new geojsonvt_feature_t{mapbox::feature::feature<int16_t>{geom->geom}};
}

geojsonvt_feature_t *geojsonvt_feature_create(geojsonvt_identifier_t *id,
                                              geojsonvt_geometry_t *geom,
                                              geojsonvt_property_map_t *props) {
  return new geojsonvt_feature_t{
      mapbox::feature::feature<int16_t>{geom->geom, props->prop, id->id}};
}

void geojsonvt_feature_free(geojsonvt_feature_t *feat) { delete feat; }

void geojsonvt_feature_set_identifier(geojsonvt_feature_t *feat,
                                      geojsonvt_identifier_t *id) {
  feat->feat.id = id->id;
}

void geojsonvt_feature_set_geometry(geojsonvt_feature_t *feat,
                                    geojsonvt_geometry_t *geom) {
  feat->feat.geometry = geom->geom;
}

void geojsonvt_feature_set_property_map(geojsonvt_feature_t *feat,
                                        geojsonvt_property_map_t *props) {
  feat->feat.properties = props->prop;
}

geojsonvt_identifier_t *
geojsonvt_feature_get_identifier(geojsonvt_feature_t *feat) {
  if (feat->feat.id.valid()) {
    return new geojsonvt_identifier_t{feat->feat.id};
  }
  return nullptr;
}

geojsonvt_geometry_t *
geojsonvt_feature_get_geometry(geojsonvt_feature_t *feat) {
  return new geojsonvt_geometry_t{feat->feat.geometry};
}

geojsonvt_property_map_t *
geojsonvt_feature_get_property_map(geojsonvt_feature_t *feat) {
  return new geojsonvt_property_map_t{feat->feat.properties};
}

bool geojsonvt_feature_equal(geojsonvt_feature_t *feat1,
                             geojsonvt_feature_t *feat2) {
  return feat1->feat == feat2->feat;
}

geojsonvt_feature_collection_t *geojsonvt_feature_collection_new() {
  return new geojsonvt_feature_collection_t{};
}

void geojsonvt_feature_collection_free(geojsonvt_feature_collection_t *geom) {
  delete geom;
}

_Bool geojsonvt_feature_collection_empty(geojsonvt_feature_collection_t *gc) {
  return gc->fc.empty();
}

void geojsonvt_feature_collection_append(geojsonvt_feature_collection_t *gc,
                                         geojsonvt_feature_t *feat) {
  gc->fc.emplace_back(feat->feat);
}

void geojsonvt_feature_collection_update(geojsonvt_feature_collection_t *gc,
                                         int i, geojsonvt_feature_t *feat) {
  if (i < gc->fc.size()) {
    gc->fc[i] = feat->feat;
  }
}

int geojsonvt_feature_collection_get_count(geojsonvt_feature_collection_t *gc) {
  return gc->fc.size();
}

geojsonvt_feature_t *
geojsonvt_feature_collection_get(geojsonvt_feature_collection_t *gc, int i) {
  if (i < gc->fc.size()) {
    return new geojsonvt_feature_t{gc->fc[i]};
  }
  return nullptr;
}

void geojsonvt_tile_free(geojsonvt_tile_t *t) { delete t; }

geojsonvt_feature_collection_t *
geojsonvt_tile_get_feature_collection(geojsonvt_tile_t *t) {
  return new geojsonvt_feature_collection_t{t->t.features};
}

geojsonvt_t *geojsonvt_new(void *geom, struct _geojsonvt_tile_options_t opts) {
  mapbox::geojsonvt::Options opt;
  {
    opt.tolerance = opts.tolerance;
    opt.extent = opts.extent;
    opt.buffer = opts.buffer;
    opt.lineMetrics = opts.lineMetrics;
    opt.maxZoom = opts.maxZoom;
    opt.indexMaxZoom = opts.indexMaxZoom;
    opt.indexMaxPoints = opts.indexMaxPoints;
    opt.generateId = opts.generateId;
  }
  return new geojsonvt_t{
    vt : mapbox::geojsonvt::GeoJSONVT(((struct _mapbox_geojson_t *)geom)->json,
                                      opt)
  };
}

void geojsonvt_free(geojsonvt_t *t) { delete t; }

geojsonvt_tile_t *geojsonvt_get_tile(geojsonvt_t *t, uint32_t z, uint32_t x,
                                     uint32_t y) {
  return new geojsonvt_tile_t{t->vt.getTile(z, x, y)};
}

#ifdef __cplusplus
}
#endif
