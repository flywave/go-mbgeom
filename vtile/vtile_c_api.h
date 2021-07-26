#ifndef GO_VTILE_C_API_H_
#define GO_VTILE_C_API_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define VTILECAPICALL __declspec(dllexport)
#else
#define VTILECAPICALL
#endif

typedef struct _mvt_vector_tile_t mvt_vector_tile_t;
typedef struct _mvt_layer_t mvt_layer_t;
typedef struct _mvt_feature_t mvt_feature_t;
typedef struct _mvt_property_t mvt_property_t;
typedef struct _mvt_geometry_t mvt_geometry_t;
typedef struct _mvt_property_value_t mvt_property_value_t;

typedef struct _mvt_geometry_point_t mvt_geometry_point_t;
typedef struct _mvt_geometry_linestring_t mvt_geometry_linestring_t;
typedef struct _mvt_geometry_polygon_t mvt_geometry_polygon_t;

typedef struct _mvt_property_mapper_t mvt_property_mapper_t;

typedef struct _mvt_tile_builder_t mvt_tile_builder_t;
typedef struct _mvt_layer_builder_t mvt_layer_builder_t;
typedef struct _mvt_key_index_t mvt_key_index_t;
typedef struct _mvt_int32_value_index_t mvt_int32_value_index_t;
typedef struct _mvt_int64_value_index_t mvt_int64_value_index_t;
typedef struct _mvt_uint64_value_index_t mvt_uint64_value_index_t;
typedef struct _mvt_uint32_value_index_t mvt_uint32_value_index_t;
typedef struct _mvt_float_value_index_t mvt_float_value_index_t;
typedef struct _mvt_double_value_index_t mvt_double_value_index_t;
typedef struct _mvt_string_value_index_t mvt_string_value_index_t;
typedef struct _mvt_bool_value_index_t mvt_bool_value_index_t;
typedef struct _mvt_uint16_t_value_index_t mvt_uint16_t_value_index_t;

typedef struct _mvt_point_feature_builder_t mvt_point_feature_builder_t;
typedef struct _mvt_linestring_feature_builder_t
    mvt_linestring_feature_builder_t;
typedef struct _mvt_polygon_feature_builder_t mvt_polygon_feature_builder_t;
typedef struct _mvt_geometry_feature_builder_t mvt_geometry_feature_builder_t;

typedef struct _mvt_tile_object_t mvt_tile_object_t;
typedef struct _mvt_baton_t mvt_baton_t;

VTILECAPICALL mvt_vector_tile_t *mvt_vector_tile_new(const char *data,
                                                     size_t si);
VTILECAPICALL void mvt_vector_tile_free(mvt_vector_tile_t *ctx);
VTILECAPICALL _Bool mvt_vector_tile_empty(mvt_vector_tile_t *ctx);
VTILECAPICALL size_t mvt_vector_tile_count_layers(mvt_vector_tile_t *ctx);
VTILECAPICALL mvt_layer_t *mvt_vector_tile_next_layer(mvt_vector_tile_t *ctx);
VTILECAPICALL void mvt_vector_tile_reset_layer(mvt_vector_tile_t *ctx);
VTILECAPICALL mvt_layer_t *mvt_vector_tile_get_layer(mvt_vector_tile_t *ctx,
                                                     int index);
VTILECAPICALL mvt_layer_t *
mvt_vector_tile_get_layer_by_name(mvt_vector_tile_t *ctx, const char *name);
VTILECAPICALL _Bool mvt_vector_tile_is_vector_tile(const char *data, size_t si);

VTILECAPICALL mvt_layer_t *mvt_layer_new();
VTILECAPICALL mvt_layer_t *mvt_layer_new_with_data(const char *data, size_t si);
VTILECAPICALL _Bool mvt_layer_valid(mvt_layer_t *ctx);
VTILECAPICALL const char *mvt_layer_get_data(mvt_layer_t *ctx, size_t *si);
VTILECAPICALL const char *mvt_layer_get_name(mvt_layer_t *ctx);
VTILECAPICALL uint32_t mvt_layer_version(mvt_layer_t *ctx);
VTILECAPICALL uint32_t mvt_layer_extent(mvt_layer_t *ctx);
VTILECAPICALL _Bool mvt_layer_empty(mvt_layer_t *ctx);
VTILECAPICALL size_t mvt_layer_num_features(mvt_layer_t *ctx);
VTILECAPICALL char **mvt_layer_key_table(mvt_layer_t *ctx, size_t *si);
VTILECAPICALL void mvt_layer_free_key_table(char **kts, size_t si);
VTILECAPICALL size_t mvt_layer_key_table_size(mvt_layer_t *ctx);
VTILECAPICALL mvt_property_value_t **mvt_layer_value_table(mvt_layer_t *ctx,
                                                           size_t *si);
VTILECAPICALL void mvt_layer_free_value_table(mvt_property_value_t **vts,
                                              size_t si);
VTILECAPICALL size_t mvt_layer_key_value_size(mvt_layer_t *ctx);
VTILECAPICALL char *mvt_layer_get_key(mvt_layer_t *ctx, int i);
VTILECAPICALL mvt_property_value_t *mvt_layer_get_value(mvt_layer_t *ctx,
                                                        int i);
VTILECAPICALL mvt_feature_t *mvt_vector_layer_next_feature(mvt_layer_t *ctx);
VTILECAPICALL void mvt_layer_reset_feature(mvt_layer_t *ctx);
VTILECAPICALL mvt_feature_t *
mvt_vector_layer_get_feature_by_id(mvt_layer_t *ctx, uint64_t i);

VTILECAPICALL mvt_feature_t *mvt_feature_new();
VTILECAPICALL mvt_feature_t *
mvt_feature_new_with_data(mvt_layer_t *layer, const char *data, size_t si);
VTILECAPICALL void mvt_feature_free(mvt_feature_t *ctx);
VTILECAPICALL _Bool mvt_feature_valid(mvt_feature_t *ctx);
VTILECAPICALL uint64_t mvt_feature_get_id(mvt_feature_t *ctx);
VTILECAPICALL _Bool mvt_feature_has_id(mvt_feature_t *ctx);
VTILECAPICALL uint32_t mvt_feature_get_geometry_type(mvt_feature_t *ctx);
VTILECAPICALL mvt_geometry_t *mvt_feature_get_geometry(mvt_feature_t *ctx);
VTILECAPICALL _Bool mvt_feature_empty(mvt_feature_t *ctx);
VTILECAPICALL size_t mvt_feature_num_properties(mvt_feature_t *ctx);
VTILECAPICALL mvt_property_t *mvt_feature_next_property(mvt_feature_t *ctx);
VTILECAPICALL void mvt_feature_reset_property(mvt_feature_t *ctx);
VTILECAPICALL _Bool mvt_feature_next_property_indexes(mvt_feature_t *ctx,
                                                      uint32_t *key,
                                                      uint32_t *value);

VTILECAPICALL mvt_property_t *mvt_property_new();
VTILECAPICALL mvt_property_t *
mvt_property_new_with_keyvalue(const char *key, mvt_property_value_t *value);
VTILECAPICALL void mvt_property_free(mvt_property_t *prop);
VTILECAPICALL _Bool mvt_property_valid(mvt_property_t *prop);
VTILECAPICALL char *mvt_feature_get_key(mvt_property_t *prop);
VTILECAPICALL mvt_property_value_t *mvt_feature_get_value(mvt_property_t *prop);

VTILECAPICALL mvt_property_value_t *mvt_property_value_new();
VTILECAPICALL mvt_property_value_t *
mvt_property_value_new_with_data(const char *data, size_t si);
VTILECAPICALL void mvt_property_value_free(mvt_property_value_t *pv);
VTILECAPICALL _Bool mvt_property_value_valid(mvt_property_value_t *pv);
VTILECAPICALL uint32_t mvt_property_value_get_type(mvt_property_value_t *pv);
VTILECAPICALL const char *mvt_property_value_get_data(mvt_property_value_t *pv,
                                                      size_t *si);
VTILECAPICALL const char *
mvt_property_value_get_string(mvt_property_value_t *pv);
VTILECAPICALL float mvt_property_value_get_float(mvt_property_value_t *pv);
VTILECAPICALL double mvt_property_value_get_double(mvt_property_value_t *pv);
VTILECAPICALL int64_t mvt_property_value_get_int(mvt_property_value_t *pv);
VTILECAPICALL uint64_t mvt_property_value_get_uint(mvt_property_value_t *pv);
VTILECAPICALL int64_t mvt_property_value_get_sint(mvt_property_value_t *pv);
VTILECAPICALL bool mvt_property_value_get_bool(mvt_property_value_t *pv);

VTILECAPICALL mvt_geometry_t *mvt_geometry_new();
VTILECAPICALL mvt_geometry_t *
mvt_geometry_new_with_data(const char *data, size_t si, uint32_t type);
VTILECAPICALL void mvt_geometry_free(mvt_geometry_t *geom);
VTILECAPICALL uint32_t mvt_geometry_get_type(mvt_geometry_t *geom);
VTILECAPICALL const char *mvt_geometry_get_data(mvt_geometry_t *geom,
                                                size_t *si);
VTILECAPICALL mvt_geometry_point_t *
mvt_geometry_decode_point_geometry(mvt_geometry_t *geom);
VTILECAPICALL mvt_geometry_linestring_t *
mvt_geometry_decode_linestring_geometry(mvt_geometry_t *geom);
VTILECAPICALL mvt_geometry_polygon_t *
mvt_geometry_decode_polygon_geometry(mvt_geometry_t *geom);

VTILECAPICALL void mvt_geometry_point_free(mvt_geometry_point_t *point);
VTILECAPICALL size_t mvt_geometry_point_count(mvt_geometry_point_t *point);
VTILECAPICALL size_t mvt_geometry_point_get_points(mvt_geometry_point_t *point,
                                                   int32_t *xylist,
                                                   size_t count);

VTILECAPICALL void mvt_geometry_linestring_free(mvt_geometry_linestring_t *ls);
VTILECAPICALL size_t
mvt_geometry_linestring_count(mvt_geometry_linestring_t *ls);
VTILECAPICALL size_t mvt_geometry_linestring_get_lines(
    mvt_geometry_linestring_t *ls, mvt_geometry_point_t *ptlist, size_t count);

VTILECAPICALL void mvt_geometry_polygon_free(mvt_geometry_polygon_t *poly);
VTILECAPICALL size_t mvt_geometry_polygon_count(mvt_geometry_polygon_t *poly);
VTILECAPICALL size_t mvt_geometry_polygon_get_lines(
    mvt_geometry_polygon_t *poly, mvt_geometry_point_t *ptlist, size_t count);

VTILECAPICALL mvt_tile_builder_t *mvt_tile_builder_new();
VTILECAPICALL void mvt_tile_builder_free(mvt_tile_builder_t *tb);
VTILECAPICALL void mvt_tile_builder_add_existing_layer(mvt_tile_builder_t *tb,
                                                       mvt_layer_t *layer);
VTILECAPICALL char *mvt_tile_builder_serialize(mvt_tile_builder_t *tb,
                                               size_t *si);
VTILECAPICALL mvt_layer_builder_t *
mvt_tile_builder_get_layer_builder(mvt_tile_builder_t *tb, const char *name,
                                   uint32_t version, uint32_t extent);

VTILECAPICALL void mvt_layer_builder_free(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_layer_builder_add_key(mvt_layer_builder_t *layer,
                                             const char *name);
VTILECAPICALL void mvt_layer_builder_add_value(mvt_layer_builder_t *layer,
                                               mvt_property_value_t *value);
VTILECAPICALL void mvt_layer_builder_add_feature(mvt_layer_builder_t *layer,
                                                 mvt_feature_t *feat);
VTILECAPICALL mvt_point_feature_builder_t *
mvt_layer_builder_get_point_feature_builder(mvt_layer_builder_t *layer);
VTILECAPICALL mvt_linestring_feature_builder_t *
mvt_layer_builder_get_linestring_feature_builder(mvt_layer_builder_t *layer);
VTILECAPICALL mvt_polygon_feature_builder_t *
mvt_layer_builder_get_polygon_feature_builder(mvt_layer_builder_t *layer);
VTILECAPICALL mvt_geometry_feature_builder_t *
mvt_layer_builder_get_geometry_feature_builder(mvt_layer_builder_t *layer);

VTILECAPICALL void
mvt_point_feature_builder_free(mvt_point_feature_builder_t *builder);
VTILECAPICALL void
mvt_point_feature_builder_set_id(mvt_point_feature_builder_t *builder,
                                 uint64_t id);
VTILECAPICALL void
mvt_point_feature_builder_copy_id(mvt_point_feature_builder_t *builder,
                                  mvt_feature_t *feat);
VTILECAPICALL void
mvt_point_feature_builder_add_property(mvt_point_feature_builder_t *builder,
                                       mvt_property_t *property);
VTILECAPICALL void
mvt_point_feature_builder_copy_property(mvt_point_feature_builder_t *builder,
                                        mvt_feature_t *feat);
VTILECAPICALL void mvt_point_feature_builder_copy_property_with_mapper(
    mvt_point_feature_builder_t *builder, mvt_feature_t *feat,
    mvt_property_mapper_t *mapper);

VTILECAPICALL void
mvt_point_feature_builder_commit(mvt_point_feature_builder_t *builder);
VTILECAPICALL void
mvt_point_feature_builder_rollback(mvt_point_feature_builder_t *builder);

VTILECAPICALL void
mvt_point_feature_builder_add_point(mvt_point_feature_builder_t *builder,
                                    const int32_t x, const int32_t y);
VTILECAPICALL void
mvt_point_feature_builder_set_point(mvt_point_feature_builder_t *builder,
                                    const int32_t x, const int32_t y);

VTILECAPICALL void
mvt_linestring_feature_builder_free(mvt_linestring_feature_builder_t *builder);
VTILECAPICALL void
mvt_linestring_feature_builder_set_id(mvt_linestring_feature_builder_t *builder,
                                      uint64_t id);
VTILECAPICALL void mvt_linestring_feature_builder_copy_id(
    mvt_linestring_feature_builder_t *builder, mvt_feature_t *feat);
VTILECAPICALL void mvt_linestring_feature_builder_add_property(
    mvt_linestring_feature_builder_t *builder, mvt_property_t *property);
VTILECAPICALL void mvt_linestring_feature_builder_copy_property(
    mvt_linestring_feature_builder_t *builder, mvt_feature_t *feat);
VTILECAPICALL void mvt_linestring_feature_builder_commit(
    mvt_linestring_feature_builder_t *builder);
VTILECAPICALL void mvt_linestring_feature_builder_rollback(
    mvt_linestring_feature_builder_t *builder);
VTILECAPICALL void mvt_linestring_feature_builder_add_linestring(
    mvt_linestring_feature_builder_t *builder, int linecount);
VTILECAPICALL void mvt_linestring_feature_builder_set_point(
    mvt_linestring_feature_builder_t *builder, const int32_t x,
    const int32_t y);
VTILECAPICALL void mvt_linestring_feature_builder_copy_property_with_mapper(
    mvt_linestring_feature_builder_t *builder, mvt_feature_t *feat,
    mvt_property_mapper_t *mapper);
VTILECAPICALL void
mvt_polygon_feature_builder_free(mvt_polygon_feature_builder_t *builder);
VTILECAPICALL void
mvt_polygon_feature_builder_set_id(mvt_polygon_feature_builder_t *builder,
                                   uint64_t id);
VTILECAPICALL void
mvt_polygon_feature_builder_copy_id(mvt_polygon_feature_builder_t *builder,
                                    mvt_feature_t *feat);
VTILECAPICALL void
mvt_polygon_feature_builder_add_property(mvt_polygon_feature_builder_t *builder,
                                         mvt_property_t *property);
VTILECAPICALL void mvt_polygon_feature_builder_copy_property(
    mvt_polygon_feature_builder_t *builder, mvt_feature_t *feat);
VTILECAPICALL void mvt_polygon_feature_builder_copy_property_with_mapper(
    mvt_polygon_feature_builder_t *builder, mvt_feature_t *feat,
    mvt_property_mapper_t *mapper);
VTILECAPICALL void
mvt_polygon_feature_builder_commit(mvt_polygon_feature_builder_t *builder);
VTILECAPICALL void
mvt_polygon_feature_builder_rollback(mvt_polygon_feature_builder_t *builder);
VTILECAPICALL void
mvt_polygon_feature_builder_add_ring(mvt_polygon_feature_builder_t *builder,
                                     int ringcont);
VTILECAPICALL void
mvt_polygon_feature_builder_set_point(mvt_polygon_feature_builder_t *builder,
                                      const int32_t x, const int32_t y);
VTILECAPICALL void
mvt_polygon_feature_builder_close_ring(mvt_polygon_feature_builder_t *builder);

VTILECAPICALL void
mvt_geometry_feature_builder_free(mvt_geometry_feature_builder_t *builder);
VTILECAPICALL void
mvt_geometry_feature_builder_set_id(mvt_geometry_feature_builder_t *builder,
                                    uint64_t id);
VTILECAPICALL void
mvt_geometry_feature_builder_copy_id(mvt_geometry_feature_builder_t *builder,
                                     mvt_feature_t *feat);
VTILECAPICALL void mvt_geometry_feature_builder_add_property(
    mvt_geometry_feature_builder_t *builder, mvt_property_t *property);
VTILECAPICALL void mvt_geometry_feature_builder_copy_property(
    mvt_geometry_feature_builder_t *builder, mvt_feature_t *feat);
VTILECAPICALL void mvt_geometry_feature_builder_copy_property_with_mapper(
    mvt_geometry_feature_builder_t *builder, mvt_feature_t *feat,
    mvt_property_mapper_t *mapper);
VTILECAPICALL void
mvt_geometry_feature_builder_commit(mvt_geometry_feature_builder_t *builder);
VTILECAPICALL void
mvt_geometry_feature_builder_rollback(mvt_geometry_feature_builder_t *builder);

VTILECAPICALL void mvt_geometry_feature_builder_set_geometry(
    mvt_geometry_feature_builder_t *builder, mvt_geometry_t *geom);

VTILECAPICALL mvt_key_index_t *mvt_key_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_key_index_free(mvt_key_index_t *idx);
VTILECAPICALL uint32_t mvt_key_index_get(mvt_key_index_t *idx, const char *ket);

VTILECAPICALL mvt_int32_value_index_t *
mvt_int32_value_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_int32_value_index_free(mvt_int32_value_index_t *idx);
VTILECAPICALL uint32_t mvt_int32_value_index_get(mvt_int32_value_index_t *idx,
                                                 int32_t val);

VTILECAPICALL mvt_int64_value_index_t *
mvt_int64_value_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_int64_value_index_free(mvt_int64_value_index_t *idx);
VTILECAPICALL uint32_t mvt_int64_value_index_get(mvt_int64_value_index_t *idx,
                                                 int64_t val);

VTILECAPICALL mvt_uint64_value_index_t *
mvt_uint64_value_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_uint64_value_index_free(mvt_uint64_value_index_t *idx);
VTILECAPICALL uint32_t mvt_uint64_value_index_get(mvt_uint64_value_index_t *idx,
                                                  uint64_t val);

VTILECAPICALL mvt_uint32_value_index_t *
mvt_uint32_value_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_uint32_value_index_free(mvt_uint32_value_index_t *idx);
VTILECAPICALL uint32_t mvt_uint32_value_index_get(mvt_uint32_value_index_t *idx,
                                                  uint32_t val);

VTILECAPICALL mvt_float_value_index_t *
mvt_float_value_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_float_value_index_free(mvt_float_value_index_t *idx);
VTILECAPICALL uint32_t mvt_float_value_index_get(mvt_float_value_index_t *idx,
                                                 float val);

VTILECAPICALL mvt_double_value_index_t *
mvt_double_value_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_double_value_index_free(mvt_double_value_index_t *idx);
VTILECAPICALL uint32_t mvt_double_value_index_get(mvt_double_value_index_t *idx,
                                                  double val);

VTILECAPICALL mvt_string_value_index_t *
mvt_string_value_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_string_value_index_free(mvt_string_value_index_t *idx);
VTILECAPICALL uint32_t mvt_string_value_index_get(mvt_string_value_index_t *idx,
                                                  const char *val);

VTILECAPICALL mvt_bool_value_index_t *
mvt_bool_value_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void mvt_bool_value_index_free(mvt_bool_value_index_t *idx);
VTILECAPICALL uint32_t mvt_bool_value_index_get(mvt_bool_value_index_t *idx,
                                                _Bool val);

VTILECAPICALL mvt_uint16_t_value_index_t *
mvt_uint16_t_value_index_new(mvt_layer_builder_t *layer);
VTILECAPICALL void
mvt_uint16_t_value_index_free(mvt_uint16_t_value_index_t *idx);
VTILECAPICALL uint32_t
mvt_uint16_t_value_index_get(mvt_uint16_t_value_index_t *idx, uint16_t val);

VTILECAPICALL mvt_tile_object_t *mvt_tile_object_new(uint32_t z0, uint32_t x0,
                                                     uint32_t y0,
                                                     const char *data,
                                                     size_t size);
VTILECAPICALL void mvt_tile_object_free(mvt_tile_object_t *to);
VTILECAPICALL void mvt_tile_object_add_layer(mvt_tile_object_t *to,
                                             const char *layer);

VTILECAPICALL mvt_baton_t *mvt_baton_new(size_t num_tiles);
VTILECAPICALL void mvt_baton_free(mvt_baton_t *baton);
VTILECAPICALL void mvt_baton_set_zxy(mvt_baton_t *baton, uint32_t z0,
                                     uint32_t x0, uint32_t y0);
VTILECAPICALL void mvt_baton_set_buffer_size(mvt_baton_t *baton,
                                             int buffer_size);
VTILECAPICALL void mvt_baton_add_tile(mvt_baton_t *baton, mvt_tile_object_t *t);
VTILECAPICALL void mvt_baton_clear_tile(mvt_baton_t *baton);

VTILECAPICALL char *mvt_composite(mvt_baton_t *baton, size_t *size,
                                  _Bool *error);

VTILECAPICALL mvt_property_mapper_t *
mvt_property_mapper_new(mvt_layer_t *layer, mvt_layer_builder_t *builder);
VTILECAPICALL void mvt_property_mapper_free(mvt_property_mapper_t *mapper);
VTILECAPICALL uint32_t
mvt_property_mapper_map_key(mvt_property_mapper_t *mapper, uint32_t key);
VTILECAPICALL uint32_t
mvt_property_mapper_map_value(mvt_property_mapper_t *mapper, uint32_t val);
VTILECAPICALL void
mvt_property_mapper_map_keyvalue(mvt_property_mapper_t *mapper, uint32_t key,
                                 uint32_t val, uint32_t *mkey, uint32_t *mval);

#ifdef __cplusplus
}
#endif

#endif