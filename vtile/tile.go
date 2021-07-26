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
	C.mvt_vector_tile_free(v.m)
}
