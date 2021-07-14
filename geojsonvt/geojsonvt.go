package geojsonvt

// #include <stdlib.h>
// #include <string.h>
// #include "geojsonvt_c_api.h"
// #cgo CFLAGS: -I ../
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"runtime"
	"unsafe"

	"github.com/flywave/go-mbgeom/geojson"
)

type TileOptions struct {
	Tolerance      float64
	Extent         uint16
	Buffer         uint16
	LineMetrics    bool
	MaxZoom        uint8
	IndexMaxZoom   uint8
	IndexMaxPoints uint32
	GenerateId     bool
}

type GeoJSONVT struct {
	vt *C.struct__geojsonvt_t
}

func NewGeoJSONVT(geo *geojson.GeoJSON, opts TileOptions) *GeoJSONVT {
	var copt C.struct__geojsonvt_tile_options_t
	copt = *(*C.struct__geojsonvt_tile_options_t)(unsafe.Pointer(&opts))
	ret := &GeoJSONVT{vt: C.geojsonvt_new(geo.GetNative(), copt)}
	runtime.SetFinalizer(ret, (*GeoJSONVT).free)
	return ret
}

func (t *GeoJSONVT) free() {
	if t.vt != nil {
		C.geojsonvt_free(t.vt)
	}
}

func (t *GeoJSONVT) GetTile(z, x, y uint32) *Tile {
	return &Tile{t: C.geojsonvt_get_tile(t.vt, C.uint(z), C.uint(x), C.uint(y))}
}
