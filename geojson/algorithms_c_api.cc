#include "algorithms_c_api.h"
#include "geom_c_api_impl.hh"

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
