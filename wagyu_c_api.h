#ifndef GO_WAGYU_C_API_H_
#define GO_WAGYU_C_API_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define WAGYUCAPICALL __declspec(dllexport)
#else
#define WAGYUCAPICALL
#endif

typedef struct _mapbox_box_t mapbox_box_t;
typedef struct _mapbox_value_t mapbox_value_t;
typedef struct _mapbox_property_map_t mapbox_property_map_t;
typedef struct _mapbox_point_t mapbox_point_t;
typedef struct _mapbox_line_string_t mapbox_line_string_t;
typedef struct _mapbox_linear_ring_t mapbox_linear_ring_t;
typedef struct _mapbox_polygon_t mapbox_polygon_t;
typedef struct _mapbox_multi_point_t mapbox_multi_point_t;
typedef struct _mapbox_multi_line_string_t mapbox_multi_line_string_t;
typedef struct _mapbox_multi_polygon_t mapbox_multi_polygon_t;
typedef struct _mapbox_geometry_collection_t mapbox_geometry_collection_t;
typedef struct _mapbox_geometry_t mapbox_geometry_t;
typedef struct _mapbox_feature_t mapbox_feature_t;
typedef struct _mapbox_identifier_t mapbox_identifier_t;
typedef struct _mapbox_feature_collection_t mapbox_feature_collection_t;

typedef struct _mapbox_wagyu_t mapbox_wagyu_t;

WAGYUCAPICALL mapbox_box_t *mapbox_box_new(mapbox_point_t *min,
                                           mapbox_point_t *max);
WAGYUCAPICALL void mapbox_box_free(mapbox_box_t *box);
WAGYUCAPICALL mapbox_point_t *mapbox_box_get_min(mapbox_box_t *box);
WAGYUCAPICALL mapbox_point_t *mapbox_box_get_max(mapbox_box_t *box);
WAGYUCAPICALL mapbox_box_t *mapbox_box_envelope(mapbox_geometry_t *geom);

WAGYUCAPICALL mapbox_point_t *mapbox_point_new(double x, double y);
WAGYUCAPICALL void mapbox_point_free(mapbox_point_t *pt);
WAGYUCAPICALL double mapbox_point_get_x(mapbox_point_t *pt);
WAGYUCAPICALL double mapbox_point_get_y(mapbox_point_t *pt);
WAGYUCAPICALL void mapbox_point_get_xy(mapbox_point_t *pt, double *x,
                                       double *y);
WAGYUCAPICALL void mapbox_point_set_xy(mapbox_point_t *pt, double x, double y);
WAGYUCAPICALL mapbox_geometry_t *mapbox_point_to_geometry(mapbox_point_t *pt);
WAGYUCAPICALL bool mapbox_point_equal(mapbox_point_t *geom1,
                                      mapbox_point_t *geom2);

WAGYUCAPICALL mapbox_line_string_t *mapbox_line_string_new(double *x, double *y,
                                                           int pointcount);
WAGYUCAPICALL void mapbox_line_string_free(mapbox_line_string_t *pt);
WAGYUCAPICALL int mapbox_line_string_get_points_count(mapbox_line_string_t *pt);
WAGYUCAPICALL mapbox_point_t *
mapbox_line_string_get_point(mapbox_line_string_t *pt, int i);
WAGYUCAPICALL void mapbox_line_string_update_point(mapbox_line_string_t *pt,
                                                   int i, double x, double y);
WAGYUCAPICALL void mapbox_line_string_append_point(mapbox_line_string_t *pt,
                                                   double x, double y);
WAGYUCAPICALL mapbox_geometry_t *
mapbox_line_string_to_geometry(mapbox_line_string_t *pt);
WAGYUCAPICALL bool mapbox_line_string_equal(mapbox_line_string_t *geom1,
                                            mapbox_line_string_t *geom2);

WAGYUCAPICALL mapbox_multi_point_t *mapbox_multi_point_new(double *x, double *y,
                                                           int pointcount);
WAGYUCAPICALL void mapbox_multi_point_free(mapbox_multi_point_t *pt);
WAGYUCAPICALL int mapbox_multi_point_get_points_count(mapbox_multi_point_t *pt);
WAGYUCAPICALL void mapbox_multi_point_update_point(mapbox_multi_point_t *pt,
                                                   int i, double x, double y);
WAGYUCAPICALL void mapbox_multi_point_append_point(mapbox_multi_point_t *pt,
                                                   double x, double y);
WAGYUCAPICALL mapbox_point_t *
mapbox_multi_point_get_point(mapbox_multi_point_t *pt, int i);
WAGYUCAPICALL mapbox_geometry_t *
mapbox_multi_point_to_geometry(mapbox_multi_point_t *pt);
WAGYUCAPICALL bool mapbox_multi_point_equal(mapbox_multi_point_t *geom1,
                                            mapbox_multi_point_t *geom2);

WAGYUCAPICALL mapbox_linear_ring_t *mapbox_linear_ring_new(double *x, double *y,
                                                           int pointcount);
WAGYUCAPICALL void mapbox_linear_ring_free(mapbox_linear_ring_t *pt);
WAGYUCAPICALL int mapbox_linear_ring_get_points_count(mapbox_linear_ring_t *pt);
WAGYUCAPICALL void mapbox_linear_ring_update_point(mapbox_linear_ring_t *pt,
                                                   int i, double x, double y);
WAGYUCAPICALL void mapbox_linear_ring_append_point(mapbox_linear_ring_t *pt,
                                                   double x, double y);
WAGYUCAPICALL mapbox_point_t *
mapbox_linear_ring_get_point(mapbox_linear_ring_t *pt, int i);
WAGYUCAPICALL bool mapbox_linear_ring_equal(mapbox_linear_ring_t *geom1,
                                            mapbox_linear_ring_t *geom2);

WAGYUCAPICALL mapbox_polygon_t *mapbox_polygon_new(mapbox_linear_ring_t *rings,
                                                   int ringcount);
WAGYUCAPICALL void mapbox_polygon_free(mapbox_polygon_t *pt);
WAGYUCAPICALL mapbox_linear_ring_t *
mapbox_polygon_get_exterior(mapbox_polygon_t *pt);
WAGYUCAPICALL void mapbox_polygon_set_exterior(mapbox_polygon_t *pt,
                                               mapbox_linear_ring_t *ring);
WAGYUCAPICALL int mapbox_polygon_get_interior_count(mapbox_polygon_t *pt);
WAGYUCAPICALL void
mapbox_polygon_append_interior_ring(mapbox_polygon_t *pt,
                                    mapbox_linear_ring_t *ring);
WAGYUCAPICALL void
mapbox_polygon_update_interior_ring(mapbox_polygon_t *pt, int i,
                                    mapbox_linear_ring_t *ring);
WAGYUCAPICALL mapbox_linear_ring_t *
mapbox_polygon_get_interior(mapbox_polygon_t *pt, int i);
WAGYUCAPICALL mapbox_geometry_t *
mapbox_polygon_to_geometry(mapbox_polygon_t *pt);
WAGYUCAPICALL bool mapbox_polygon_equal(mapbox_polygon_t *geom1,
                                        mapbox_polygon_t *geom2);

WAGYUCAPICALL mapbox_multi_line_string_t *
mapbox_multi_line_string_new(mapbox_line_string_t *lines, int ringcount);
WAGYUCAPICALL void
mapbox_multi_line_string_free(mapbox_multi_line_string_t *pt);
WAGYUCAPICALL void
mapbox_multi_line_string_append(mapbox_multi_line_string_t *pt,
                                mapbox_line_string_t *line);
WAGYUCAPICALL void
mapbox_multi_line_string_update(mapbox_multi_line_string_t *pt, int i,
                                mapbox_line_string_t *line);
WAGYUCAPICALL int mapbox_multi_line_get_count(mapbox_multi_line_string_t *pt);
WAGYUCAPICALL mapbox_line_string_t *
mapbox_multi_line_string_get(mapbox_multi_line_string_t *pt, int i);
WAGYUCAPICALL mapbox_geometry_t *
mapbox_multi_line_string_to_geometry(mapbox_multi_line_string_t *pt);
WAGYUCAPICALL bool
mapbox_multi_line_string_equal(mapbox_multi_line_string_t *geom1,
                               mapbox_multi_line_string_t *geom2);

WAGYUCAPICALL mapbox_multi_polygon_t *
mapbox_multi_polygon_new(mapbox_polygon_t *lines, int ringcount);
WAGYUCAPICALL void mapbox_multi_polygon_free(mapbox_multi_polygon_t *pt);
WAGYUCAPICALL void mapbox_multi_polygon_append(mapbox_multi_polygon_t *pt,
                                               mapbox_polygon_t *line);
WAGYUCAPICALL void mapbox_multi_polygon_update(mapbox_multi_polygon_t *pt,
                                               int i, mapbox_polygon_t *line);
WAGYUCAPICALL int mapbox_multi_polygon_get_count(mapbox_multi_polygon_t *pt);
WAGYUCAPICALL mapbox_polygon_t *
mapbox_multi_polygon_get(mapbox_multi_polygon_t *pt, int i);
WAGYUCAPICALL mapbox_geometry_t *
mapbox_multi_polygon_to_geometry(mapbox_multi_polygon_t *pt);
WAGYUCAPICALL bool mapbox_multi_polygon_equal(mapbox_multi_polygon_t *geom1,
                                              mapbox_multi_polygon_t *geom2);

WAGYUCAPICALL void mapbox_geometry_free(mapbox_geometry_t *geom);
WAGYUCAPICALL _Bool mapbox_geometry_empty(mapbox_geometry_t *geom);
WAGYUCAPICALL _Bool mapbox_geometry_is_point(mapbox_geometry_t *geom);
WAGYUCAPICALL _Bool mapbox_geometry_is_line_string(mapbox_geometry_t *geom);
WAGYUCAPICALL _Bool mapbox_geometry_is_polygon(mapbox_geometry_t *geom);
WAGYUCAPICALL _Bool mapbox_geometry_is_multi_point(mapbox_geometry_t *geom);
WAGYUCAPICALL _Bool
mapbox_geometry_is_multi_line_string(mapbox_geometry_t *geom);
WAGYUCAPICALL _Bool mapbox_geometry_is_multi_polygon(mapbox_geometry_t *geom);
WAGYUCAPICALL mapbox_point_t *
mapbox_geometry_cast_point(mapbox_geometry_t *geom);
WAGYUCAPICALL mapbox_line_string_t *
mapbox_geometry_cast_line_string(mapbox_geometry_t *geom);
WAGYUCAPICALL mapbox_polygon_t *
mapbox_geometry_cast_polygon(mapbox_geometry_t *geom);
WAGYUCAPICALL mapbox_multi_point_t *
mapbox_geometry_cast_multi_point(mapbox_geometry_t *geom);
WAGYUCAPICALL mapbox_multi_line_string_t *
mapbox_geometry_cast_multi_line_string(mapbox_geometry_t *geom);
WAGYUCAPICALL mapbox_multi_polygon_t *
mapbox_geometry_cast_multi_polygon(mapbox_geometry_t *geom);
WAGYUCAPICALL bool mapbox_geometry_equal(mapbox_geometry_t *geom1,
                                         mapbox_geometry_t *geom2);

WAGYUCAPICALL mapbox_geometry_collection_t *mapbox_geometry_collection_new();
WAGYUCAPICALL void
mapbox_geometry_collection_free(mapbox_geometry_collection_t *geom);
WAGYUCAPICALL _Bool
mapbox_geometry_collection_empty(mapbox_geometry_collection_t *gc);
WAGYUCAPICALL void
mapbox_geometry_collection_append(mapbox_geometry_collection_t *gc,
                                  mapbox_geometry_t *geom);
WAGYUCAPICALL void
mapbox_geometry_collection_update(mapbox_geometry_collection_t *gc, int i,
                                  mapbox_geometry_t *geom);
WAGYUCAPICALL int
mapbox_geometry_collection_get_count(mapbox_geometry_collection_t *gc);
WAGYUCAPICALL mapbox_geometry_t *
mapbox_geometry_collection_get(mapbox_geometry_collection_t *gc, int i);

WAGYUCAPICALL mapbox_value_t *mapbox_value_new();
WAGYUCAPICALL void mapbox_value_free(mapbox_value_t *val);
WAGYUCAPICALL mapbox_value_t *mapbox_value_from_bool(_Bool v);
WAGYUCAPICALL mapbox_value_t *mapbox_value_from_uint(uint64_t v);
WAGYUCAPICALL mapbox_value_t *mapbox_value_from_int(int64_t v);
WAGYUCAPICALL mapbox_value_t *mapbox_value_from_double(double v);
WAGYUCAPICALL mapbox_value_t *mapbox_value_from_string(const char *v);
WAGYUCAPICALL mapbox_value_t *mapbox_value_from_values(mapbox_value_t *vs,
                                                       int valuecount);
WAGYUCAPICALL mapbox_value_t *mapbox_value_from_keyvalues(const char **ks,
                                                          mapbox_value_t *vs,
                                                          int valuecount);
WAGYUCAPICALL _Bool mapbox_value_is_empty(mapbox_value_t *geom);
WAGYUCAPICALL _Bool mapbox_value_is_null(mapbox_value_t *geom);
WAGYUCAPICALL _Bool mapbox_value_is_bool(mapbox_value_t *geom);
WAGYUCAPICALL _Bool mapbox_value_is_uint(mapbox_value_t *geom);
WAGYUCAPICALL _Bool mapbox_value_is_int(mapbox_value_t *geom);
WAGYUCAPICALL _Bool mapbox_value_is_double(mapbox_value_t *geom);
WAGYUCAPICALL _Bool mapbox_value_is_string(mapbox_value_t *geom);
WAGYUCAPICALL _Bool mapbox_value_is_vector(mapbox_value_t *geom);
WAGYUCAPICALL _Bool mapbox_value_is_map(mapbox_value_t *geom);
WAGYUCAPICALL _Bool mapbox_value_cast_bool(mapbox_value_t *geom);
WAGYUCAPICALL uint64_t mapbox_value_cast_uint(mapbox_value_t *geom);
WAGYUCAPICALL int64_t mapbox_value_cast_int(mapbox_value_t *geom);
WAGYUCAPICALL double mapbox_value_cast_double(mapbox_value_t *geom);
WAGYUCAPICALL char *mapbox_value_cast_string(mapbox_value_t *geom);
WAGYUCAPICALL mapbox_value_t *mapbox_value_cast_vector(mapbox_value_t *geom,
                                                       int *count);
WAGYUCAPICALL void mapbox_values_free(mapbox_value_t *vs);
WAGYUCAPICALL mapbox_property_map_t *
mapbox_value_cast_map(mapbox_value_t *geom);

WAGYUCAPICALL mapbox_property_map_t *mapbox_property_map_new();
WAGYUCAPICALL void mapbox_property_map_free(mapbox_property_map_t *val);
WAGYUCAPICALL mapbox_value_t *
mapbox_property_map_get(mapbox_property_map_t *val, const char *key);
WAGYUCAPICALL void mapbox_property_map_set(mapbox_property_map_t *val,
                                           const char *key, mapbox_value_t *v);
WAGYUCAPICALL _Bool mapbox_property_map_has(mapbox_property_map_t *val,
                                            const char *key);
WAGYUCAPICALL _Bool mapbox_property_map_empty(mapbox_property_map_t *val);

WAGYUCAPICALL mapbox_identifier_t *mapbox_identifier_from_uint(uint64_t v);
WAGYUCAPICALL mapbox_identifier_t *mapbox_identifier_from_int(int64_t v);
WAGYUCAPICALL mapbox_identifier_t *mapbox_identifier_from_double(double v);
WAGYUCAPICALL mapbox_identifier_t *mapbox_identifier_from_string(const char *v);
WAGYUCAPICALL void mapbox_identifier_free(mapbox_identifier_t *val);
WAGYUCAPICALL _Bool mapbox_identifier_is_uint(mapbox_identifier_t *geom);
WAGYUCAPICALL _Bool mapbox_identifier_is_int(mapbox_identifier_t *geom);
WAGYUCAPICALL _Bool mapbox_identifier_is_double(mapbox_identifier_t *geom);
WAGYUCAPICALL _Bool mapbox_identifier_is_string(mapbox_identifier_t *geom);
WAGYUCAPICALL uint64_t mapbox_identifier_cast_uint(mapbox_identifier_t *geom);
WAGYUCAPICALL int64_t mapbox_identifier_cast_int(mapbox_identifier_t *geom);
WAGYUCAPICALL double mapbox_identifier_cast_double(mapbox_identifier_t *geom);
WAGYUCAPICALL char *mapbox_identifier_cast_string(mapbox_identifier_t *geom);

WAGYUCAPICALL mapbox_feature_t *mapbox_feature_new(mapbox_geometry_t *geom);
WAGYUCAPICALL mapbox_feature_t *
mapbox_feature_create(mapbox_identifier_t *id, mapbox_geometry_t *geom,
                      mapbox_property_map_t *props);
WAGYUCAPICALL void mapbox_feature_set_identifier(mapbox_feature_t *feat,
                                                 mapbox_identifier_t *id);
WAGYUCAPICALL void mapbox_feature_set_geometry(mapbox_feature_t *feat,
                                               mapbox_geometry_t *geom);
WAGYUCAPICALL void
mapbox_feature_set_property_map(mapbox_feature_t *feat,
                                mapbox_property_map_t *props);
WAGYUCAPICALL mapbox_identifier_t *
mapbox_feature_get_identifier(mapbox_feature_t *feat);
WAGYUCAPICALL mapbox_geometry_t *
mapbox_feature_get_geometry(mapbox_feature_t *feat);
WAGYUCAPICALL mapbox_property_map_t *
mapbox_feature_get_property_map(mapbox_feature_t *feat);
WAGYUCAPICALL bool mapbox_feature_equal(mapbox_feature_t *feat1,
                                        mapbox_feature_t *feat2);

WAGYUCAPICALL mapbox_feature_collection_t *mapbox_feature_collection_new();
WAGYUCAPICALL void
mapbox_feature_collection_free(mapbox_feature_collection_t *featc);
WAGYUCAPICALL _Bool
mapbox_feature_collection_empty(mapbox_feature_collection_t *gc);
WAGYUCAPICALL void
mapbox_feature_collection_append(mapbox_feature_collection_t *gc,
                                 mapbox_feature_t *feat);
WAGYUCAPICALL void
mapbox_feature_collection_update(mapbox_feature_collection_t *gc, int i,
                                 mapbox_feature_t *feat);
WAGYUCAPICALL int
mapbox_feature_collection_get_count(mapbox_feature_collection_t *gc);
WAGYUCAPICALL mapbox_feature_t *
mapbox_feature_collection_get(mapbox_feature_collection_t *gc, int i);

WAGYUCAPICALL mapbox_wagyu_t *mapbox_wagyu_new();
WAGYUCAPICALL void mapbox_wagyu_free(mapbox_wagyu_t *ctx);
WAGYUCAPICALL void mapbox_wagyu_add_ring(mapbox_wagyu_t *ctx,
                                         mapbox_linear_ring_t *ring,
                                         uint8_t p_type);
WAGYUCAPICALL void mapbox_wagyu_add_polygon(mapbox_wagyu_t *ctx,
                                            mapbox_polygon_t *poly,
                                            uint8_t p_type);
WAGYUCAPICALL void mapbox_wagyu_reverse_rings(mapbox_wagyu_t *ctx, _Bool value);
WAGYUCAPICALL void mapbox_wagyu_clear(mapbox_wagyu_t *ctx);
WAGYUCAPICALL mapbox_box_t *mapbox_wagyu_get_bounds(mapbox_wagyu_t *ctx);
WAGYUCAPICALL _Bool mapbox_wagyu_execute(mapbox_wagyu_t *ctx, uint8_t tp,
                                         mapbox_multi_polygon_t *mp,
                                         uint8_t subject_fill_type,
                                         uint8_t clip_fill_type);

#ifdef __cplusplus
}
#endif

#endif