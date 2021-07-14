package geojsonvt

// #include <stdlib.h>
// #include <string.h>
// #include "geojsonvt_c_api.h"
// #include "wagyu_c_api.h"
// #cgo CFLAGS: -I ../
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"runtime"

	"github.com/flywave/go-wagyu/geojson"
)

type GeoJSONVT struct {
	vt *C.struct__geojsonvt_t
}

func NewGeoJSONVT(fc *geojson.FeatureCollection) *GeoJSONVT {
	ret := &GeoJSONVT{vt: C.geojsonvt_new(fc.GetNative())}
	runtime.SetFinalizer(ret, (*GeoJSONVT).free)
	return ret
}

func (t *GeoJSONVT) free() {
	if t.vt != nil {
		C.geojsonvt_free(t.vt)
	}
}
