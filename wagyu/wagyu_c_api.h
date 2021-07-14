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