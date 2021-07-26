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

type Geometry struct {
	g *C.struct__mvt_geometry_t
}

func NewGeometry() *Geometry {
	ret := &Geometry{g: C.mvt_geometry_new()}
	runtime.SetFinalizer(ret, (*Geometry).free)
	return ret
}

func NewGeometryValueWithData(data []byte, tp GeomType) *Geometry {
	ret := &Geometry{g: C.mvt_geometry_new_with_data((*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)), C.uint(tp))}
	runtime.SetFinalizer(ret, (*Geometry).free)
	return ret
}

func (v *Geometry) free() {
	C.mvt_geometry_free(v.g)
}

type PointGeometry struct {
	p *C.struct__mvt_geometry_point_t
}

func (v *PointGeometry) free() {
	C.mvt_geometry_point_free(v.g)
}

type LineStringGeometry struct {
	p *C.struct__mvt_geometry_linestring_t
}

func (v *LineStringGeometry) free() {
	C.mvt_geometry_linestring_free(v.g)
}

type PolygonGeometry struct {
	p *C.struct__mvt_geometry_polygon_t
}

func (v *PolygonGeometry) free() {
	C.mvt_geometry_polygon_free(v.g)
}
