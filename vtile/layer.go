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

type Layer struct {
	l *C.struct__mvt_layer_t
}

func NewLayer() *Layer {
	ret := &Layer{l: C.mvt_layer_new()}
	runtime.SetFinalizer(ret, (*Layer).free)
	return ret
}

func NewLayerWithData(data []byte) *Layer {
	ret := &Layer{l: C.mvt_layer_new_with_data((*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)))}
	runtime.SetFinalizer(ret, (*Layer).free)
	return ret
}

func (v *Layer) free() {
	C.mvt_vector_layer_free(v.l)
}
