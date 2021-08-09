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

type Tile struct {
	m *C.struct__mvt_vector_tile_t
}

func NewTile(data []byte) *Tile {
	ret := &Tile{m: C.mvt_vector_tile_new((*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)))}
	runtime.SetFinalizer(ret, (*Tile).free)
	return ret
}

func (v *Tile) free() {
	if v.m != nil {
		C.mvt_vector_tile_free(v.m)
	}
}

func (v *Tile) Empty() bool {
	return bool(C.mvt_vector_tile_empty(v.m))
}

func (v *Tile) LayersCount() int {
	return int(C.mvt_vector_tile_count_layers(v.m))
}

func (v *Tile) NextLayer() *Layer {
	ret := &Layer{l: C.mvt_vector_tile_next_layer(v.m)}
	runtime.SetFinalizer(ret, (*Layer).free)
	return ret
}

func (v *Tile) ResetLayer() {
	C.mvt_vector_tile_reset_layer(v.m)
}

func (v *Tile) GetLayer(index int) *Layer {
	ret := &Layer{l: C.mvt_vector_tile_get_layer(v.m, C.int(index))}
	runtime.SetFinalizer(ret, (*Layer).free)
	return ret
}

func (v *Tile) GetLayerByName(name string) *Layer {
	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))
	ret := &Layer{l: C.mvt_vector_tile_get_layer_by_name(v.m, cname)}
	runtime.SetFinalizer(ret, (*Layer).free)
	return ret
}

func IsVectorTile(data []byte) bool {
	return bool(C.mvt_vector_tile_is_vector_tile((*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data))))
}
