#ifndef GO_VTILE_C_API_H_
#define GO_VTILE_C_API_H_

#include <stdbool.h>
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
typedef struct _mvt_geometry_t mvt_geometry_t;

typedef struct _mvt_property_mapper_t mvt_property_mapper_t;

typedef struct _mvt_tile_builder_t mvt_tile_builder_t;
typedef struct _mvt_layer_builder_t mvt_layer_builder_t;
typedef struct _mvt_key_index_t mvt_key_index_t;
typedef struct _mvt_point_feature_builder_t mvt_point_feature_builder_t;
typedef struct _mvt_linestring_feature_builder_t mvt_linestring_feature_builder_t;
typedef struct _mvt_polygon_feature_builder_t mvt_polygon_feature_builder_t;

#ifdef __cplusplus
}
#endif

#endif