package geojson

// #include <stdlib.h>
// #include <string.h>
// #include "geojson_c_api.h"
// #cgo CFLAGS: -I ../ -std=c11
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"runtime"
	"unsafe"
)

type Box struct {
	m *C.struct__mapbox_box_t
}

func (e *Box) free() {
	if e.m != nil {
		C.mapbox_box_free(e.m)
	}
}

func NewBox(min, max *Point) *Box {
	d := &Box{m: C.mapbox_box_new(min.p, max.p)}
	runtime.SetFinalizer(d, (*Box).free)
	return d
}

func NewBoxNative(m unsafe.Pointer) *Box {
	d := &Box{m: (*C.struct__mapbox_box_t)(m)}
	runtime.SetFinalizer(d, (*Box).free)
	return d
}

func (b *Box) GetMin() *Point {
	p := &Point{p: C.mapbox_box_get_min(b.m)}
	runtime.SetFinalizer(p, (*Point).free)
	return p
}

func (b *Box) GetMax() *Point {
	p := &Point{p: C.mapbox_box_get_max(b.m)}
	runtime.SetFinalizer(p, (*Point).free)
	return p
}
