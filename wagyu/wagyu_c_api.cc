#include "wagyu_c_api.h"
#include "geom_c_api_impl.hh"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

mapbox_wagyu_t *mapbox_wagyu_new() { return new mapbox_wagyu_t{}; }

void mapbox_wagyu_free(mapbox_wagyu_t *ctx) { delete ctx; }

void mapbox_wagyu_add_ring(mapbox_wagyu_t *ctx, mapbox_linear_ring_t *ring,
                           uint8_t p_type) {
  ctx->ctx.add_ring(ring->lr,
                    static_cast<mapbox::geometry::wagyu::polygon_type>(p_type));
}

void mapbox_wagyu_add_polygon(mapbox_wagyu_t *ctx, mapbox_polygon_t *poly,
                              uint8_t p_type) {
  ctx->ctx.add_polygon(
      poly->poly, static_cast<mapbox::geometry::wagyu::polygon_type>(p_type));
}

void mapbox_wagyu_reverse_rings(mapbox_wagyu_t *ctx, _Bool value) {
  ctx->ctx.reverse_rings(value);
}

void mapbox_wagyu_clear(mapbox_wagyu_t *ctx) { ctx->ctx.clear(); }

mapbox_box_t *mapbox_wagyu_get_bounds(mapbox_wagyu_t *ctx) {
  return new mapbox_box_t{ctx->ctx.get_bounds()};
}

_Bool mapbox_wagyu_execute(mapbox_wagyu_t *ctx, uint8_t tp,
                           mapbox_multi_polygon_t *mp,
                           uint8_t subject_fill_type, uint8_t clip_fill_type) {
  return ctx->ctx.execute(
      static_cast<mapbox::geometry::wagyu::clip_type>(tp), mp->mp,
      static_cast<mapbox::geometry::wagyu::fill_type>(subject_fill_type),
      static_cast<mapbox::geometry::wagyu::fill_type>(clip_fill_type));
}

#ifdef __cplusplus
}
#endif
