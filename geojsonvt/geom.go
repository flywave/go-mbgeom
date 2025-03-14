package geojsonvt

// #include <stdlib.h>
// #include <string.h>
// #include "geojsonvt_c_api.h"
// #cgo CFLAGS: -I ../ -std=c11
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"runtime"
	"unsafe"

	"github.com/flywave/go-geom"
)

type Point struct {
	p *C.struct__geojsonvt_point_t
}

func NewEmptyPoint() *Point {
	p := &Point{p: C.geojsonvt_point_new_empty()}
	runtime.SetFinalizer(p, (*Point).free)
	return p
}

func NewPoint(x, y float64) *Point {
	p := &Point{p: C.geojsonvt_point_new(C.short(x), C.short(y))}
	runtime.SetFinalizer(p, (*Point).free)
	return p
}

func (e *Point) free() {
	if e.p != nil {
		C.geojsonvt_point_free(e.p)
	}
}

func (e *Point) GetType() string {
	return "Point"
}

func (e *Point) X() int16 {
	return int16(C.geojsonvt_point_get_x(e.p))
}

func (e *Point) Y() int16 {
	return int16(C.geojsonvt_point_get_y(e.p))
}

func (e *Point) SetXY(x, y int16) {
	C.geojsonvt_point_set_xy(e.p, C.short(x), C.short(y))
}

func (e *Point) Data() []int16 {
	var x, y C.short
	C.geojsonvt_point_get_xy(e.p, &x, &y)
	return []int16{int16(x), int16(y)}
}

func (e *Point) Geom() *Geometry {
	g := &Geometry{g: C.geojsonvt_point_to_geometry(e.p)}
	runtime.SetFinalizer(g, (*Geometry).free)
	return g
}

func (e *Point) Equal(b *Point) bool {
	return bool(C.geojsonvt_point_equal(e.p, b.p))
}

type LineString struct {
	ls *C.struct__geojsonvt_line_string_t
}

func NewEmptyLineString() *LineString {
	p := &LineString{ls: C.geojsonvt_line_string_new_empty()}
	runtime.SetFinalizer(p, (*LineString).free)
	return p
}

func NewLineString(pts [][2]int16) *LineString {
	ls := &LineString{ls: C.geojsonvt_line_string_new((*C.short)(unsafe.Pointer(&pts[0])), C.int(len(pts)))}
	runtime.SetFinalizer(ls, (*LineString).free)
	return ls
}

func (e *LineString) free() {
	if e.ls != nil {
		C.geojsonvt_line_string_free(e.ls)
	}
}

func (e *LineString) GetType() string {
	return "LineString"
}

func (e *LineString) Count() int {
	return int(C.geojsonvt_line_string_get_points_count(e.ls))
}

func (e *LineString) GetPoint(i int) *Point {
	p := &Point{p: C.geojsonvt_line_string_get_point(e.ls, C.int(i))}
	runtime.SetFinalizer(p, (*Point).free)
	return p
}

func (e *LineString) GetPointXY(i int) (x, y int16) {
	var cx, cy C.short
	C.geojsonvt_line_string_get_point_xy(e.ls, C.int(i), &cx, &cy)
	x = int16(cx)
	y = int16(cy)
	return
}

func (e *LineString) getPoint(i int, pt *Point) {
	pt.p = C.geojsonvt_line_string_get_point(e.ls, C.int(i))
	runtime.SetFinalizer(pt, (*Point).free)
}

func (e *LineString) SetPoint(i int, x, y int16) {
	C.geojsonvt_line_string_update_point(e.ls, C.int(i), C.short(x), C.short(y))
}

func (e *LineString) AppendPoint(x, y int16) {
	C.geojsonvt_line_string_append_point(e.ls, C.short(x), C.short(y))
}

func (e *LineString) Geom() *Geometry {
	g := &Geometry{g: C.geojsonvt_line_string_to_geometry(e.ls)}
	runtime.SetFinalizer(g, (*Geometry).free)
	return g
}

func (e *LineString) Equal(b *LineString) bool {
	return bool(C.geojsonvt_line_string_equal(e.ls, b.ls))
}

func (e *LineString) Data() [][]int16 {
	ret := make([][]int16, e.Count())
	for i := range ret {
		p := e.GetPoint(i)
		ret[i] = p.Data()
	}
	return ret
}

type MultiPoint struct {
	mp *C.struct__geojsonvt_multi_point_t
}

func NewEmptyMultiPoint() *MultiPoint {
	p := &MultiPoint{mp: C.geojsonvt_multi_point_new_empty()}
	runtime.SetFinalizer(p, (*MultiPoint).free)
	return p
}

func NewMultiPoint(pts [][2]int16) *MultiPoint {
	ls := &MultiPoint{mp: C.geojsonvt_multi_point_new((*C.short)(unsafe.Pointer(&pts[0])), C.int(len(pts)))}
	runtime.SetFinalizer(ls, (*MultiPoint).free)
	return ls
}

func (e *MultiPoint) free() {
	if e.mp != nil {
		C.geojsonvt_multi_point_free(e.mp)
	}
}

func (e *MultiPoint) GetType() string {
	return "MultiPoint"
}

func (e *MultiPoint) Count() int {
	return int(C.geojsonvt_multi_point_get_points_count(e.mp))
}

func (e *MultiPoint) GetPointXY(i int) (x, y int16) {
	var cx, cy C.short
	C.geojsonvt_multi_point_get_point_xy(e.mp, C.int(i), &cx, &cy)
	x = int16(cx)
	y = int16(cy)
	return
}

func (e *MultiPoint) GetPoint(i int) *Point {
	p := &Point{p: C.geojsonvt_multi_point_get_point(e.mp, C.int(i))}
	runtime.SetFinalizer(p, (*Point).free)
	return p
}

func (e *MultiPoint) getPoint(i int, pt *Point) {
	pt.p = C.geojsonvt_multi_point_get_point(e.mp, C.int(i))
	runtime.SetFinalizer(pt, (*Point).free)
}

func (e *MultiPoint) SetPoint(i int, x, y int16) {
	C.geojsonvt_multi_point_update_point(e.mp, C.int(i), C.short(x), C.short(y))
}

func (e *MultiPoint) AppendPoint(x, y int16) {
	C.geojsonvt_multi_point_append_point(e.mp, C.short(x), C.short(y))
}

func (e *MultiPoint) Geom() *Geometry {
	g := &Geometry{g: C.geojsonvt_multi_point_to_geometry(e.mp)}
	runtime.SetFinalizer(g, (*Geometry).free)
	return g
}

func (e *MultiPoint) Equal(b *MultiPoint) bool {
	return bool(C.geojsonvt_multi_point_equal(e.mp, b.mp))
}

func (e *MultiPoint) Data() [][]int16 {
	ret := make([][]int16, e.Count())
	for i := range ret {
		p := e.GetPoint(i)
		ret[i] = p.Data()
	}
	return ret
}

type LinearRing struct {
	lr *C.struct__geojsonvt_linear_ring_t
}

func NewEmptyLinearRing() *LinearRing {
	p := &LinearRing{lr: C.geojsonvt_linear_ring_new_empty()}
	runtime.SetFinalizer(p, (*LinearRing).free)
	return p
}

func NewLinearRing(pts [][2]int16) *LinearRing {
	ls := &LinearRing{lr: C.geojsonvt_linear_ring_new((*C.short)(unsafe.Pointer(&pts[0])), C.int(len(pts)))}
	runtime.SetFinalizer(ls, (*LinearRing).free)
	return ls
}

func (e *LinearRing) free() {
	if e.lr != nil {
		C.geojsonvt_linear_ring_free(e.lr)
	}
}

func (e *LinearRing) GetType() string {
	return "LinearRing"
}

func (e *LinearRing) Count() int {
	return int(C.geojsonvt_linear_ring_get_points_count(e.lr))
}

func (e *LinearRing) GetPoint(i int) *Point {
	p := &Point{p: C.geojsonvt_linear_ring_get_point(e.lr, C.int(i))}
	runtime.SetFinalizer(p, (*Point).free)
	return p
}

func (e *LinearRing) SetPoint(i int, x, y int16) {
	C.geojsonvt_linear_ring_update_point(e.lr, C.int(i), C.short(x), C.short(y))
}

func (e *LinearRing) AppendPoint(x, y int16) {
	C.geojsonvt_linear_ring_append_point(e.lr, C.short(x), C.short(y))
}

func (e *LinearRing) getPoint(i int, pt *Point) {
	pt.p = C.geojsonvt_linear_ring_get_point(e.lr, C.int(i))
	runtime.SetFinalizer(pt, (*Point).free)
}

func (e *LinearRing) GetPointXY(i int) (x, y int16) {
	var cx, cy C.short
	C.geojsonvt_linear_ring_get_point_xy(e.lr, C.int(i), &cx, &cy)
	x = int16(cx)
	y = int16(cy)
	return
}

func (e *LinearRing) Equal(b *LinearRing) bool {
	return bool(C.geojsonvt_linear_ring_equal(e.lr, b.lr))
}

func (e *LinearRing) Data() [][]int16 {
	ret := make([][]int16, e.Count())
	for i := range ret {
		p := e.GetPoint(i)
		ret[i] = p.Data()
	}
	return ret
}

type Polygon struct {
	p *C.struct__geojsonvt_polygon_t
}

func NewEmptyPolygon() *Polygon {
	ls := &Polygon{p: C.geojsonvt_polygon_new_empty()}
	runtime.SetFinalizer(ls, (*Polygon).free)
	return ls
}

func NewPolygon(rings []*LinearRing) *Polygon {
	crings := make([]*C.struct__geojsonvt_linear_ring_t, len(rings))
	for i := range rings {
		crings[i] = rings[i].lr
	}

	ls := &Polygon{p: C.geojsonvt_polygon_new(&crings[0], C.int(len(rings)))}
	runtime.SetFinalizer(ls, (*Polygon).free)
	return ls
}

func (e *Polygon) free() {
	if e.p != nil {
		C.geojsonvt_polygon_free(e.p)
	}
}

func (e *Polygon) GetType() string {
	return "Polygon"
}

func (p *Polygon) GetExterior() *LinearRing {
	ls := &LinearRing{lr: C.geojsonvt_polygon_get_exterior(p.p)}
	runtime.SetFinalizer(ls, (*LinearRing).free)
	return ls
}

func (p *Polygon) SetExterior(ring *LinearRing) {
	C.geojsonvt_polygon_set_exterior(p.p, ring.lr)
}

func (e *Polygon) GetInteriorCount() int {
	return int(C.geojsonvt_polygon_get_interior_count(e.p))
}

func (e *Polygon) AppendInterior(lr *LinearRing) {
	C.geojsonvt_polygon_append_interior_ring(e.p, lr.lr)
}

func (e *Polygon) SetInterior(i int, lr *LinearRing) {
	C.geojsonvt_polygon_update_interior_ring(e.p, C.int(i), lr.lr)
}

func (e *Polygon) getInterior(i int, lr *LinearRing) {
	lr.lr = C.geojsonvt_polygon_get_interior(e.p, C.int(i))
	runtime.SetFinalizer(lr, (*LinearRing).free)
}

func (p *Polygon) GetInterior(i int) *LinearRing {
	ret := &LinearRing{}
	p.getInterior(i, ret)
	return ret
}

func (p *Polygon) GetInteriors() []LinearRing {
	icount := p.GetInteriorCount()
	ret := make([]LinearRing, icount)
	for i := 0; i < icount; i++ {
		p.getInterior(i, &ret[i])
	}
	return ret
}

func (e *Polygon) Geom() *Geometry {
	g := &Geometry{g: C.geojsonvt_polygon_to_geometry(e.p)}
	runtime.SetFinalizer(g, (*Geometry).free)
	return g
}

func (e *Polygon) Equal(b *Polygon) bool {
	return bool(C.geojsonvt_polygon_equal(e.p, b.p))
}

func (e *Polygon) Data() [][][]int16 {
	ret := make([][][]int16, e.GetInteriorCount()+1)
	el := e.GetExterior()
	ret[0] = el.Data()
	for i := range ret[1:] {
		p := e.GetInterior(i)
		ret[i+1] = p.Data()
	}
	return ret
}

type MultiLineString struct {
	mls *C.struct__geojsonvt_multi_line_string_t
}

func NewEmptyMultiLineString() *MultiLineString {
	ls := &MultiLineString{mls: C.geojsonvt_multi_line_string_new_empty()}
	runtime.SetFinalizer(ls, (*MultiLineString).free)
	return ls
}

func NewMultiLineString(lines []*LineString) *MultiLineString {
	clines := make([]*C.struct__geojsonvt_line_string_t, len(lines))
	for i := range lines {
		clines[i] = lines[i].ls
	}

	ls := &MultiLineString{mls: C.geojsonvt_multi_line_string_new(&clines[0], C.int(len(lines)))}
	runtime.SetFinalizer(ls, (*MultiLineString).free)
	return ls
}

func (e *MultiLineString) free() {
	if e.mls != nil {
		C.geojsonvt_multi_line_string_free(e.mls)
	}
}

func (e *MultiLineString) GetType() string {
	return "MultiLineString"
}

func (e *MultiLineString) Count() int {
	return int(C.geojsonvt_multi_line_get_count(e.mls))
}

func (e *MultiLineString) Append(lr *LineString) {
	C.geojsonvt_multi_line_string_append(e.mls, lr.ls)
}

func (e *MultiLineString) Set(i int, lr *LineString) {
	C.geojsonvt_multi_line_string_update(e.mls, C.int(i), lr.ls)
}

func (e *MultiLineString) Get(i int) *LineString {
	ret := &LineString{ls: C.geojsonvt_multi_line_string_get(e.mls, C.int(i))}
	runtime.SetFinalizer(ret, (*LineString).free)
	return ret
}

func (e *MultiLineString) Geom() *Geometry {
	g := &Geometry{g: C.geojsonvt_multi_line_string_to_geometry(e.mls)}
	runtime.SetFinalizer(g, (*Geometry).free)
	return g
}

func (e *MultiLineString) Equal(b *MultiLineString) bool {
	return bool(C.geojsonvt_multi_line_string_equal(e.mls, b.mls))
}

func (e *MultiLineString) getLineString(i int, lr *LineString) {
	lr.ls = C.geojsonvt_multi_line_string_get(e.mls, C.int(i))
	runtime.SetFinalizer(lr, (*LineString).free)
}

func (e *MultiLineString) Data() [][][]int16 {
	ret := make([][][]int16, e.Count())
	for i := range ret {
		p := e.Get(i)
		ret[i] = p.Data()
	}
	return ret
}

type MultiPolygon struct {
	mp *C.struct__geojsonvt_multi_polygon_t
}

func NewEmptyMultiPolygon() *MultiPolygon {
	ls := &MultiPolygon{mp: C.geojsonvt_multi_polygon_new_empty()}
	runtime.SetFinalizer(ls, (*MultiPolygon).free)
	return ls
}

func NewMultiPolygon(polys []*Polygon) *MultiPolygon {
	cpolys := make([]*C.struct__geojsonvt_polygon_t, len(polys))
	for i := range polys {
		cpolys[i] = polys[i].p
	}

	ls := &MultiPolygon{mp: C.geojsonvt_multi_polygon_new(&cpolys[0], C.int(len(polys)))}
	runtime.SetFinalizer(ls, (*MultiPolygon).free)
	return ls
}

func (e *MultiPolygon) free() {
	if e.mp != nil {
		C.geojsonvt_multi_polygon_free(e.mp)
	}
}

func (e *MultiPolygon) GetType() string {
	return "MultiPolygon"
}

func (e *MultiPolygon) Count() int {
	return int(C.geojsonvt_multi_polygon_get_count(e.mp))
}

func (e *MultiPolygon) Append(lr *Polygon) {
	C.geojsonvt_multi_polygon_append(e.mp, lr.p)
}

func (e *MultiPolygon) Set(i int, lr *Polygon) {
	C.geojsonvt_multi_polygon_update(e.mp, C.int(i), lr.p)
}

func (e *MultiPolygon) Get(i int) *Polygon {
	ret := &Polygon{p: C.geojsonvt_multi_polygon_get(e.mp, C.int(i))}
	runtime.SetFinalizer(ret, (*Polygon).free)
	return ret
}

func (e *MultiPolygon) get(i int, p *Polygon) {
	p.p = C.geojsonvt_multi_polygon_get(e.mp, C.int(i))
	runtime.SetFinalizer(p, (*Polygon).free)
}

func (e *MultiPolygon) Geom() *Geometry {
	g := &Geometry{g: C.geojsonvt_multi_polygon_to_geometry(e.mp)}
	runtime.SetFinalizer(g, (*Geometry).free)
	return g
}

func (e *MultiPolygon) Equal(b *MultiPolygon) bool {
	return bool(C.geojsonvt_multi_polygon_equal(e.mp, b.mp))
}

func (e *MultiPolygon) Data() [][][][]int16 {
	ret := make([][][][]int16, e.Count())
	for i := range ret {
		p := e.Get(i)
		ret[i] = p.Data()
	}
	return ret
}

type Geometry struct {
	g *C.struct__geojsonvt_geometry_t
}

func (e *Geometry) free() {
	if e.g != nil {
		C.geojsonvt_geometry_free(e.g)
	}
}

func (e *Geometry) GetType() string {
	if e.IsPoint() {
		return "Point"
	} else if e.IsLineString() {
		return "LineString"
	} else if e.IsPolygon() {
		return "Polygon"
	} else if e.IsMultiPoint() {
		return "MultiPoint"
	} else if e.IsMultiLineString() {
		return "MultiLineString"
	} else if e.IsMultiPolygon() {
		return "MultiPolygon"
	}
	return ""
}

func (e *Geometry) Empty() bool {
	return bool(C.geojsonvt_geometry_empty(e.g))
}

func (e *Geometry) IsPoint() bool {
	return bool(C.geojsonvt_geometry_is_point(e.g))
}

func (e *Geometry) IsLineString() bool {
	return bool(C.geojsonvt_geometry_is_line_string(e.g))
}

func (e *Geometry) IsPolygon() bool {
	return bool(C.geojsonvt_geometry_is_polygon(e.g))
}

func (e *Geometry) IsMultiPoint() bool {
	return bool(C.geojsonvt_geometry_is_multi_point(e.g))
}

func (e *Geometry) IsMultiLineString() bool {
	return bool(C.geojsonvt_geometry_is_multi_line_string(e.g))
}

func (e *Geometry) IsMultiPolygon() bool {
	return bool(C.geojsonvt_geometry_is_multi_polygon(e.g))
}

func (e *Geometry) Cast() interface{} {
	if e.IsPoint() {
		p := &Point{p: C.geojsonvt_geometry_cast_point(e.g)}
		runtime.SetFinalizer(p, (*Point).free)
		return p
	} else if e.IsLineString() {
		ls := &LineString{ls: C.geojsonvt_geometry_cast_line_string(e.g)}
		runtime.SetFinalizer(ls, (*LineString).free)
		return ls
	} else if e.IsPolygon() {
		ls := &Polygon{p: C.geojsonvt_geometry_cast_polygon(e.g)}
		runtime.SetFinalizer(ls, (*Polygon).free)
		return ls
	} else if e.IsMultiPoint() {
		ls := &MultiPoint{mp: C.geojsonvt_geometry_cast_multi_point(e.g)}
		runtime.SetFinalizer(ls, (*MultiPoint).free)
		return ls
	} else if e.IsMultiLineString() {
		ls := &MultiLineString{mls: C.geojsonvt_geometry_cast_multi_line_string(e.g)}
		runtime.SetFinalizer(ls, (*MultiLineString).free)
		return ls
	} else if e.IsMultiPolygon() {
		ls := &MultiPolygon{mp: C.geojsonvt_geometry_cast_multi_polygon(e.g)}
		runtime.SetFinalizer(ls, (*MultiPolygon).free)
		return ls
	}
	return nil
}

func (e *Geometry) Equal(b *Geometry) bool {
	return bool(C.geojsonvt_geometry_equal(e.g, b.g))
}

func (e *Geometry) Stringify() string {
	cjson := C.geojsonvt_geometry_stringify(e.g)
	defer C.free(unsafe.Pointer(cjson))
	return C.GoString(cjson)
}

type GeometryCollection struct {
	g *C.struct__geojsonvt_geometry_collection_t
}

func NewEmptyGeometryCollection() *GeometryCollection {
	ls := &GeometryCollection{g: C.geojsonvt_geometry_collection_new()}
	runtime.SetFinalizer(ls, (*GeometryCollection).free)
	return ls
}

func (e *GeometryCollection) free() {
	if e.g != nil {
		C.geojsonvt_geometry_collection_free(e.g)
	}
}

func (e *GeometryCollection) Empty() bool {
	return bool(C.geojsonvt_geometry_collection_empty(e.g))
}

func (e *GeometryCollection) Count() int {
	return int(C.geojsonvt_geometry_collection_get_count(e.g))
}

func (e *GeometryCollection) Append(geom *Geometry) {
	C.geojsonvt_geometry_collection_append(e.g, geom.g)
}

func (e *GeometryCollection) Set(i int, geom *Geometry) {
	C.geojsonvt_geometry_collection_update(e.g, C.int(i), geom.g)
}

func (e *GeometryCollection) Get(i int) *Geometry {
	geom := &Geometry{g: C.geojsonvt_geometry_collection_get(e.g, C.int(i))}
	runtime.SetFinalizer(geom, (*Geometry).free)
	return geom
}

func (e *GeometryCollection) ToGeom() geom.Collection {
	ret := make(geom.Collection, e.Count())
	for i := range ret {
		ret[i] = e.Get(i)
	}
	return ret
}
