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

typedef struct _mapbox_wagyu_t mapbox_wagyu_t;

WAGYUCAPICALL mapbox_wagyu_t *mapbox_wagyu_new();
WAGYUCAPICALL void mapbox_wagyu_free(mapbox_wagyu_t *ctx);
WAGYUCAPICALL void mapbox_wagyu_add_ring(mapbox_wagyu_t *ctx, void *ring,
                                         uint8_t p_type);
WAGYUCAPICALL void mapbox_wagyu_add_polygon(mapbox_wagyu_t *ctx, void *poly,
                                            uint8_t p_type);
WAGYUCAPICALL void mapbox_wagyu_reverse_rings(mapbox_wagyu_t *ctx, _Bool value);
WAGYUCAPICALL void mapbox_wagyu_clear(mapbox_wagyu_t *ctx);
WAGYUCAPICALL void *mapbox_wagyu_get_bounds(mapbox_wagyu_t *ctx);
WAGYUCAPICALL _Bool mapbox_wagyu_execute(mapbox_wagyu_t *ctx, uint8_t tp,
                                         void *mp, uint8_t subject_fill_type,
                                         uint8_t clip_fill_type);

#ifdef __cplusplus
}
#endif

#endif