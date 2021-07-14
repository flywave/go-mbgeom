#ifndef GO_ALGORITHMS_C_API_H_
#define GO_ALGORITHMS_C_API_H_

#include "geojson_c_api.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define ALGORITHMSCAPICALL __declspec(dllexport)
#else
#define ALGORITHMSCAPICALL
#endif

ALGORITHMSCAPICALL mapbox_geometry_t **
mapbox_spatial_algorithms_intersects(mapbox_geometry_t *geom1,
                                     mapbox_geometry_t *geom2, int *count);
ALGORITHMSCAPICALL _Bool mapbox_spatial_algorithms_disjoint(
    mapbox_geometry_t *geom1, mapbox_geometry_t *geom2);
ALGORITHMSCAPICALL mapbox_geometry_t **
mapbox_spatial_algorithms_intersection(mapbox_geometry_t *geom1,
                                       mapbox_geometry_t *geom2, int *count);

#ifdef __cplusplus
}
#endif

#endif