package geojsonvt

// #include <stdlib.h>
// #include <string.h>
// #include "geojsonvt_c_api.h"
// #cgo CFLAGS: -I ../
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"reflect"
	"runtime"
	"unsafe"
)

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
	runtime.SetFinalizer(fc, (*FeatureCollection).free)
	return fc
}

func ParseFeatureCollections(data string) map[string]*FeatureCollection {
	cdata := C.CString(data)
	defer C.free(unsafe.Pointer(cdata))
	var feats **C.struct__geojsonvt_feature_collection_t
	var keys **C.char

	si := C.geojsonvt_feature_collections_parse(cdata, &feats, &keys)

	defer C.geojsonvt_feature_collections_free(si, feats, keys)

	rets := make(map[string]*FeatureCollection)

	var fcSlice []*C.struct__geojsonvt_feature_collection_t
	fcHeader := (*reflect.SliceHeader)((unsafe.Pointer(&fcSlice)))
	fcHeader.Cap = int(si)
	fcHeader.Len = int(si)
	fcHeader.Data = uintptr(unsafe.Pointer(feats))

	var keysSlice []*C.char
	keysHeader := (*reflect.SliceHeader)((unsafe.Pointer(&keysSlice)))
	keysHeader.Cap = int(si)
	keysHeader.Len = int(si)
	keysHeader.Data = uintptr(unsafe.Pointer(keys))

	for i := 0; i < int(si); i++ {
		k := C.GoString(keysSlice[i])
		ret := &FeatureCollection{fc: fcSlice[i]}
		runtime.SetFinalizer(ret, (*FeatureCollection).free)

		rets[k] = ret
	}

	return rets
}
