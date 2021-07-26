package vtile

// #include <stdlib.h>
// #include <string.h>
// #include "vtile_c_api.h"
// #cgo CFLAGS: -I ../
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"runtime"
	"unsafe"
)

type Feature struct {
	f *C.struct__mvt_feature_t
}

func NewFeature() *Feature {
	ret := &Feature{f: C.mvt_feature_new()}
	runtime.SetFinalizer(ret, (*Feature).free)
	return ret
}

func NewFeatureWithData(layer *Layer, data []byte) *Feature {
	ret := &Feature{f: C.mvt_feature_new_with_data(layer.l, (*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)))}
	runtime.SetFinalizer(ret, (*Feature).free)
	return ret
}

func (v *Feature) free() {
	C.mvt_feature_free(v.f)
}
