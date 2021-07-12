package wagyu

// #include <stdlib.h>
// #include <string.h>
// #include "wagyu_c_api.h"
// #cgo CFLAGS: -I ./
// #cgo CXXFLAGS:  -I ./ -std=c++14
import "C"
import (
	"runtime"

	"github.com/flywave/go-geom"
)

type Point struct {
	geom.Point
	p *C.struct__mapbox_point_t
}

func NewPoint(x, y float64) *Point {
	p := &Point{p: C.mapbox_point_new(C.double(x), C.double(y))}
	runtime.SetFinalizer(p, (*Point).free)
	return p
}

func (e *Point) free() {
	if e.p != nil {
		C.mapbox_point_free(e.p)
	}
}

func (e *Point) X() float64 {
	return float64(C.mapbox_point_get_x(e.p))
}

func (e *Point) Y() float64 {
	return float64(C.mapbox_point_get_y(e.p))
}

func (e *Point) SetXY(x, y float64) {
	C.mapbox_point_set_xy(e.p, C.double(x), C.double(y))
}

func (e *Point) Data() []float64 {
	var x, y C.double
	C.mapbox_point_get_xy(e.p, &x, &y)
	return []float64{float64(x), float64(y)}
}

func (e *Point) Geom() *Geometry {
	g := &Geometry{g: C.mapbox_point_to_geometry(e.p)}
	runtime.SetFinalizer(g, (*Geometry).free)
	return g
}

func (e *Point) Equal(b *Point) bool {
	return bool(C.mapbox_point_equal(e.p, b.p))
}

type LineString struct {
	geom.LineString
	ls *C.struct__mapbox_line_string_t
}

func (e *LineString) free() {
	if e.ls != nil {
		C.mapbox_line_string_free(e.ls)
	}
}

func (e *LineString) Count() int {
	return int(C.mapbox_line_string_get_points_count(e.ls))
}

func (e *LineString) GetPoint(i int) *Point {
	p := &Point{p: C.mapbox_line_string_get_point(e.ls, C.int(i))}
	runtime.SetFinalizer(p, (*Point).free)
	return p
}

func (e *LineString) SetPoint(i int, x, y float64) {
	C.mapbox_line_string_update_point(e.ls, C.int(i), C.double(x), C.double(y))
}

func (e *LineString) AppendPoint(x, y float64) {
	C.mapbox_line_string_append_point(e.ls, C.double(x), C.double(y))
}

func (e *LineString) Geom() *Geometry {
	g := &Geometry{g: C.mapbox_line_string_to_geometry(e.ls)}
	runtime.SetFinalizer(g, (*Geometry).free)
	return g
}

func (e *LineString) Equal(b *LineString) bool {
	return bool(C.mapbox_line_string_equal(e.ls, b.ls))
}

type MultiPoint struct {
	geom.MultiPoint
	mp *C.struct__mapbox_multi_point_t
}

func (e *MultiPoint) free() {
	if e.mp != nil {
		C.mapbox_multi_point_free(e.mp)
	}
}

type LinearRing struct {
	lr *C.struct__mapbox_linear_ring_t
}

func (e *LinearRing) free() {
	if e.lr != nil {
		C.mapbox_linear_ring_free(e.lr)
	}
}

type Polygon struct {
	geom.Polygon
	p *C.struct__mapbox_polygon_t
}

func (e *Polygon) free() {
	if e.p != nil {
		C.mapbox_polygon_free(e.p)
	}
}

type MultiLineString struct {
	geom.MultiLine
	mls *C.struct__mapbox_multi_line_string_t
}

func (e *MultiLineString) free() {
	if e.mls != nil {
		C.mapbox_multi_line_string_free(e.mls)
	}
}

type MultiPolygon struct {
	geom.MultiPolygon
	mp *C.struct__mapbox_multi_polygon_t
}

func (e *MultiPolygon) free() {
	if e.mp != nil {
		C.mapbox_multi_polygon_free(e.mp)
	}
}

type Geometry struct {
	g *C.struct__mapbox_geometry_t
}

func (e *Geometry) free() {
	if e.g != nil {
		C.mapbox_geometry_free(e.g)
	}
}

type GeometryCollection struct {
	g *C.struct__mapbox_geometry_collection_t
}

func (e *GeometryCollection) free() {
	if e.g != nil {
		C.mapbox_geometry_collection_free(e.g)
	}
}
