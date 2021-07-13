package wagyu

// #include <stdlib.h>
// #include <string.h>
// #include "wagyu_c_api.h"
// #cgo CFLAGS: -I ./
// #cgo CXXFLAGS:  -I ./ -std=c++14
import "C"
import "runtime"

type ClipType uint8

const (
	ClipTypeIntersection ClipType = 0
	ClipTypeUnion        ClipType = 1
	ClipTypeDifference   ClipType = 2
	ClipTypeXOR          ClipType = 3
)

type PolygonType uint8

const (
	PolygonTypeSubject PolygonType = 0
	PolygonTypeClip    PolygonType = 1
)

type FillType uint8

const (
	FillTypeEvenOdd  FillType = 0
	FillTypeNonZero  FillType = 1
	FillTypePositive FillType = 2
	FillTypeNegative FillType = 3
)

type Context struct {
	c *C.struct__mapbox_wagyu_t
}

func NewContext() *Context {
	ret := &Context{c: C.mapbox_wagyu_new()}
	runtime.SetFinalizer(ret, (*Context).free)
	return ret
}

func (e *Context) free() {
	if e.c != nil {
		C.mapbox_wagyu_free(e.c)
	}
}

func (e *Context) AddRing(rings *LinearRing, ptype PolygonType) {
	C.mapbox_wagyu_add_ring(e.c, rings.lr, C.uchar(ptype))
}

func (e *Context) AddPolygon(poly *Polygon, ptype PolygonType) {
	C.mapbox_wagyu_add_polygon(e.c, poly.p, C.uchar(ptype))
}

func (e *Context) ReverseRings(value bool) {
	C.mapbox_wagyu_reverse_rings(e.c, C.bool(value))
}

func (e *Context) Clear() {
	C.mapbox_wagyu_clear(e.c)
}

func (e *Context) GetBounds() *Box {
	d := &Box{C.mapbox_wagyu_get_bounds(e.c)}
	runtime.SetFinalizer(d, (*Box).free)
	return d
}

func (e *Context) Execute(tp ClipType, p *MultiPolygon, subjectFillType FillType, clipFillType FillType) bool {
	return bool(C.mapbox_wagyu_execute(e.c, C.uchar(tp), p.mp, C.uchar(subjectFillType), C.uchar(clipFillType)))
}
