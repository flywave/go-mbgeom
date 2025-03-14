package vtile

// #include <stdlib.h>
// #include <string.h>
// #include "vtile_c_api.h"
// #cgo CFLAGS: -I ../ -std=c11
// #cgo CXXFLAGS:  -I ../ -std=c++14
// #cgo darwin CXXFLAGS: -Wno-enum-constexpr-conversion -Wno-c++11-narrowing
import "C"
import (
	"reflect"
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
	if v.g != nil {
		C.mvt_geometry_free(v.g)
	}
}

func (v *Geometry) GetType() GeomType {
	return GeomType(C.mvt_geometry_get_type(v.g))
}

func (v *Geometry) GetData() []byte {
	var si C.size_t
	cdata := C.mvt_geometry_get_data(v.g, &si)

	var dataSlice []byte
	dataHeader := (*reflect.SliceHeader)((unsafe.Pointer(&dataSlice)))
	dataHeader.Cap = int(si)
	dataHeader.Len = int(si)
	dataHeader.Data = uintptr(unsafe.Pointer(cdata))

	ret := make([]byte, int(si))
	copy(ret, dataSlice)
	return ret
}

func (v *Geometry) GetPointGeometry() *PointGeometry {
	ret := &PointGeometry{p: C.mvt_geometry_decode_point_geometry(v.g)}
	runtime.SetFinalizer(ret, (*PointGeometry).free)
	return ret
}

func (v *Geometry) GetLineStringGeometry() *LineStringGeometry {
	ret := &LineStringGeometry{p: C.mvt_geometry_decode_linestring_geometry(v.g)}
	runtime.SetFinalizer(ret, (*LineStringGeometry).free)
	return ret
}

func (v *Geometry) GetPolygonGeometry() *PolygonGeometry {
	ret := &PolygonGeometry{p: C.mvt_geometry_decode_polygon_geometry(v.g)}
	runtime.SetFinalizer(ret, (*PolygonGeometry).free)
	return ret
}

type PointGeometry struct {
	p *C.struct__mvt_geometry_point_t
}

func (v *PointGeometry) free() {
	C.mvt_geometry_point_free(v.p)
}

func (v *PointGeometry) PointCount() int {
	return int(C.mvt_geometry_point_count(v.p))
}

func (v *PointGeometry) GetPoints() [][2]int32 {
	ptsi := v.PointCount()
	ret := make([][2]int32, ptsi)

	C.mvt_geometry_point_get_points(v.p, (*C.int)(unsafe.Pointer(&ret[0])), C.size_t(ptsi))

	return ret
}

type LineStringGeometry struct {
	p *C.struct__mvt_geometry_linestring_t
}

func (v *LineStringGeometry) LineStringCount() int {
	return int(C.mvt_geometry_linestring_count(v.p))
}

func (v *LineStringGeometry) GetPoints() []PointGeometry {
	ptsi := v.LineStringCount()
	cret := make([]*C.struct__mvt_geometry_point_t, ptsi)

	C.mvt_geometry_linestring_get_lines(v.p, &cret[0], C.size_t(ptsi))

	ret := make([]PointGeometry, ptsi)
	for i := range cret {
		ret[i].p = cret[i]
		runtime.SetFinalizer(&ret[i], (*PointGeometry).free)
	}
	return ret
}

func (v *LineStringGeometry) free() {
	C.mvt_geometry_linestring_free(v.p)
}

type PolygonGeometry struct {
	p *C.struct__mvt_geometry_polygon_t
}

func (v *PolygonGeometry) free() {
	C.mvt_geometry_polygon_free(v.p)
}

func (v *PolygonGeometry) PolygonCount() int {
	return int(C.mvt_geometry_polygon_count(v.p))
}

func (v *PolygonGeometry) GetLineStrings() []PointGeometry {
	ptsi := v.PolygonCount()
	cret := make([]*C.struct__mvt_geometry_point_t, ptsi)

	C.mvt_geometry_polygon_get_lines(v.p, &cret[0], C.size_t(ptsi))

	ret := make([]PointGeometry, ptsi)
	for i := range cret {
		ret[i].p = cret[i]
		runtime.SetFinalizer(&ret[i], (*PointGeometry).free)
	}
	return ret
}
