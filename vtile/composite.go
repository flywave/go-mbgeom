package vtile

// #include <stdlib.h>
// #include <string.h>
// #include "vtile_c_api.h"
// #cgo CFLAGS: -I ../ -std=c11
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"errors"
	"reflect"
	"runtime"
	"unsafe"
)

type TileObject struct {
	o *C.struct__mvt_tile_object_t
}

func NewTileObject(z, x, y uint32, data []byte) *TileObject {
	ret := &TileObject{o: C.mvt_tile_object_new(C.uint(z), C.uint(x), C.uint(y), (*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)))}
	runtime.SetFinalizer(ret, (*TileObject).free)
	return ret
}

func (v *TileObject) free() {
	if v.o != nil {
		C.mvt_tile_object_free(v.o)
	}
}

func (v *TileObject) AddLayer(layer string) {
	l := C.CString(layer)
	defer C.free(unsafe.Pointer(l))
	C.mvt_tile_object_add_layer(v.o, l)
}

type TileBaton struct {
	b *C.struct__mvt_baton_t
}

func NewTileBaton(num_tiles int) *TileBaton {
	ret := &TileBaton{b: C.mvt_baton_new(C.size_t(num_tiles))}
	runtime.SetFinalizer(ret, (*TileBaton).free)
	return ret
}

func (t *TileBaton) free() {
	if t.b != nil {
		C.mvt_baton_free(t.b)
	}
}

func (t *TileBaton) SetZXY(z, x, y uint32) {
	C.mvt_baton_set_zxy(t.b, C.uint(z), C.uint(x), C.uint(y))
}

func (t *TileBaton) SetBufferSize(buffer_size int) {
	C.mvt_baton_set_buffer_size(t.b, C.int(buffer_size))
}

func (t *TileBaton) AddTile(to *TileObject) {
	C.mvt_baton_add_tile(t.b, to.o)
}

func (t *TileBaton) ClearTile() {
	C.mvt_baton_clear_tile(t.b)
}

func Composite(baton *TileBaton) ([]byte, error) {
	var si C.size_t
	var hasErr C.bool
	cdata := C.mvt_composite(baton.b, &si, &hasErr)

	if bool(hasErr) {
		return nil, errors.New(C.GoString(cdata))
	}

	var dSlice []byte
	dHeader := (*reflect.SliceHeader)((unsafe.Pointer(&dSlice)))
	dHeader.Cap = int(si)
	dHeader.Len = int(si)
	dHeader.Data = uintptr(unsafe.Pointer(cdata))

	ret := make([]byte, int(si))
	copy(ret, dSlice)
	return ret, nil
}
