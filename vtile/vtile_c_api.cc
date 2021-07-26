#include "vtile_c_api.h"
#include "composite.hh"
#include "geom_c_api_impl.hh"

#include <vtzero/builder.hpp>
#include <vtzero/index.hpp>
#include <vtzero/property_mapper.hpp>
#include <vtzero/vector_tile.hpp>

#include <unordered_map>

#ifdef __cplusplus
extern "C" {
#endif

struct _mvt_vector_tile_t {
  vtzero::vector_tile vt;
};

struct _mvt_layer_t {
  vtzero::layer l;
};

struct _mvt_property_value_t {
  vtzero::property_value pv;
};

struct _mvt_feature_t {
  vtzero::feature feat;
};

struct _mvt_geometry_t {
  vtzero::geometry geom;
};

struct _mvt_property_t {
  vtzero::property prop;
};

struct _mvt_property_mapper_t {
  vtzero::property_mapper mapper;
};

struct _mvt_geometry_point_t {
  std::vector<vtzero::point> data;

  void points_begin(uint32_t count) { data.reserve(count); }

  void points_point(const vtzero::point point) { data.push_back(point); }

  void points_end() const noexcept {}
};

using ls_type = std::vector<std::vector<vtzero::point>>;

struct _mvt_geometry_linestring_t {

  ls_type data;

  void linestring_begin(uint32_t count) {
    data.emplace_back();
    data.back().reserve(count);
  }

  void linestring_point(const vtzero::point point) {
    data.back().push_back(point);
  }

  void linestring_end() const noexcept {}
};

using polygon_type = std::vector<std::vector<vtzero::point>>;

struct _mvt_geometry_polygon_t {

  polygon_type data;

  void ring_begin(uint32_t count) {
    data.emplace_back();
    data.back().reserve(count);
  }

  void ring_point(const vtzero::point point) { data.back().push_back(point); }

  void ring_end(vtzero::ring_type /* type */) const noexcept {}
};

struct _mvt_tile_builder_t {
  vtzero::tile_builder builder;
};

struct _mvt_layer_builder_t {
  vtzero::layer_builder builder;
};

struct _mvt_point_feature_builder_t {
  vtzero::point_feature_builder builder;
};

struct _mvt_linestring_feature_builder_t {
  vtzero::linestring_feature_builder builder;
};

struct _mvt_polygon_feature_builder_t {
  vtzero::polygon_feature_builder builder;
};

struct _mvt_geometry_feature_builder_t {
  vtzero::geometry_feature_builder builder;
};

struct _mvt_key_index_t {
  vtzero::key_index<std::unordered_map> idx;
};

struct _mvt_int32_value_index_t {
  vtzero::value_index<vtzero::sint_value_type, int32_t, std::unordered_map> idx;
};

struct _mvt_int64_value_index_t {
  vtzero::value_index<vtzero::sint_value_type, int64_t, std::unordered_map> idx;
};

struct _mvt_uint64_value_index_t {
  vtzero::value_index<vtzero::uint_value_type, uint64_t, std::unordered_map>
      idx;
};

struct _mvt_uint32_value_index_t {
  vtzero::value_index<vtzero::uint_value_type, uint32_t, std::unordered_map>
      idx;
};

struct _mvt_float_value_index_t {
  vtzero::value_index<vtzero::float_value_type, float, std::unordered_map> idx;
};

struct _mvt_double_value_index_t {
  vtzero::value_index<vtzero::double_value_type, double, std::unordered_map>
      idx;
};

struct _mvt_string_value_index_t {
  vtzero::value_index<vtzero::string_value_type, std::string,
                      std::unordered_map>
      idx;
};

struct _mvt_bool_value_index_t {
  vtzero::value_index_bool idx;
};

struct _mvt_uint16_t_value_index_t {
  vtzero::value_index_small_uint idx;
};

struct _mvt_tile_object_t {
  std::unique_ptr<vtile::tile_object> obj;
};

struct _mvt_baton_t {
  std::unique_ptr<vtile::baton_type> b;
};

mvt_vector_tile_t *mvt_vector_tile_new(const char *data, size_t si) {
  return new mvt_vector_tile_t{vtzero::vector_tile(data, si)};
}

void mvt_vector_tile_free(mvt_vector_tile_t *ctx) {
  if (ctx != nullptr) {
    delete ctx;
  }
}

_Bool mvt_vector_tile_empty(mvt_vector_tile_t *ctx) { return ctx->vt.empty(); }

size_t mvt_vector_tile_count_layers(mvt_vector_tile_t *ctx) {
  return ctx->vt.count_layers();
}

mvt_layer_t *mvt_vector_tile_next_layer(mvt_vector_tile_t *ctx) {
  return new mvt_layer_t{ctx->vt.next_layer()};
}

void mvt_vector_tile_reset_layer(mvt_vector_tile_t *ctx) {
  ctx->vt.reset_layer();
}

mvt_layer_t *mvt_vector_tile_get_layer(mvt_vector_tile_t *ctx, int index) {
  return new mvt_layer_t{ctx->vt.get_layer(index)};
}

mvt_layer_t *mvt_vector_tile_get_layer_by_name(mvt_vector_tile_t *ctx,
                                               const char *name) {
  return new mvt_layer_t{ctx->vt.get_layer_by_name(name)};
}

_Bool mvt_vector_tile_is_vector_tile(const char *data, size_t si) {
  return vtzero::is_vector_tile(vtzero::data_view(data, si));
}

mvt_layer_t *mvt_layer_new() { return new mvt_layer_t{}; }

mvt_layer_t *mvt_layer_new_with_data(const char *data, size_t si) {
  return new mvt_layer_t{vtzero::layer(vtzero::data_view(data, si))};
}

_Bool mvt_layer_valid(mvt_layer_t *ctx) { return ctx->l.valid(); }

const char *mvt_layer_get_data(mvt_layer_t *ctx, size_t *si) {
  auto dv = ctx->l.data();
  *si = dv.size();
  return dv.data();
}

const char *mvt_layer_get_name(mvt_layer_t *ctx) {
  return ctx->l.name().data();
}

uint32_t mvt_layer_version(mvt_layer_t *ctx) { return ctx->l.version(); }

uint32_t mvt_layer_extent(mvt_layer_t *ctx) { return ctx->l.extent(); }

_Bool mvt_layer_empty(mvt_layer_t *ctx) { return ctx->l.empty(); }

size_t mvt_layer_num_features(mvt_layer_t *ctx) {
  return ctx->l.num_features();
}

char **mvt_layer_key_table(mvt_layer_t *ctx, size_t *si) {
  auto kts = ctx->l.key_table();
  *si = kts.size();
  char **ret = new char *[*si];
  for (int i = 0; i < *si; i++) {
    ret[i] = strdup(kts[i].data());
  }
  return ret;
}

void mvt_layer_free_key_table(char **kts, size_t si) {
  for (int i = 0; i < si; i++) {
    free(kts[i]);
  }
  delete[] kts;
}

size_t mvt_layer_key_table_size(mvt_layer_t *ctx) {
  return ctx->l.key_table_size();
}

mvt_property_value_t **mvt_layer_value_table(mvt_layer_t *ctx, size_t *si) {
  auto vts = ctx->l.value_table();
  *si = vts.size();
  mvt_property_value_t **ret = new mvt_property_value_t *[*si];
  for (int i = 0; i < *si; i++) {
    ret[i] = new mvt_property_value_t{vts[i]};
  }
  return ret;
}

void mvt_layer_free_value_table(mvt_property_value_t **vts, size_t si) {
  for (int i = 0; i < si; i++) {
    delete vts[i];
  }
  delete[] vts;
}

size_t mvt_layer_key_value_size(mvt_layer_t *ctx) {
  return ctx->l.value_table_size();
}

char *mvt_layer_get_key(mvt_layer_t *ctx, int i) {
  auto key = ctx->l.key(i);
  return strdup(key.data());
}

mvt_property_value_t *mvt_layer_get_value(mvt_layer_t *ctx, int i) {
  auto val = ctx->l.value(i);
  return new mvt_property_value_t{val};
}

mvt_feature_t *mvt_vector_layer_next_feature(mvt_layer_t *ctx) {
  return new mvt_feature_t{ctx->l.next_feature()};
}

void mvt_layer_reset_feature(mvt_layer_t *ctx) { ctx->l.reset_feature(); }

mvt_feature_t *mvt_vector_layer_get_feature_by_id(mvt_layer_t *ctx,
                                                  uint64_t i) {
  return new mvt_feature_t{ctx->l.get_feature_by_id(i)};
}

mvt_feature_t *mvt_feature_new() { return new mvt_feature_t{}; }

mvt_feature_t *mvt_feature_new_with_data(mvt_layer_t *layer, const char *data,
                                         size_t si) {
  return new mvt_feature_t{
      vtzero::feature(&layer->l, vtzero::data_view{data, si})};
}

void mvt_feature_free(mvt_feature_t *ctx) { delete ctx; }

_Bool mvt_feature_valid(mvt_feature_t *ctx) { return ctx->feat.valid(); }

uint64_t mvt_feature_get_id(mvt_feature_t *ctx) { return ctx->feat.id(); }

_Bool mvt_feature_has_id(mvt_feature_t *ctx) { return ctx->feat.has_id(); }

uint32_t mvt_feature_get_geometry_type(mvt_feature_t *ctx) {
  return static_cast<uint32_t>(ctx->feat.geometry_type());
}

mvt_geometry_t *mvt_feature_get_geometry(mvt_feature_t *ctx) {
  return new mvt_geometry_t{ctx->feat.geometry()};
}

_Bool mvt_feature_empty(mvt_feature_t *ctx) { return ctx->feat.empty(); }

size_t mvt_feature_num_properties(mvt_feature_t *ctx) {
  return ctx->feat.num_properties();
}

mvt_property_t *mvt_feature_next_property(mvt_feature_t *ctx) {
  return new mvt_property_t{ctx->feat.next_property()};
}

void mvt_feature_reset_property(mvt_feature_t *ctx) {
  ctx->feat.reset_property();
}

_Bool mvt_feature_next_property_indexes(mvt_feature_t *ctx, uint32_t *key,
                                        uint32_t *value) {
  auto pair = ctx->feat.next_property_indexes();
  if (pair.key().valid() && pair.value().valid()) {
    *key = pair.key().value();
    *value = pair.value().value();
    return true;
  }
  return false;
}

mvt_property_t *mvt_property_new() { return new mvt_property_t{}; }

mvt_property_t *mvt_property_new_with_keyvalue(const char *key,
                                               mvt_property_value_t *value) {
  vtzero::data_view dview{key, strlen(key)};
  return new mvt_property_t{vtzero::property(dview, value->pv)};
}

void mvt_property_free(mvt_property_t *prop) { delete prop; }

_Bool mvt_property_valid(mvt_property_t *prop) { return prop->prop.valid(); }

char *mvt_feature_get_key(mvt_property_t *prop) {
  return strdup(prop->prop.key().data());
}

mvt_property_value_t *mvt_feature_get_value(mvt_property_t *prop) {
  return new mvt_property_value_t{prop->prop.value()};
}

mvt_property_value_t *mvt_property_value_new() {
  return new mvt_property_value_t{};
}

mvt_property_value_t *mvt_property_value_new_with_data(const char *data,
                                                       size_t si) {
  return new mvt_property_value_t{
      vtzero::property_value(vtzero::data_view(data, si))};
}

void mvt_property_value_free(mvt_property_value_t *pv) { delete pv; }

_Bool mvt_property_value_valid(mvt_property_value_t *pv) {
  return pv->pv.valid();
}

uint32_t mvt_property_value_get_type(mvt_property_value_t *pv) {
  return static_cast<uint32_t>(pv->pv.type());
}

const char *mvt_property_value_get_data(mvt_property_value_t *pv, size_t *si) {
  auto dv = pv->pv.data();
  *si = dv.size();
  return dv.data();
}

const char *mvt_property_value_get_string(mvt_property_value_t *pv) {
  return pv->pv.string_value().data();
}

float mvt_property_value_get_float(mvt_property_value_t *pv) {
  return pv->pv.float_value();
}

double mvt_property_value_get_double(mvt_property_value_t *pv) {
  return pv->pv.double_value();
}

int64_t mvt_property_value_get_int(mvt_property_value_t *pv) {
  return pv->pv.int_value();
}

uint64_t mvt_property_value_get_uint(mvt_property_value_t *pv) {
  return pv->pv.uint_value();
}

int64_t mvt_property_value_get_sint(mvt_property_value_t *pv) {
  return pv->pv.sint_value();
}

bool mvt_property_value_get_bool(mvt_property_value_t *pv) {
  return pv->pv.bool_value();
}

mvt_geometry_t *mvt_geometry_new() { return new mvt_geometry_t{}; }

mvt_geometry_t *mvt_geometry_new_with_data(const char *data, size_t si,
                                           uint32_t type) {
  return new mvt_geometry_t{vtzero::geometry(
      vtzero::data_view(data, si), static_cast<vtzero::GeomType>(type))};
}

void mvt_geometry_free(mvt_geometry_t *geom) { delete geom; }

uint32_t mvt_geometry_get_type(mvt_geometry_t *geom) {
  return static_cast<uint32_t>(geom->geom.type());
}

const char *mvt_geometry_get_data(mvt_geometry_t *geom, size_t *si) {
  auto dv = geom->geom.data();
  *si = dv.size();
  return dv.data();
}

mvt_geometry_point_t *mvt_geometry_decode_point_geometry(mvt_geometry_t *geom) {
  mvt_geometry_point_t *handler = new mvt_geometry_point_t{};
  vtzero::decode_point_geometry(geom->geom, *handler);
  return handler;
}

mvt_geometry_linestring_t *
mvt_geometry_decode_linestring_geometry(mvt_geometry_t *geom) {
  mvt_geometry_linestring_t *handler = new mvt_geometry_linestring_t{};
  vtzero::decode_linestring_geometry(geom->geom, *handler);
  return handler;
}

mvt_geometry_polygon_t *
mvt_geometry_decode_polygon_geometry(mvt_geometry_t *geom) {
  mvt_geometry_polygon_t *handler = new mvt_geometry_polygon_t{};
  vtzero::decode_polygon_geometry(geom->geom, *handler);
  return handler;
}

void mvt_geometry_point_free(mvt_geometry_point_t *point) { delete point; }

size_t mvt_geometry_point_count(mvt_geometry_point_t *point) {
  return point->data.size();
}

size_t mvt_geometry_point_get_points(mvt_geometry_point_t *point,
                                     int32_t *xylist, size_t count) {
  size_t si = std::min(count, point->data.size());
  for (int i = 0; i < si; i++) {
    xylist[i * 2] = point->data[i].x;
    xylist[i * 2 + 1] = point->data[i].y;
  }
  return si;
}

void mvt_geometry_linestring_free(mvt_geometry_linestring_t *ls) { delete ls; }

size_t mvt_geometry_linestring_count(mvt_geometry_linestring_t *ls) {
  return ls->data.size();
}

size_t mvt_geometry_linestring_get_lines(mvt_geometry_linestring_t *ls,
                                         mvt_geometry_point_t *ptlist,
                                         size_t count) {
  size_t si = std::min(count, ls->data.size());
  for (int i = 0; i < si; i++) {
    ptlist[i].data = ls->data[i];
  }
  return si;
}

void mvt_geometry_polygon_free(mvt_geometry_polygon_t *poly) { delete poly; }

size_t mvt_geometry_polygon_count(mvt_geometry_polygon_t *poly) {
  return poly->data.size();
}

size_t mvt_geometry_polygon_get_lines(mvt_geometry_polygon_t *poly,
                                      mvt_geometry_point_t *ptlist,
                                      size_t count) {
  size_t si = std::min(count, poly->data.size());
  for (int i = 0; i < si; i++) {
    ptlist[i].data = poly->data[i];
  }
  return si;
}

mvt_tile_builder_t *mvt_tile_builder_new() { return new mvt_tile_builder_t{}; }

void mvt_tile_builder_free(mvt_tile_builder_t *tb) { delete tb; }

void mvt_tile_builder_add_existing_layer(mvt_tile_builder_t *tb,
                                         mvt_layer_t *layer) {
  tb->builder.add_existing_layer(layer->l);
}

char *mvt_tile_builder_serialize(mvt_tile_builder_t *tb, size_t *si) {
  auto str = tb->builder.serialize();
  *si = str.size();
  char *rstr = (char *)malloc(sizeof(char) * str.size());
  memcpy(rstr, str.data(), *si);
  return rstr;
}

mvt_layer_builder_t *mvt_tile_builder_get_layer_builder(mvt_tile_builder_t *tb,
                                                        const char *name,
                                                        uint32_t version,
                                                        uint32_t extent) {
  return new mvt_layer_builder_t{
      vtzero::layer_builder(tb->builder, name, version, extent)};
}

void mvt_layer_builder_free(mvt_layer_builder_t *layer) { delete layer; }

void mvt_layer_builder_add_key(mvt_layer_builder_t *layer, const char *name) {
  layer->builder.add_key(vtzero::data_view(name, strlen(name)));
}

void mvt_layer_builder_add_value(mvt_layer_builder_t *layer,
                                 mvt_property_value_t *value) {
  layer->builder.add_value(value->pv);
}

void mvt_layer_builder_add_feature(mvt_layer_builder_t *layer,
                                   mvt_feature_t *feat) {
  layer->builder.add_feature(feat->feat);
}

mvt_point_feature_builder_t *
mvt_layer_builder_get_point_feature_builder(mvt_layer_builder_t *layer) {
  return new mvt_point_feature_builder_t{
      vtzero::point_feature_builder{layer->builder}};
}

mvt_linestring_feature_builder_t *
mvt_layer_builder_get_linestring_feature_builder(mvt_layer_builder_t *layer) {
  return new mvt_linestring_feature_builder_t{
      vtzero::linestring_feature_builder{layer->builder}};
}

mvt_polygon_feature_builder_t *
mvt_layer_builder_get_polygon_feature_builder(mvt_layer_builder_t *layer) {
  return new mvt_polygon_feature_builder_t{
      vtzero::polygon_feature_builder{layer->builder}};
}

mvt_geometry_feature_builder_t *
mvt_layer_builder_get_geometry_feature_builder(mvt_layer_builder_t *layer) {
  return new mvt_geometry_feature_builder_t{
      vtzero::geometry_feature_builder{layer->builder}};
}

void mvt_point_feature_builder_free(mvt_point_feature_builder_t *builder) {
  delete builder;
}

void mvt_point_feature_builder_set_id(mvt_point_feature_builder_t *builder,
                                      uint64_t id) {
  builder->builder.set_id(id);
}
void mvt_point_feature_builder_copy_id(mvt_point_feature_builder_t *builder,
                                       mvt_feature_t *feat) {
  builder->builder.copy_id(feat->feat);
}

void mvt_point_feature_builder_add_property(
    mvt_point_feature_builder_t *builder, mvt_property_t *property) {
  builder->builder.add_property(property->prop);
}

void mvt_point_feature_builder_copy_properties(
    mvt_point_feature_builder_t *builder, mvt_feature_t *feat) {
  builder->builder.copy_properties(feat->feat);
}

void mvt_point_feature_builder_copy_properties_with_mapper(
    mvt_point_feature_builder_t *builder, mvt_feature_t *feat,
    mvt_property_mapper_t *mapper) {
  builder->builder.copy_properties(feat->feat, mapper->mapper);
}

void mvt_point_feature_builder_commit(mvt_point_feature_builder_t *builder) {
  builder->builder.commit();
}

void mvt_point_feature_builder_rollback(mvt_point_feature_builder_t *builder) {
  builder->builder.rollback();
}

void mvt_point_feature_builder_add_point(mvt_point_feature_builder_t *builder,
                                         const int32_t x, const int32_t y) {
  builder->builder.add_point(vtzero::point{x, y});
}

void mvt_point_feature_builder_set_point(mvt_point_feature_builder_t *builder,
                                         const int32_t x, const int32_t y) {
  builder->builder.set_point(x, y);
}

void mvt_linestring_feature_builder_free(
    mvt_linestring_feature_builder_t *builder) {
  delete builder;
}

void mvt_linestring_feature_builder_set_id(
    mvt_linestring_feature_builder_t *builder, uint64_t id) {
  builder->builder.set_id(id);
}
void mvt_linestring_feature_builder_copy_id(
    mvt_linestring_feature_builder_t *builder, mvt_feature_t *feat) {
  builder->builder.copy_id(feat->feat);
}

void mvt_linestring_feature_builder_add_property(
    mvt_linestring_feature_builder_t *builder, mvt_property_t *property) {
  builder->builder.add_property(property->prop);
}

void mvt_linestring_feature_builder_copy_properties(
    mvt_linestring_feature_builder_t *builder, mvt_feature_t *feat) {
  builder->builder.copy_properties(feat->feat);
}

void mvt_linestring_feature_builder_copy_properties_with_mapper(
    mvt_linestring_feature_builder_t *builder, mvt_feature_t *feat,
    mvt_property_mapper_t *mapper) {
  builder->builder.copy_properties(feat->feat, mapper->mapper);
}

void mvt_linestring_feature_builder_commit(
    mvt_linestring_feature_builder_t *builder) {
  builder->builder.commit();
}

void mvt_linestring_feature_builder_rollback(
    mvt_linestring_feature_builder_t *builder) {
  builder->builder.rollback();
}

void mvt_linestring_feature_builder_add_linestring(
    mvt_linestring_feature_builder_t *builder, int linecount) {
  builder->builder.add_linestring(linecount);
}

void mvt_linestring_feature_builder_set_point(
    mvt_linestring_feature_builder_t *builder, const int32_t x,
    const int32_t y) {
  builder->builder.set_point(x, y);
}

void mvt_polygon_feature_builder_free(mvt_polygon_feature_builder_t *builder) {
  delete builder;
}

void mvt_polygon_feature_builder_set_id(mvt_polygon_feature_builder_t *builder,
                                        uint64_t id) {
  builder->builder.set_id(id);
}

void mvt_polygon_feature_builder_copy_id(mvt_polygon_feature_builder_t *builder,
                                         mvt_feature_t *feat) {
  builder->builder.copy_id(feat->feat);
}

void mvt_polygon_feature_builder_add_property(
    mvt_polygon_feature_builder_t *builder, mvt_property_t *property) {
  builder->builder.add_property(property->prop);
}

void mvt_polygon_feature_builder_copy_properties(
    mvt_polygon_feature_builder_t *builder, mvt_feature_t *feat) {
  builder->builder.copy_properties(feat->feat);
}

void mvt_polygon_feature_builder_copy_properties_with_mapper(
    mvt_polygon_feature_builder_t *builder, mvt_feature_t *feat,
    mvt_property_mapper_t *mapper) {
  builder->builder.copy_properties(feat->feat, mapper->mapper);
}

void mvt_polygon_feature_builder_add_ring(
    mvt_polygon_feature_builder_t *builder, int ringcont) {
  builder->builder.add_ring(ringcont);
}

void mvt_polygon_feature_builder_set_point(
    mvt_polygon_feature_builder_t *builder, const int32_t x, const int32_t y) {
  builder->builder.set_point(x, y);
}

void mvt_polygon_feature_builder_close_ring(
    mvt_polygon_feature_builder_t *builder) {
  builder->builder.close_ring();
}

void mvt_polygon_feature_builder_commit(
    mvt_polygon_feature_builder_t *builder) {
  builder->builder.commit();
}

void mvt_polygon_feature_builder_rollback(
    mvt_polygon_feature_builder_t *builder) {
  builder->builder.rollback();
}

void mvt_geometry_feature_builder_free(
    mvt_geometry_feature_builder_t *builder) {
  delete builder;
}

void mvt_geometry_feature_builder_set_id(
    mvt_geometry_feature_builder_t *builder, uint64_t id) {
  builder->builder.set_id(id);
}
void mvt_geometry_feature_builder_copy_id(
    mvt_geometry_feature_builder_t *builder, mvt_feature_t *feat) {
  builder->builder.copy_id(feat->feat);
}

void mvt_geometry_feature_builder_add_property(
    mvt_geometry_feature_builder_t *builder, mvt_property_t *property) {
  builder->builder.add_property(property->prop);
}

void mvt_geometry_feature_builder_copy_properties(
    mvt_geometry_feature_builder_t *builder, mvt_feature_t *feat) {
  builder->builder.copy_properties(feat->feat);
}

void mvt_geometry_feature_builder_copy_properties_with_mapper(
    mvt_geometry_feature_builder_t *builder, mvt_feature_t *feat,
    mvt_property_mapper_t *mapper) {
  builder->builder.copy_properties(feat->feat, mapper->mapper);
}

void mvt_geometry_feature_builder_commit(
    mvt_geometry_feature_builder_t *builder) {
  builder->builder.commit();
}

void mvt_geometry_feature_builder_rollback(
    mvt_geometry_feature_builder_t *builder) {
  builder->builder.rollback();
}

void mvt_geometry_feature_builder_set_geometry(
    mvt_geometry_feature_builder_t *builder, mvt_geometry_t *geom) {
  builder->builder.set_geometry(geom->geom);
}

mvt_key_index_t *mvt_key_index_new(mvt_layer_builder_t *layer) {
  return new mvt_key_index_t{
      vtzero::key_index<std::unordered_map>(layer->builder)};
}

void mvt_key_index_free(mvt_key_index_t *idx) { delete idx; }

uint32_t mvt_key_index_get(mvt_key_index_t *idx, const char *key) {
  return idx->idx(key).value();
}

mvt_int32_value_index_t *mvt_int32_value_index_new(mvt_layer_builder_t *layer) {
  return new mvt_int32_value_index_t{
      vtzero::value_index<vtzero::sint_value_type, int32_t, std::unordered_map>(
          layer->builder)};
}

void mvt_int32_value_index_free(mvt_int32_value_index_t *idx) { delete idx; }

uint32_t mvt_int32_value_index_get(mvt_int32_value_index_t *idx, int32_t val) {
  return idx->idx(val).value();
}

mvt_int64_value_index_t *mvt_int64_value_index_new(mvt_layer_builder_t *layer) {
  return new mvt_int64_value_index_t{
      vtzero::value_index<vtzero::sint_value_type, int64_t, std::unordered_map>(
          layer->builder)};
}

void mvt_int64_value_index_free(mvt_int64_value_index_t *idx) { delete idx; }

uint32_t mvt_int64_value_index_get(mvt_int64_value_index_t *idx, int64_t val) {
  return idx->idx(val).value();
}

mvt_uint64_value_index_t *
mvt_uint64_value_index_new(mvt_layer_builder_t *layer) {
  return new mvt_uint64_value_index_t{
      vtzero::value_index<vtzero::uint_value_type, uint64_t,
                          std::unordered_map>(layer->builder)};
}

void mvt_uint64_value_index_free(mvt_uint64_value_index_t *idx) { delete idx; }

uint32_t mvt_uint64_value_index_get(mvt_uint64_value_index_t *idx,
                                    uint64_t val) {
  return idx->idx(val).value();
}

mvt_uint32_value_index_t *
mvt_uint32_value_index_new(mvt_layer_builder_t *layer) {
  return new mvt_uint32_value_index_t{
      vtzero::value_index<vtzero::uint_value_type, uint32_t,
                          std::unordered_map>(layer->builder)};
}

void mvt_uint32_value_index_free(mvt_uint32_value_index_t *idx) { delete idx; }

uint32_t mvt_uint32_value_index_get(mvt_uint32_value_index_t *idx,
                                    uint32_t val) {
  return idx->idx(val).value();
}

mvt_float_value_index_t *mvt_float_value_index_new(mvt_layer_builder_t *layer) {
  return new mvt_float_value_index_t{
      vtzero::value_index<vtzero::float_value_type, float, std::unordered_map>(
          layer->builder)};
}

void mvt_float_value_index_free(mvt_float_value_index_t *idx) { delete idx; }

uint32_t mvt_float_value_index_get(mvt_float_value_index_t *idx, float val) {
  return idx->idx(val).value();
}

mvt_double_value_index_t *
mvt_double_value_index_new(mvt_layer_builder_t *layer) {
  return new mvt_double_value_index_t{
      vtzero::value_index<vtzero::double_value_type, double,
                          std::unordered_map>(layer->builder)};
}

void mvt_double_value_index_free(mvt_double_value_index_t *idx) { delete idx; }

uint32_t mvt_double_value_index_get(mvt_double_value_index_t *idx, double val) {
  return idx->idx(val).value();
}

mvt_string_value_index_t *
mvt_string_value_index_new(mvt_layer_builder_t *layer) {
  return new mvt_string_value_index_t{
      vtzero::value_index<vtzero::string_value_type, std::string,
                          std::unordered_map>(layer->builder)};
}

void mvt_string_value_index_free(mvt_string_value_index_t *idx) { delete idx; }

uint32_t mvt_string_value_index_get(mvt_string_value_index_t *idx,
                                    const char *val) {
  return idx->idx(val).value();
}

mvt_bool_value_index_t *mvt_bool_value_index_new(mvt_layer_builder_t *layer) {
  return new mvt_bool_value_index_t{vtzero::value_index_bool(layer->builder)};
}

void mvt_bool_value_index_free(mvt_bool_value_index_t *idx) { delete idx; }

uint32_t mvt_bool_value_index_get(mvt_bool_value_index_t *idx, _Bool val) {
  return idx->idx(val).value();
}

mvt_uint16_t_value_index_t *
mvt_uint16_t_value_index_new(mvt_layer_builder_t *layer) {
  return new mvt_uint16_t_value_index_t{
      vtzero::value_index_small_uint(layer->builder)};
}

void mvt_uint16_t_value_index_free(mvt_uint16_t_value_index_t *idx) {
  delete idx;
}

uint32_t mvt_uint16_t_value_index_get(mvt_uint16_t_value_index_t *idx,
                                      uint16_t val) {
  return idx->idx(val).value();
}

mvt_tile_object_t *mvt_tile_object_new(uint32_t z0, uint32_t x0, uint32_t y0,
                                       const char *data, size_t size) {
  return new mvt_tile_object_t{std::make_unique<vtile::tile_object>(
      z0, x0, y0, data, size, std::vector<std::string>{})};
}

void mvt_tile_object_free(mvt_tile_object_t *to) { delete to; }

void mvt_tile_object_add_layer(mvt_tile_object_t *to, const char *layer) {
  to->obj->layers.emplace_back(layer);
}

mvt_baton_t *mvt_baton_new(size_t num_tiles) {
  return new mvt_baton_t{std::make_unique<vtile::baton_type>(num_tiles)};
}

void mvt_baton_free(mvt_baton_t *baton) { delete baton; }

void mvt_baton_set_zxy(mvt_baton_t *baton, uint32_t z0, uint32_t x0,
                       uint32_t y0) {
  baton->b->x = x0;
  baton->b->y = y0;
  baton->b->z = z0;
}

void mvt_baton_set_buffer_size(mvt_baton_t *baton, int buffer_size) {
  baton->b->buffer_size = buffer_size;
}

void mvt_baton_add_tile(mvt_baton_t *baton, mvt_tile_object_t *t) {
  baton->b->tiles.emplace_back(std::move(t->obj));
}

void mvt_baton_clear_tile(mvt_baton_t *baton) { baton->b->tiles.clear(); }

char *mvt_composite(mvt_baton_t *baton, size_t *size, _Bool *error) {
  auto str = vtile::composite(std::move(baton->b), error);
  *size = str.size();
  char *result = (char *)malloc(sizeof(char) * *size);
  memcpy(result, str.c_str(), *size);
  return result;
}

mvt_property_mapper_t *mvt_property_mapper_new(mvt_layer_t *layer,
                                               mvt_layer_builder_t *builder) {
  return new mvt_property_mapper_t{
      vtzero::property_mapper(layer->l, builder->builder)};
}

void mvt_property_mapper_free(mvt_property_mapper_t *mapper) { delete mapper; }

uint32_t mvt_property_mapper_map_key(mvt_property_mapper_t *mapper,
                                     uint32_t key) {
  return mapper->mapper.map_key(key).value();
}

uint32_t mvt_property_mapper_map_value(mvt_property_mapper_t *mapper,
                                       uint32_t val) {
  return mapper->mapper.map_value(val).value();
}

void mvt_property_mapper_map_keyvalue(mvt_property_mapper_t *mapper,
                                      uint32_t key, uint32_t val,
                                      uint32_t *mkey, uint32_t *mval) {
  auto pair = mapper->mapper(vtzero::index_value_pair(key, val));
  *mkey = pair.key().value();
  *mval = pair.value().value();
}

#ifdef __cplusplus
}
#endif
