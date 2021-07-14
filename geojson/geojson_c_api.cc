#include "geojson_c_api.h"
#include "geom_c_api_impl.hh"

#include <mapbox/geojson_impl.hpp>

#include <mapbox/geometry/algorithms/closest_point.hpp>
#include <mapbox/geometry/algorithms/detail/boost_adapters.hpp>
#include <mapbox/geometry/algorithms/intersection.hpp>
#include <mapbox/geometry/algorithms/intersection_impl.hpp>
#include <mapbox/geometry/algorithms/predicates.hpp>
#include <mapbox/geometry/algorithms/scaling.hpp>

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

mapbox_box_t *mapbox_box_new(mapbox_point_t *min, mapbox_point_t *max) {
  return new mapbox_box_t{mapbox::geometry::box<double>{min->pt, max->pt}};
}

void mapbox_box_free(mapbox_box_t *box) { delete box; }

mapbox_point_t *mapbox_box_get_min(mapbox_box_t *box) {
  return new mapbox_point_t{box->box.min};
}

mapbox_point_t *mapbox_box_get_max(mapbox_box_t *box) {
  return new mapbox_point_t{box->box.max};
}

mapbox_box_t *mapbox_box_envelope(mapbox_geometry_t *geom) {
  return new mapbox_box_t{mapbox::geometry::envelope(geom->geom)};
}

mapbox_point_t *mapbox_point_new(double x, double y) {
  return new mapbox_point_t{mapbox::geometry::point<double>{x, y}};
}

void mapbox_point_free(mapbox_point_t *pt) { delete pt; }

double mapbox_point_get_x(mapbox_point_t *pt) { return pt->pt.x; }

double mapbox_point_get_y(mapbox_point_t *pt) { return pt->pt.y; }

void mapbox_point_get_xy(mapbox_point_t *pt, double *x, double *y) {
  *x = pt->pt.x;
  *y = pt->pt.y;
}

void mapbox_point_set_xy(mapbox_point_t *pt, double x, double y) {
  pt->pt.x = x;
  pt->pt.y = y;
}

mapbox_geometry_t *mapbox_point_to_geometry(mapbox_point_t *pt) {
  return new mapbox_geometry_t{mapbox::geometry::geometry<double>{pt->pt}};
}

bool mapbox_point_equal(mapbox_point_t *geom1, mapbox_point_t *geom2) {
  return geom1->pt == geom2->pt;
}

mapbox_line_string_t *mapbox_line_string_new(double *xy, int pointcount) {
  mapbox::geometry::line_string<double> ls;
  ls.reserve(pointcount);
  for (int i = 0; i < pointcount; i++) {
    ls.emplace_back(mapbox::geometry::point<double>{xy[i * 2], xy[i * 2 + 1]});
  }
  return new mapbox_line_string_t{std::move(ls)};
}

void mapbox_line_string_free(mapbox_line_string_t *ls) { delete ls; }

int mapbox_line_string_get_points_count(mapbox_line_string_t *ls) {
  return ls->ls.size();
}

void mapbox_line_string_update_point(mapbox_line_string_t *pt, int i, double x,
                                     double y) {
  if (i < pt->ls.size()) {
    pt->ls[i].x = x;
    pt->ls[i].y = y;
  }
}

mapbox_point_t *mapbox_line_string_get_point(mapbox_line_string_t *pt, int i) {
  auto p = pt->ls[i];
  return new mapbox_point_t{mapbox::geometry::point<double>{p.x, p.y}};
}

void mapbox_line_string_append_point(mapbox_line_string_t *pt, double x,
                                     double y) {
  pt->ls.emplace_back(mapbox::geometry::point<double>{x, y});
}

void mapbox_line_string_get_point_xy(mapbox_line_string_t *pt, int i, double *x,
                                     double *y) {
  auto p = pt->ls[i];
  *x = p.x;
  *y = p.y;
}

mapbox_geometry_t *mapbox_line_string_to_geometry(mapbox_line_string_t *pt) {
  return new mapbox_geometry_t{mapbox::geometry::geometry<double>{pt->ls}};
}

bool mapbox_line_string_equal(mapbox_line_string_t *geom1,
                              mapbox_line_string_t *geom2) {
  return geom1->ls == geom2->ls;
}

mapbox_multi_point_t *mapbox_multi_point_new(double *xy, int pointcount) {
  mapbox::geometry::multi_point<double> ls;
  ls.reserve(pointcount);
  for (int i = 0; i < pointcount; i++) {
    ls.emplace_back(mapbox::geometry::point<double>{xy[i * 2], xy[i * 2 + 1]});
  }
  return new mapbox_multi_point_t{std::move(ls)};
}

void mapbox_multi_point_free(mapbox_multi_point_t *ls) { delete ls; }

int mapbox_multi_point_get_points_count(mapbox_multi_point_t *ls) {
  return ls->mp.size();
}

mapbox_point_t *mapbox_multi_point_get_point(mapbox_multi_point_t *pt, int i) {
  auto p = pt->mp[i];
  return new mapbox_point_t{mapbox::geometry::point<double>{p.x, p.y}};
}

mapbox_geometry_t *mapbox_multi_point_to_geometry(mapbox_multi_point_t *pt) {
  return new mapbox_geometry_t{mapbox::geometry::geometry<double>{pt->mp}};
}

void mapbox_multi_point_update_point(mapbox_multi_point_t *pt, int i, double x,
                                     double y) {
  if (i < pt->mp.size()) {
    pt->mp[i].x = x;
    pt->mp[i].y = y;
  }
}

void mapbox_multi_point_append_point(mapbox_multi_point_t *pt, double x,
                                     double y) {
  pt->mp.emplace_back(mapbox::geometry::point<double>{x, y});
}

bool mapbox_multi_point_equal(mapbox_multi_point_t *geom1,
                              mapbox_multi_point_t *geom2) {
  return geom1->mp == geom2->mp;
}

void mapbox_multi_point_get_point_xy(mapbox_multi_point_t *pt, int i, double *x,
                                     double *y) {
  auto p = pt->mp[i];
  *x = p.x;
  *y = p.y;
}

mapbox_linear_ring_t *mapbox_linear_ring_new(double *xy, int pointcount) {
  mapbox::geometry::linear_ring<double> ls;
  ls.reserve(pointcount);
  for (int i = 0; i < pointcount; i++) {
    ls.emplace_back(mapbox::geometry::point<double>{xy[i * 2], xy[i * 2 + 1]});
  }
  return new mapbox_linear_ring_t{std::move(ls)};
}

void mapbox_linear_ring_free(mapbox_linear_ring_t *ls) { delete ls; }

int mapbox_linear_ring_get_points_count(mapbox_linear_ring_t *ls) {
  return ls->lr.size();
}

void mapbox_linear_ring_update_point(mapbox_linear_ring_t *pt, int i, double x,
                                     double y) {
  if (i < pt->lr.size()) {
    pt->lr[i].x = x;
    pt->lr[i].y = y;
  }
}

mapbox_point_t *mapbox_linear_ring_get_point(mapbox_linear_ring_t *pt, int i) {
  auto p = pt->lr[i];
  return new mapbox_point_t{mapbox::geometry::point<double>{p.x, p.y}};
}

void mapbox_linear_ring_get_point_xy(mapbox_linear_ring_t *pt, int i, double *x,
                                     double *y) {
  auto p = pt->lr[i];
  *x = p.x;
  *y = p.y;
}

void mapbox_linear_ring_append_point(mapbox_linear_ring_t *pt, double x,
                                     double y) {
  pt->lr.emplace_back(mapbox::geometry::point<double>{x, y});
}

bool mapbox_linear_ring_equal(mapbox_linear_ring_t *geom1,
                              mapbox_linear_ring_t *geom2) {
  return geom1->lr == geom2->lr;
}

mapbox_polygon_t *mapbox_polygon_new(mapbox_linear_ring_t **rings,
                                     int ringcount) {
  mapbox::geometry::polygon<double> polys;
  polys.reserve(ringcount);
  for (int i = 0; i < ringcount; i++) {
    polys.emplace_back(rings[i]->lr);
  }
  return new mapbox_polygon_t{polys};
}

void mapbox_polygon_free(mapbox_polygon_t *pt) { delete pt; }

mapbox_geometry_t *mapbox_polygon_to_geometry(mapbox_polygon_t *pt) {
  return new mapbox_geometry_t{mapbox::geometry::geometry<double>{pt->poly}};
}

void mapbox_polygon_set_exterior(mapbox_polygon_t *pt,
                                 mapbox_linear_ring_t *ring) {
  if (!pt->poly.empty()) {
    pt->poly[0] = ring->lr;
  } else {
    pt->poly.emplace_back(ring->lr);
  }
}

mapbox_linear_ring_t *mapbox_polygon_get_exterior(mapbox_polygon_t *pt) {
  if (!pt->poly.empty()) {
    return new mapbox_linear_ring_t{pt->poly[0]};
  }
  return nullptr;
}

int mapbox_polygon_get_interior_count(mapbox_polygon_t *pt) {
  return pt->poly.size() - 1;
}

mapbox_linear_ring_t *mapbox_polygon_get_interior(mapbox_polygon_t *pt, int i) {
  if (pt->poly.size() > 1) {
    return new mapbox_linear_ring_t{pt->poly[i + 1]};
  }
  return nullptr;
}

void mapbox_polygon_update_interior_ring(mapbox_polygon_t *pt, int i,
                                         mapbox_linear_ring_t *ring) {
  if (i < pt->poly.size() - 1) {
    pt->poly[i + 1] = ring->lr;
  }
}

void mapbox_polygon_append_interior_ring(mapbox_polygon_t *pt,
                                         mapbox_linear_ring_t *ring) {
  pt->poly.emplace_back(ring->lr);
}

bool mapbox_polygon_equal(mapbox_polygon_t *geom1, mapbox_polygon_t *geom2) {
  return geom1->poly == geom2->poly;
}

mapbox_multi_line_string_t *
mapbox_multi_line_string_new(mapbox_line_string_t **lines, int ringcount) {
  mapbox::geometry::multi_line_string<double> mls;
  mls.reserve(ringcount);
  for (int i = 0; i < ringcount; i++) {
    mls.emplace_back(lines[i]->ls);
  }
  return new mapbox_multi_line_string_t{mls};
}

void mapbox_multi_line_string_free(mapbox_multi_line_string_t *pt) {
  delete pt;
}

void mapbox_multi_line_string_append(mapbox_multi_line_string_t *pt,
                                     mapbox_line_string_t *line) {
  pt->mls.emplace_back(line->ls);
}

void mapbox_multi_line_string_update(mapbox_multi_line_string_t *pt, int i,
                                     mapbox_line_string_t *line) {
  if (i < pt->mls.size()) {
    pt->mls[i] = line->ls;
  }
}

int mapbox_multi_line_get_count(mapbox_multi_line_string_t *pt) {
  return pt->mls.size();
}

mapbox_line_string_t *
mapbox_multi_line_string_get(mapbox_multi_line_string_t *pt, int i) {
  return new mapbox_line_string_t{pt->mls[i]};
}

mapbox_geometry_t *
mapbox_multi_line_string_to_geometry(mapbox_multi_line_string_t *pt) {
  return new mapbox_geometry_t{mapbox::geometry::geometry<double>{pt->mls}};
}

bool mapbox_multi_line_string_equal(mapbox_multi_line_string_t *geom1,
                                    mapbox_multi_line_string_t *geom2) {
  return geom1->mls == geom2->mls;
}

mapbox_multi_polygon_t *mapbox_multi_polygon_new(mapbox_polygon_t **polys,
                                                 int polycount) {
  mapbox::geometry::multi_polygon<double> mls;
  mls.reserve(polycount);
  for (int i = 0; i < polycount; i++) {
    mls.emplace_back(polys[i]->poly);
  }
  return new mapbox_multi_polygon_t{mls};
}

void mapbox_multi_polygon_free(mapbox_multi_polygon_t *pt) { delete pt; }

void mapbox_multi_polygon_append(mapbox_multi_polygon_t *pt,
                                 mapbox_polygon_t *poly) {
  pt->mp.emplace_back(poly->poly);
}

void mapbox_multi_polygon_update(mapbox_multi_polygon_t *pt, int i,
                                 mapbox_polygon_t *line) {
  if (i < pt->mp.size()) {
    pt->mp[i] = line->poly;
  }
}

int mapbox_multi_polygon_get_count(mapbox_multi_polygon_t *pt) {
  return pt->mp.size();
}

mapbox_polygon_t *mapbox_multi_polygon_get(mapbox_multi_polygon_t *pt, int i) {
  return new mapbox_polygon_t{pt->mp[i]};
}

mapbox_geometry_t *
mapbox_multi_polygon_to_geometry(mapbox_multi_polygon_t *pt) {
  return new mapbox_geometry_t{mapbox::geometry::geometry<double>{pt->mp}};
}

bool mapbox_multi_polygon_equal(mapbox_multi_polygon_t *geom1,
                                mapbox_multi_polygon_t *geom2) {
  return geom1->mp == geom2->mp;
}

void mapbox_geometry_free(mapbox_geometry_t *geom) { delete geom; }

_Bool mapbox_geometry_empty(mapbox_geometry_t *geom) {
  return geom->geom.valid();
}

_Bool mapbox_geometry_is_point(mapbox_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::point<double>>();
}

_Bool mapbox_geometry_is_line_string(mapbox_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::line_string<double>>();
}

_Bool mapbox_geometry_is_polygon(mapbox_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::polygon<double>>();
}

_Bool mapbox_geometry_is_multi_point(mapbox_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::multi_point<double>>();
}

_Bool mapbox_geometry_is_multi_line_string(mapbox_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::multi_line_string<double>>();
}

_Bool mapbox_geometry_is_multi_polygon(mapbox_geometry_t *geom) {
  return geom->geom.is<mapbox::geometry::multi_polygon<double>>();
}

mapbox_point_t *mapbox_geometry_cast_point(mapbox_geometry_t *geom) {
  if (mapbox_geometry_is_point(geom)) {
    return new mapbox_point_t{
        geom->geom.get<mapbox::geometry::point<double>>()};
  }
  return nullptr;
}

mapbox_line_string_t *
mapbox_geometry_cast_line_string(mapbox_geometry_t *geom) {
  if (mapbox_geometry_is_line_string(geom)) {
    return new mapbox_line_string_t{
        geom->geom.get<mapbox::geometry::line_string<double>>()};
  }
  return nullptr;
}

mapbox_polygon_t *mapbox_geometry_cast_polygon(mapbox_geometry_t *geom) {
  if (mapbox_geometry_is_polygon(geom)) {
    return new mapbox_polygon_t{
        geom->geom.get<mapbox::geometry::polygon<double>>()};
  }
  return nullptr;
}

mapbox_multi_point_t *
mapbox_geometry_cast_multi_point(mapbox_geometry_t *geom) {
  if (mapbox_geometry_is_multi_point(geom)) {
    return new mapbox_multi_point_t{
        geom->geom.get<mapbox::geometry::multi_point<double>>()};
  }
  return nullptr;
}

mapbox_multi_line_string_t *
mapbox_geometry_cast_multi_line_string(mapbox_geometry_t *geom) {
  if (mapbox_geometry_is_multi_line_string(geom)) {
    return new mapbox_multi_line_string_t{
        geom->geom.get<mapbox::geometry::multi_line_string<double>>()};
  }
  return nullptr;
}

mapbox_multi_polygon_t *
mapbox_geometry_cast_multi_polygon(mapbox_geometry_t *geom) {
  if (mapbox_geometry_is_multi_polygon(geom)) {
    return new mapbox_multi_polygon_t{
        geom->geom.get<mapbox::geometry::multi_polygon<double>>()};
  }
  return nullptr;
}

bool mapbox_geometry_equal(mapbox_geometry_t *geom1, mapbox_geometry_t *geom2) {
  return geom1->geom == geom2->geom;
}

mapbox_geometry_collection_t *mapbox_geometry_collection_new() {
  return new mapbox_geometry_collection_t{};
}

void mapbox_geometry_collection_free(mapbox_geometry_collection_t *geom) {
  delete geom;
}

_Bool mapbox_geometry_collection_empty(mapbox_geometry_collection_t *gc) {
  return gc->gc.empty();
}

void mapbox_geometry_collection_append(mapbox_geometry_collection_t *gc,
                                       mapbox_geometry_t *geom) {
  gc->gc.emplace_back(geom->geom);
}

void mapbox_geometry_collection_update(mapbox_geometry_collection_t *gc, int i,
                                       mapbox_geometry_t *geom) {
  if (i < gc->gc.size()) {
    gc->gc[i] = geom->geom;
  }
}

int mapbox_geometry_collection_get_count(mapbox_geometry_collection_t *gc) {
  return gc->gc.size();
}

mapbox_geometry_t *
mapbox_geometry_collection_get(mapbox_geometry_collection_t *gc, int i) {
  if (i < gc->gc.size()) {
    return new mapbox_geometry_t{gc->gc[i]};
  }
  return nullptr;
}

mapbox_value_t *mapbox_value_new() {
  return new mapbox_value_t{
      mapbox::feature::value{mapbox::feature::null_value}};
}

void mapbox_value_free(mapbox_value_t *val) { delete val; }

mapbox_value_t *mapbox_value_from_bool(_Bool v) {
  return new mapbox_value_t{mapbox::feature::value{v}};
}

mapbox_value_t *mapbox_value_from_uint(uint64_t v) {
  return new mapbox_value_t{mapbox::feature::value{v}};
}

mapbox_value_t *mapbox_value_from_int(int64_t v) {
  return new mapbox_value_t{mapbox::feature::value{v}};
}

mapbox_value_t *mapbox_value_from_double(double v) {
  return new mapbox_value_t{mapbox::feature::value{v}};
}

mapbox_value_t *mapbox_value_from_string(const char *v) {
  return new mapbox_value_t{mapbox::feature::value{std::string(v)}};
}

mapbox_value_t *mapbox_value_from_values(mapbox_value_t **vs, int valuecount) {
  std::vector<mapbox::feature::value> v;
  v.reserve(valuecount);
  for (int i = 0; i < valuecount; i++) {
    v.emplace_back(vs[i]->val);
  }
  return new mapbox_value_t{mapbox::feature::value{v}};
}

mapbox_value_t *mapbox_value_from_keyvalues(const char **ks,
                                            mapbox_value_t **vs,
                                            int valuecount) {
  std::unordered_map<std::string, mapbox::feature::value> v;
  for (int i = 0; i < valuecount; i++) {
    v.emplace(ks[i], vs[i]->val);
  }
  return new mapbox_value_t{mapbox::feature::value{v}};
}

_Bool mapbox_value_is_empty(mapbox_value_t *geom) { return !geom->val.valid(); }

_Bool mapbox_value_is_null(mapbox_value_t *geom) {
  return geom->val.is<mapbox::feature::null_value_t>();
}

_Bool mapbox_value_is_bool(mapbox_value_t *geom) {
  return geom->val.is<bool>();
}

_Bool mapbox_value_is_uint(mapbox_value_t *geom) {
  return geom->val.is<uint64_t>();
}

_Bool mapbox_value_is_int(mapbox_value_t *geom) {
  return geom->val.is<int64_t>();
}

_Bool mapbox_value_is_double(mapbox_value_t *geom) {
  return geom->val.is<double>();
}

_Bool mapbox_value_is_string(mapbox_value_t *geom) {
  return geom->val.is<std::string>();
}

_Bool mapbox_value_is_vector(mapbox_value_t *geom) {
  return geom->val.is<std::shared_ptr<std::vector<mapbox::feature::value>>>();
}

_Bool mapbox_value_is_map(mapbox_value_t *geom) {
  return geom->val.is<std::shared_ptr<
      std::unordered_map<std::string, mapbox::feature::value>>>();
}

_Bool mapbox_value_cast_bool(mapbox_value_t *geom) {
  return geom->val.get<bool>();
}

uint64_t mapbox_value_cast_uint(mapbox_value_t *geom) {
  return geom->val.get<uint64_t>();
}

int64_t mapbox_value_cast_int(mapbox_value_t *geom) {
  return geom->val.get<int64_t>();
}

double mapbox_value_cast_double(mapbox_value_t *geom) {
  return geom->val.get<double>();
}

char *mapbox_value_cast_string(mapbox_value_t *geom) {
  auto str = geom->val.get<std::string>();
  return strdup(str.c_str());
}

mapbox_value_t **mapbox_value_cast_vector(mapbox_value_t *geom, int *count) {
  auto wvec =
      geom->val.get<std::shared_ptr<std::vector<mapbox::feature::value>>>();
  auto &vec = *wvec;
  mapbox_value_t **ret = new mapbox_value_t *[vec.size()];
  *count = vec.size();
  for (int i = 0; i < vec.size(); i++) {
    ret[i] = new mapbox_value_t{vec[i]};
  }
  return ret;
}

void mapbox_values_free(mapbox_value_t **vs) { delete[] vs; }

mapbox_property_map_t *mapbox_value_cast_map(mapbox_value_t *geom) {
  auto wmap = geom->val.get<std::shared_ptr<
      std::unordered_map<std::string, mapbox::feature::value>>>();
  return new mapbox_property_map_t{*wmap};
}

mapbox_property_map_t *mapbox_property_map_new() {
  return new mapbox_property_map_t{};
}

void mapbox_property_map_free(mapbox_property_map_t *val) { delete val; }

mapbox_value_t *mapbox_property_map_get(mapbox_property_map_t *val,
                                        const char *key) {
  if (mapbox_property_map_has(val, key)) {
    return new mapbox_value_t{val->prop[key]};
  }
  return mapbox_value_new();
}

void mapbox_property_map_set(mapbox_property_map_t *val, const char *key,
                             mapbox_value_t *v) {
  val->prop[key] = v->val;
}

_Bool mapbox_property_map_has(mapbox_property_map_t *val, const char *key) {
  if (val->prop.find(key) == val->prop.end()) {
    return false;
  }
  return true;
}

_Bool mapbox_property_map_empty(mapbox_property_map_t *val) {
  return val->prop.empty();
}

char **mapbox_property_map_keys(mapbox_property_map_t *val, int *count) {
  *count = val->prop.size();
  char **keys = new char *[*count];
  int i = 0;
  for (auto rp : val->prop) {
    keys[i] = strdup(rp.first.c_str());
  }
  return keys;
}

void mapbox_property_map_free_keys(char **keys, int count) {
  for (int i = 0; i < count; i++) {
    free(keys[i]);
  }
  delete[] keys;
}

int mapbox_property_map_count(mapbox_property_map_t *val) {
  return val->prop.size();
}

mapbox_identifier_t *mapbox_identifier_from_uint(uint64_t v) {
  return new mapbox_identifier_t{v};
}

mapbox_identifier_t *mapbox_identifier_from_int(int64_t v) {
  return new mapbox_identifier_t{v};
}

mapbox_identifier_t *mapbox_identifier_from_double(double v) {
  return new mapbox_identifier_t{v};
}

mapbox_identifier_t *mapbox_identifier_from_string(const char *v) {
  return new mapbox_identifier_t{std::string(v)};
}

void mapbox_identifier_free(mapbox_identifier_t *val) { delete val; }

_Bool mapbox_identifier_is_uint(mapbox_identifier_t *geom) {
  return geom->id.is<uint64_t>();
}

_Bool mapbox_identifier_is_int(mapbox_identifier_t *geom) {
  return geom->id.is<int64_t>();
}

_Bool mapbox_identifier_is_double(mapbox_identifier_t *geom) {
  return geom->id.is<double>();
}

_Bool mapbox_identifier_is_string(mapbox_identifier_t *geom) {
  return geom->id.is<std::string>();
}

uint64_t mapbox_identifier_cast_uint(mapbox_identifier_t *geom) {
  return geom->id.get<uint64_t>();
}

int64_t mapbox_identifier_cast_int(mapbox_identifier_t *geom) {
  return geom->id.get<int64_t>();
}

double mapbox_identifier_cast_double(mapbox_identifier_t *geom) {
  return geom->id.get<double>();
}

char *mapbox_identifier_cast_string(mapbox_identifier_t *geom) {
  auto str = geom->id.get<std::string>();
  return strdup(str.c_str());
}

mapbox_feature_t *mapbox_feature_new(mapbox_geometry_t *geom) {
  return new mapbox_feature_t{mapbox::feature::feature<double>{geom->geom}};
}

mapbox_feature_t *mapbox_feature_create(mapbox_identifier_t *id,
                                        mapbox_geometry_t *geom,
                                        mapbox_property_map_t *props) {
  return new mapbox_feature_t{
      mapbox::feature::feature<double>{geom->geom, props->prop, id->id}};
}

void mapbox_feature_free(mapbox_feature_t *feat) { delete feat; }

void mapbox_feature_set_identifier(mapbox_feature_t *feat,
                                   mapbox_identifier_t *id) {
  feat->feat.id = id->id;
}

void mapbox_feature_set_geometry(mapbox_feature_t *feat,
                                 mapbox_geometry_t *geom) {
  feat->feat.geometry = geom->geom;
}

void mapbox_feature_set_property_map(mapbox_feature_t *feat,
                                     mapbox_property_map_t *props) {
  feat->feat.properties = props->prop;
}

mapbox_identifier_t *mapbox_feature_get_identifier(mapbox_feature_t *feat) {
  if (feat->feat.id.valid()) {
    return new mapbox_identifier_t{feat->feat.id};
  }
  return nullptr;
}

mapbox_geometry_t *mapbox_feature_get_geometry(mapbox_feature_t *feat) {
  return new mapbox_geometry_t{feat->feat.geometry};
}

mapbox_property_map_t *mapbox_feature_get_property_map(mapbox_feature_t *feat) {
  return new mapbox_property_map_t{feat->feat.properties};
}

bool mapbox_feature_equal(mapbox_feature_t *feat1, mapbox_feature_t *feat2) {
  return feat1->feat == feat2->feat;
}

mapbox_feature_collection_t *mapbox_feature_collection_new() {
  return new mapbox_feature_collection_t{};
}

void mapbox_feature_collection_free(mapbox_feature_collection_t *geom) {
  delete geom;
}

_Bool mapbox_feature_collection_empty(mapbox_feature_collection_t *gc) {
  return gc->fc.empty();
}

void mapbox_feature_collection_append(mapbox_feature_collection_t *gc,
                                      mapbox_feature_t *feat) {
  gc->fc.emplace_back(feat->feat);
}

void mapbox_feature_collection_update(mapbox_feature_collection_t *gc, int i,
                                      mapbox_feature_t *feat) {
  if (i < gc->fc.size()) {
    gc->fc[i] = feat->feat;
  }
}

int mapbox_feature_collection_get_count(mapbox_feature_collection_t *gc) {
  return gc->fc.size();
}

mapbox_feature_t *mapbox_feature_collection_get(mapbox_feature_collection_t *gc,
                                                int i) {
  if (i < gc->fc.size()) {
    return new mapbox_feature_t{gc->fc[i]};
  }
  return nullptr;
}

mapbox_geojson_t *mapbox_geojson_parse(const char *json) {
  return new mapbox_geojson_t{mapbox::geojson::parse(json)};
}

mapbox_geojson_t *mapbox_geojson_from_geometry(mapbox_geometry_t *geom) {
  return new mapbox_geojson_t{geom->geom};
}

mapbox_geojson_t *mapbox_geojson_from_feature(mapbox_feature_t *feat) {
  return new mapbox_geojson_t{feat->feat};
}

mapbox_geojson_t *
mapbox_geojson_from_feature_collection(mapbox_feature_collection_t *fc) {
  return new mapbox_geojson_t{fc->fc};
}

void mapbox_geojson_free(mapbox_geojson_t *gejson) { delete gejson; }

_Bool mapbox_geojson_is_empty(mapbox_geojson_t *gejson) {
  return !gejson->json.valid();
}

_Bool mapbox_geojson_is_geometry(mapbox_geojson_t *gejson) {
  return gejson->json.is<mapbox::geojson::geometry>();
}

_Bool mapbox_geojson_is_feature(mapbox_geojson_t *gejson) {
  return gejson->json.is<mapbox::geojson::feature>();
}

_Bool mapbox_geojson_is_feature_collection(mapbox_geojson_t *gejson) {
  return gejson->json.is<mapbox::geojson::feature_collection>();
}

mapbox_geometry_t *mapbox_geojson_get_geometry(mapbox_geojson_t *gejson) {
  return new mapbox_geometry_t{gejson->json.get<mapbox::geojson::geometry>()};
}

mapbox_feature_t *mapbox_geojson_get_feature(mapbox_geojson_t *gejson) {
  return new mapbox_feature_t{gejson->json.get<mapbox::geojson::feature>()};
}

mapbox_feature_collection_t *
mapbox_geojson_get_feature_collection(mapbox_geojson_t *gejson) {
  return new mapbox_feature_collection_t{
      gejson->json.get<mapbox::geojson::feature_collection>()};
}

void mapbox_geojson_set_geometry(mapbox_geojson_t *gejson,
                                 mapbox_geometry_t *geom) {
  gejson->json = geom->geom;
}

void mapbox_geojson_set_feature(mapbox_geojson_t *gejson,
                                mapbox_feature_t *feat) {
  gejson->json = feat->feat;
}

void mapbox_geojson_set_feature_collection(mapbox_geojson_t *gejson,
                                           mapbox_feature_collection_t *fc) {
  gejson->json = fc->fc;
}

char *mapbox_geojson_stringify(mapbox_geojson_t *gejson) {
  std::string json = mapbox::geojson::stringify(gejson->json);
  return strdup(json.c_str());
}

mapbox_geometry_t **
mapbox_spatial_algorithms_intersects(mapbox_geometry_t *geom1,
                                     mapbox_geometry_t *geom2, int *count) {
  auto geoms =
      mapbox::geometry::algorithms::intersection(geom1->geom, geom2->geom);
  return nullptr;
}

_Bool mapbox_spatial_algorithms_disjoint(mapbox_geometry_t *geom1,
                                         mapbox_geometry_t *geom2) {
  return false;
}

mapbox_geometry_t **
mapbox_spatial_algorithms_intersection(mapbox_geometry_t *geom1,
                                       mapbox_geometry_t *geom2, int *count) {
  return nullptr;
}

#ifdef __cplusplus
}
#endif
