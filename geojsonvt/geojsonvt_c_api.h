#ifndef GO_GEOJSONVT_C_API_H_
#define GO_GEOJSONVT_C_API_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define GEOJSONVTCAPICALL __declspec(dllexport)
#else
#define GEOJSONVTCAPICALL
#endif

typedef struct _mapbox_feature_collection_t mapbox_feature_collection_t;

typedef struct _geojsonvt_box_t geojsonvt_box_t;
typedef struct _geojsonvt_value_t geojsonvt_value_t;
typedef struct _geojsonvt_property_map_t geojsonvt_property_map_t;
typedef struct _geojsonvt_point_t geojsonvt_point_t;
typedef struct _geojsonvt_line_string_t geojsonvt_line_string_t;
typedef struct _geojsonvt_linear_ring_t geojsonvt_linear_ring_t;
typedef struct _geojsonvt_polygon_t geojsonvt_polygon_t;
typedef struct _geojsonvt_multi_point_t geojsonvt_multi_point_t;
typedef struct _geojsonvt_multi_line_string_t geojsonvt_multi_line_string_t;
typedef struct _geojsonvt_multi_polygon_t geojsonvt_multi_polygon_t;
typedef struct _geojsonvt_geometry_collection_t geojsonvt_geometry_collection_t;
typedef struct _geojsonvt_geometry_t geojsonvt_geometry_t;
typedef struct _geojsonvt_feature_t geojsonvt_feature_t;
typedef struct _geojsonvt_identifier_t geojsonvt_identifier_t;
typedef struct _geojsonvt_feature_collection_t geojsonvt_feature_collection_t;

typedef struct _geojsonvt_tile_t geojsonvt_tile_t;
typedef struct _geojsonvt_t geojsonvt_t;

GEOJSONVTCAPICALL geojsonvt_box_t *geojsonvt_box_new(geojsonvt_point_t *min,
                                                     geojsonvt_point_t *max);
GEOJSONVTCAPICALL void geojsonvt_box_free(geojsonvt_box_t *box);
GEOJSONVTCAPICALL geojsonvt_point_t *
geojsonvt_box_get_min(geojsonvt_box_t *box);
GEOJSONVTCAPICALL geojsonvt_point_t *
geojsonvt_box_get_max(geojsonvt_box_t *box);
GEOJSONVTCAPICALL geojsonvt_box_t *
geojsonvt_box_envelope(geojsonvt_geometry_t *geom);

GEOJSONVTCAPICALL geojsonvt_point_t *geojsonvt_point_new(int16_t x, int16_t y);
GEOJSONVTCAPICALL void geojsonvt_point_free(geojsonvt_point_t *pt);
GEOJSONVTCAPICALL int16_t geojsonvt_point_get_x(geojsonvt_point_t *pt);
GEOJSONVTCAPICALL int16_t geojsonvt_point_get_y(geojsonvt_point_t *pt);
GEOJSONVTCAPICALL void geojsonvt_point_get_xy(geojsonvt_point_t *pt, int16_t *x,
                                              int16_t *y);
GEOJSONVTCAPICALL void geojsonvt_point_set_xy(geojsonvt_point_t *pt, int16_t x,
                                              int16_t y);
GEOJSONVTCAPICALL geojsonvt_geometry_t *
geojsonvt_point_to_geometry(geojsonvt_point_t *pt);
GEOJSONVTCAPICALL bool geojsonvt_point_equal(geojsonvt_point_t *geom1,
                                             geojsonvt_point_t *geom2);

GEOJSONVTCAPICALL geojsonvt_line_string_t *
geojsonvt_line_string_new(int16_t *xy, int pointcount);
GEOJSONVTCAPICALL void geojsonvt_line_string_free(geojsonvt_line_string_t *pt);
GEOJSONVTCAPICALL int
geojsonvt_line_string_get_points_count(geojsonvt_line_string_t *pt);
GEOJSONVTCAPICALL geojsonvt_point_t *
geojsonvt_line_string_get_point(geojsonvt_line_string_t *pt, int i);
GEOJSONVTCAPICALL void
geojsonvt_line_string_update_point(geojsonvt_line_string_t *pt, int i,
                                   int16_t x, int16_t y);
GEOJSONVTCAPICALL void
geojsonvt_line_string_append_point(geojsonvt_line_string_t *pt, int16_t x,
                                   int16_t y);
GEOJSONVTCAPICALL void
geojsonvt_line_string_get_point_xy(geojsonvt_line_string_t *pt, int i,
                                   int16_t *x, int16_t *y);
GEOJSONVTCAPICALL geojsonvt_geometry_t *
geojsonvt_line_string_to_geometry(geojsonvt_line_string_t *pt);
GEOJSONVTCAPICALL bool
geojsonvt_line_string_equal(geojsonvt_line_string_t *geom1,
                            geojsonvt_line_string_t *geom2);

GEOJSONVTCAPICALL geojsonvt_multi_point_t *
geojsonvt_multi_point_new(int16_t *xy, int pointcount);
GEOJSONVTCAPICALL void geojsonvt_multi_point_free(geojsonvt_multi_point_t *pt);
GEOJSONVTCAPICALL int
geojsonvt_multi_point_get_points_count(geojsonvt_multi_point_t *pt);
GEOJSONVTCAPICALL void
geojsonvt_multi_point_update_point(geojsonvt_multi_point_t *pt, int i,
                                   int16_t x, int16_t y);
GEOJSONVTCAPICALL void
geojsonvt_multi_point_append_point(geojsonvt_multi_point_t *pt, int16_t x,
                                   int16_t y);
GEOJSONVTCAPICALL void
geojsonvt_multi_point_get_point_xy(geojsonvt_multi_point_t *pt, int i,
                                   int16_t *x, int16_t *y);
GEOJSONVTCAPICALL geojsonvt_point_t *
geojsonvt_multi_point_get_point(geojsonvt_multi_point_t *pt, int i);
GEOJSONVTCAPICALL geojsonvt_geometry_t *
geojsonvt_multi_point_to_geometry(geojsonvt_multi_point_t *pt);
GEOJSONVTCAPICALL bool
geojsonvt_multi_point_equal(geojsonvt_multi_point_t *geom1,
                            geojsonvt_multi_point_t *geom2);

GEOJSONVTCAPICALL geojsonvt_linear_ring_t *
geojsonvt_linear_ring_new(int16_t *xy, int pointcount);
GEOJSONVTCAPICALL void geojsonvt_linear_ring_free(geojsonvt_linear_ring_t *pt);
GEOJSONVTCAPICALL int
geojsonvt_linear_ring_get_points_count(geojsonvt_linear_ring_t *pt);
GEOJSONVTCAPICALL void
geojsonvt_linear_ring_update_point(geojsonvt_linear_ring_t *pt, int i,
                                   int16_t x, int16_t y);
GEOJSONVTCAPICALL void
geojsonvt_linear_ring_append_point(geojsonvt_linear_ring_t *pt, int16_t x,
                                   int16_t y);
GEOJSONVTCAPICALL geojsonvt_point_t *
geojsonvt_linear_ring_get_point(geojsonvt_linear_ring_t *pt, int i);
GEOJSONVTCAPICALL void
geojsonvt_linear_ring_get_point_xy(geojsonvt_linear_ring_t *pt, int i,
                                   int16_t *x, int16_t *y);
GEOJSONVTCAPICALL bool
geojsonvt_linear_ring_equal(geojsonvt_linear_ring_t *geom1,
                            geojsonvt_linear_ring_t *geom2);

GEOJSONVTCAPICALL geojsonvt_polygon_t *
geojsonvt_polygon_new(geojsonvt_linear_ring_t **rings, int ringcount);
GEOJSONVTCAPICALL void geojsonvt_polygon_free(geojsonvt_polygon_t *pt);
GEOJSONVTCAPICALL geojsonvt_linear_ring_t *
geojsonvt_polygon_get_exterior(geojsonvt_polygon_t *pt);
GEOJSONVTCAPICALL void
geojsonvt_polygon_set_exterior(geojsonvt_polygon_t *pt,
                               geojsonvt_linear_ring_t *ring);
GEOJSONVTCAPICALL int
geojsonvt_polygon_get_interior_count(geojsonvt_polygon_t *pt);
GEOJSONVTCAPICALL void
geojsonvt_polygon_append_interior_ring(geojsonvt_polygon_t *pt,
                                       geojsonvt_linear_ring_t *ring);
GEOJSONVTCAPICALL void
geojsonvt_polygon_update_interior_ring(geojsonvt_polygon_t *pt, int i,
                                       geojsonvt_linear_ring_t *ring);
GEOJSONVTCAPICALL geojsonvt_linear_ring_t *
geojsonvt_polygon_get_interior(geojsonvt_polygon_t *pt, int i);
GEOJSONVTCAPICALL geojsonvt_geometry_t *
geojsonvt_polygon_to_geometry(geojsonvt_polygon_t *pt);
GEOJSONVTCAPICALL bool geojsonvt_polygon_equal(geojsonvt_polygon_t *geom1,
                                               geojsonvt_polygon_t *geom2);

GEOJSONVTCAPICALL geojsonvt_multi_line_string_t *
geojsonvt_multi_line_string_new(geojsonvt_line_string_t **lines, int ringcount);
GEOJSONVTCAPICALL void
geojsonvt_multi_line_string_free(geojsonvt_multi_line_string_t *pt);
GEOJSONVTCAPICALL void
geojsonvt_multi_line_string_append(geojsonvt_multi_line_string_t *pt,
                                   geojsonvt_line_string_t *line);
GEOJSONVTCAPICALL void
geojsonvt_multi_line_string_update(geojsonvt_multi_line_string_t *pt, int i,
                                   geojsonvt_line_string_t *line);
GEOJSONVTCAPICALL int
geojsonvt_multi_line_get_count(geojsonvt_multi_line_string_t *pt);
GEOJSONVTCAPICALL geojsonvt_line_string_t *
geojsonvt_multi_line_string_get(geojsonvt_multi_line_string_t *pt, int i);
GEOJSONVTCAPICALL geojsonvt_geometry_t *
geojsonvt_multi_line_string_to_geometry(geojsonvt_multi_line_string_t *pt);
GEOJSONVTCAPICALL bool
geojsonvt_multi_line_string_equal(geojsonvt_multi_line_string_t *geom1,
                                  geojsonvt_multi_line_string_t *geom2);

GEOJSONVTCAPICALL geojsonvt_multi_polygon_t *
geojsonvt_multi_polygon_new(geojsonvt_polygon_t **lines, int ringcount);
GEOJSONVTCAPICALL void
geojsonvt_multi_polygon_free(geojsonvt_multi_polygon_t *pt);
GEOJSONVTCAPICALL void
geojsonvt_multi_polygon_append(geojsonvt_multi_polygon_t *pt,
                               geojsonvt_polygon_t *line);
GEOJSONVTCAPICALL void
geojsonvt_multi_polygon_update(geojsonvt_multi_polygon_t *pt, int i,
                               geojsonvt_polygon_t *line);
GEOJSONVTCAPICALL int
geojsonvt_multi_polygon_get_count(geojsonvt_multi_polygon_t *pt);
GEOJSONVTCAPICALL geojsonvt_polygon_t *
geojsonvt_multi_polygon_get(geojsonvt_multi_polygon_t *pt, int i);
GEOJSONVTCAPICALL geojsonvt_geometry_t *
geojsonvt_multi_polygon_to_geometry(geojsonvt_multi_polygon_t *pt);
GEOJSONVTCAPICALL bool
geojsonvt_multi_polygon_equal(geojsonvt_multi_polygon_t *geom1,
                              geojsonvt_multi_polygon_t *geom2);

GEOJSONVTCAPICALL void geojsonvt_geometry_free(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_geometry_empty(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_geometry_is_point(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL _Bool
geojsonvt_geometry_is_line_string(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL _Bool
geojsonvt_geometry_is_polygon(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL _Bool
geojsonvt_geometry_is_multi_point(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL _Bool
geojsonvt_geometry_is_multi_line_string(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL _Bool
geojsonvt_geometry_is_multi_polygon(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL geojsonvt_point_t *
geojsonvt_geometry_cast_point(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL geojsonvt_line_string_t *
geojsonvt_geometry_cast_line_string(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL geojsonvt_polygon_t *
geojsonvt_geometry_cast_polygon(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL geojsonvt_multi_point_t *
geojsonvt_geometry_cast_multi_point(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL geojsonvt_multi_line_string_t *
geojsonvt_geometry_cast_multi_line_string(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL geojsonvt_multi_polygon_t *
geojsonvt_geometry_cast_multi_polygon(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL bool geojsonvt_geometry_equal(geojsonvt_geometry_t *geom1,
                                                geojsonvt_geometry_t *geom2);

GEOJSONVTCAPICALL geojsonvt_geometry_collection_t *
geojsonvt_geometry_collection_new();
GEOJSONVTCAPICALL void
geojsonvt_geometry_collection_free(geojsonvt_geometry_collection_t *geom);
GEOJSONVTCAPICALL _Bool
geojsonvt_geometry_collection_empty(geojsonvt_geometry_collection_t *gc);
GEOJSONVTCAPICALL void
geojsonvt_geometry_collection_append(geojsonvt_geometry_collection_t *gc,
                                     geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL void
geojsonvt_geometry_collection_update(geojsonvt_geometry_collection_t *gc, int i,
                                     geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL int
geojsonvt_geometry_collection_get_count(geojsonvt_geometry_collection_t *gc);
GEOJSONVTCAPICALL geojsonvt_geometry_t *
geojsonvt_geometry_collection_get(geojsonvt_geometry_collection_t *gc, int i);

GEOJSONVTCAPICALL geojsonvt_value_t *geojsonvt_value_new();
GEOJSONVTCAPICALL void geojsonvt_value_free(geojsonvt_value_t *val);
GEOJSONVTCAPICALL geojsonvt_value_t *geojsonvt_value_from_bool(_Bool v);
GEOJSONVTCAPICALL geojsonvt_value_t *geojsonvt_value_from_uint(uint64_t v);
GEOJSONVTCAPICALL geojsonvt_value_t *geojsonvt_value_from_int(int64_t v);
GEOJSONVTCAPICALL geojsonvt_value_t *geojsonvt_value_from_double(double v);
GEOJSONVTCAPICALL geojsonvt_value_t *geojsonvt_value_from_string(const char *v);
GEOJSONVTCAPICALL geojsonvt_value_t *
geojsonvt_value_from_values(geojsonvt_value_t **vs, int valuecount);
GEOJSONVTCAPICALL geojsonvt_value_t *
geojsonvt_value_from_keyvalues(const char **ks, geojsonvt_value_t **vs,
                               int valuecount);
GEOJSONVTCAPICALL _Bool geojsonvt_value_is_empty(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_value_is_null(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_value_is_bool(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_value_is_uint(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_value_is_int(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_value_is_double(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_value_is_string(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_value_is_vector(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_value_is_map(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL _Bool geojsonvt_value_cast_bool(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL uint64_t geojsonvt_value_cast_uint(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL int64_t geojsonvt_value_cast_int(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL double geojsonvt_value_cast_double(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL char *geojsonvt_value_cast_string(geojsonvt_value_t *geom);
GEOJSONVTCAPICALL geojsonvt_value_t **
geojsonvt_value_cast_vector(geojsonvt_value_t *geom, int *count);
GEOJSONVTCAPICALL void geojsonvt_values_free(geojsonvt_value_t **vs);
GEOJSONVTCAPICALL geojsonvt_property_map_t *
geojsonvt_value_cast_map(geojsonvt_value_t *geom);

GEOJSONVTCAPICALL geojsonvt_property_map_t *geojsonvt_property_map_new();
GEOJSONVTCAPICALL void
geojsonvt_property_map_free(geojsonvt_property_map_t *val);
GEOJSONVTCAPICALL geojsonvt_value_t *
geojsonvt_property_map_get(geojsonvt_property_map_t *val, const char *key);
GEOJSONVTCAPICALL void geojsonvt_property_map_set(geojsonvt_property_map_t *val,
                                                  const char *key,
                                                  geojsonvt_value_t *v);
GEOJSONVTCAPICALL _Bool
geojsonvt_property_map_has(geojsonvt_property_map_t *val, const char *key);
GEOJSONVTCAPICALL _Bool
geojsonvt_property_map_empty(geojsonvt_property_map_t *val);
GEOJSONVTCAPICALL char **
geojsonvt_property_map_keys(geojsonvt_property_map_t *val, int *count);
GEOJSONVTCAPICALL void geojsonvt_property_map_free_keys(char **keys, int count);
GEOJSONVTCAPICALL int
geojsonvt_property_map_count(geojsonvt_property_map_t *val);

GEOJSONVTCAPICALL geojsonvt_identifier_t *
geojsonvt_identifier_from_uint(uint64_t v);
GEOJSONVTCAPICALL geojsonvt_identifier_t *
geojsonvt_identifier_from_int(int64_t v);
GEOJSONVTCAPICALL geojsonvt_identifier_t *
geojsonvt_identifier_from_double(double v);
GEOJSONVTCAPICALL geojsonvt_identifier_t *
geojsonvt_identifier_from_string(const char *v);
GEOJSONVTCAPICALL void geojsonvt_identifier_free(geojsonvt_identifier_t *val);
GEOJSONVTCAPICALL _Bool
geojsonvt_identifier_is_uint(geojsonvt_identifier_t *geom);
GEOJSONVTCAPICALL _Bool
geojsonvt_identifier_is_int(geojsonvt_identifier_t *geom);
GEOJSONVTCAPICALL _Bool
geojsonvt_identifier_is_double(geojsonvt_identifier_t *geom);
GEOJSONVTCAPICALL _Bool
geojsonvt_identifier_is_string(geojsonvt_identifier_t *geom);
GEOJSONVTCAPICALL uint64_t
geojsonvt_identifier_cast_uint(geojsonvt_identifier_t *geom);
GEOJSONVTCAPICALL int64_t
geojsonvt_identifier_cast_int(geojsonvt_identifier_t *geom);
GEOJSONVTCAPICALL double
geojsonvt_identifier_cast_double(geojsonvt_identifier_t *geom);
GEOJSONVTCAPICALL char *
geojsonvt_identifier_cast_string(geojsonvt_identifier_t *geom);

GEOJSONVTCAPICALL geojsonvt_feature_t *
geojsonvt_feature_new(geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL geojsonvt_feature_t *
geojsonvt_feature_create(geojsonvt_identifier_t *id, geojsonvt_geometry_t *geom,
                         geojsonvt_property_map_t *props);
GEOJSONVTCAPICALL void geojsonvt_feature_free(geojsonvt_feature_t *feat);
GEOJSONVTCAPICALL void
geojsonvt_feature_set_identifier(geojsonvt_feature_t *feat,
                                 geojsonvt_identifier_t *id);
GEOJSONVTCAPICALL void
geojsonvt_feature_set_geometry(geojsonvt_feature_t *feat,
                               geojsonvt_geometry_t *geom);
GEOJSONVTCAPICALL void
geojsonvt_feature_set_property_map(geojsonvt_feature_t *feat,
                                   geojsonvt_property_map_t *props);
GEOJSONVTCAPICALL geojsonvt_identifier_t *
geojsonvt_feature_get_identifier(geojsonvt_feature_t *feat);
GEOJSONVTCAPICALL geojsonvt_geometry_t *
geojsonvt_feature_get_geometry(geojsonvt_feature_t *feat);
GEOJSONVTCAPICALL geojsonvt_property_map_t *
geojsonvt_feature_get_property_map(geojsonvt_feature_t *feat);
GEOJSONVTCAPICALL bool geojsonvt_feature_equal(geojsonvt_feature_t *feat1,
                                               geojsonvt_feature_t *feat2);

GEOJSONVTCAPICALL geojsonvt_feature_collection_t *
geojsonvt_feature_collection_new();
GEOJSONVTCAPICALL void
geojsonvt_feature_collection_free(geojsonvt_feature_collection_t *featc);
GEOJSONVTCAPICALL _Bool
geojsonvt_feature_collection_empty(geojsonvt_feature_collection_t *gc);
GEOJSONVTCAPICALL void
geojsonvt_feature_collection_append(geojsonvt_feature_collection_t *gc,
                                    geojsonvt_feature_t *feat);
GEOJSONVTCAPICALL void
geojsonvt_feature_collection_update(geojsonvt_feature_collection_t *gc, int i,
                                    geojsonvt_feature_t *feat);
GEOJSONVTCAPICALL int
geojsonvt_feature_collection_get_count(geojsonvt_feature_collection_t *gc);
GEOJSONVTCAPICALL geojsonvt_feature_t *
geojsonvt_feature_collection_get(geojsonvt_feature_collection_t *gc, int i);

GEOJSONVTCAPICALL void geojsonvt_tile_free(geojsonvt_tile_t *t);
GEOJSONVTCAPICALL geojsonvt_feature_collection_t *
geojsonvt_tile_get_feature_collection(geojsonvt_tile_t *t);

struct _geojsonvt_tile_options_t {
  double tolerance;
  uint16_t extent;
  uint16_t buffer;
  bool lineMetrics;
  uint8_t maxZoom;
  uint8_t indexMaxZoom;
  uint32_t indexMaxPoints;
  bool generateId;
};

GEOJSONVTCAPICALL geojsonvt_t *
geojsonvt_new(void *geom, struct _geojsonvt_tile_options_t opts);
GEOJSONVTCAPICALL void geojsonvt_free(geojsonvt_t *t);
GEOJSONVTCAPICALL geojsonvt_tile_t *
geojsonvt_get_tile(geojsonvt_t *t, uint32_t z, uint32_t x, uint32_t y);

#ifdef __cplusplus
}
#endif

#endif