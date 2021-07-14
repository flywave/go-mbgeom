package geojsonvt

// #include <stdlib.h>
// #include <string.h>
// #include "geojsonvt_c_api.h"
// #cgo CFLAGS: -I ../
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import "runtime"

type Tile struct {
	t *C.struct__geojsonvt_tile_t
}

func (t *Tile) free() {
	if t.t != nil {
		C.geojsonvt_tile_free(t.t)
	}
}

func (t *Tile) GetFeatureCollection() *FeatureCollection {
	fc := &FeatureCollection{fc: C.geojsonvt_tile_get_feature_collection(t.t)}
	runtime.SetFinalizer(fc, (*GeometryCollection).free)
	return fc
}
