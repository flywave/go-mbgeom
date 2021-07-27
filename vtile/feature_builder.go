package vtile

// #include <stdlib.h>
// #include <string.h>
// #include "vtile_c_api.h"
// #cgo CFLAGS: -I ../
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"runtime"
)

type PropertyMapper struct {
	m *C.struct__mvt_property_mapper_t
}

func NewPropertyMapper(layer *Layer, layerBuilder *LayerBuilder) *PropertyMapper {
	ret := &PropertyMapper{m: C.mvt_property_mapper_new(layer.l, layerBuilder.m)}
	runtime.SetFinalizer(ret, (*PropertyMapper).free)
	return ret
}

func (v *PropertyMapper) free() {
	C.mvt_property_mapper_free(v.m)
}

func (v *PropertyMapper) MapKey(key uint32) uint32 {
	return uint32(C.mvt_property_mapper_map_key(v.m, C.uint(key)))
}

func (v *PropertyMapper) MapValue(val uint32) uint32 {
	return uint32(C.mvt_property_mapper_map_key(v.m, C.uint(val)))
}

func (v *PropertyMapper) Map(key uint32, val uint32) (uint32, uint32) {
	var mk, mv C.uint
	C.mvt_property_mapper_map_keyvalue(v.m, C.uint(key), C.uint(val), &mk, &mv)
	return uint32(mk), uint32(mv)
}

type PointFeatureBuilder struct {
	m *C.struct__mvt_point_feature_builder_t
}

func (v *PointFeatureBuilder) free() {
	C.mvt_point_feature_builder_free(v.m)
}

func (v *PointFeatureBuilder) SetID(id uint64) {
	C.mvt_point_feature_builder_set_id(v.m, C.ulong(id))
}

func (v *PointFeatureBuilder) CopyID(feat *Feature) {
	C.mvt_point_feature_builder_copy_id(v.m, feat.f)
}

func (v *PointFeatureBuilder) AddProperty(p *Property) {
	C.mvt_point_feature_builder_add_property(v.m, p.p)
}

func (v *PointFeatureBuilder) CopyProperties(feat *Feature) {
	C.mvt_point_feature_builder_copy_properties(v.m, feat.f)
}

func (v *PointFeatureBuilder) CopyPropertiesWithMapper(feat *Feature, mapper *PropertyMapper) {
	C.mvt_point_feature_builder_copy_properties_with_mapper(v.m, feat.f, mapper.m)
}

func (v *PointFeatureBuilder) Commit() {
	C.mvt_point_feature_builder_commit(v.m)
}

func (v *PointFeatureBuilder) Rollback() {
	C.mvt_point_feature_builder_rollback(v.m)
}

func (v *PointFeatureBuilder) AddPoint(x, y int32) {
	C.mvt_point_feature_builder_add_point(v.m, C.int(x), C.int(y))
}

func (v *PointFeatureBuilder) SetPoint(x, y int32) {
	C.mvt_point_feature_builder_set_point(v.m, C.int(x), C.int(y))
}

type LineStringFeatureBuilder struct {
	m *C.struct__mvt_linestring_feature_builder_t
}

func (v *LineStringFeatureBuilder) free() {
	C.mvt_linestring_feature_builder_free(v.m)
}

func (v *LineStringFeatureBuilder) SetID(id uint64) {
	C.mvt_linestring_feature_builder_set_id(v.m, C.ulong(id))
}

func (v *LineStringFeatureBuilder) CopyID(feat *Feature) {
	C.mvt_linestring_feature_builder_copy_id(v.m, feat.f)
}

func (v *LineStringFeatureBuilder) AddProperty(p *Property) {
	C.mvt_linestring_feature_builder_add_property(v.m, p.p)
}

func (v *LineStringFeatureBuilder) CopyProperties(feat *Feature) {
	C.mvt_linestring_feature_builder_copy_properties(v.m, feat.f)
}

func (v *LineStringFeatureBuilder) CopyPropertiesWithMapper(feat *Feature, mapper *PropertyMapper) {
	C.mvt_linestring_feature_builder_copy_properties_with_mapper(v.m, feat.f, mapper.m)
}

func (v *LineStringFeatureBuilder) Commit() {
	C.mvt_linestring_feature_builder_commit(v.m)
}

func (v *LineStringFeatureBuilder) Rollback() {
	C.mvt_linestring_feature_builder_rollback(v.m)
}

func (v *LineStringFeatureBuilder) AddLineString(count int) {
	C.mvt_linestring_feature_builder_add_linestring(v.m, C.int(count))
}

func (v *LineStringFeatureBuilder) SetPoint(x, y int32) {
	C.mvt_linestring_feature_builder_set_point(v.m, C.int(x), C.int(y))
}

type PolygonFeatureBuilder struct {
	m *C.struct__mvt_polygon_feature_builder_t
}

func (v *PolygonFeatureBuilder) free() {
	C.mvt_polygon_feature_builder_free(v.m)
}

func (v *PolygonFeatureBuilder) SetID(id uint64) {
	C.mvt_polygon_feature_builder_set_id(v.m, C.ulong(id))
}

func (v *PolygonFeatureBuilder) CopyID(feat *Feature) {
	C.mvt_polygon_feature_builder_copy_id(v.m, feat.f)
}

func (v *PolygonFeatureBuilder) AddProperty(p *Property) {
	C.mvt_polygon_feature_builder_add_property(v.m, p.p)
}

func (v *PolygonFeatureBuilder) CopyProperties(feat *Feature) {
	C.mvt_polygon_feature_builder_copy_properties(v.m, feat.f)
}

func (v *PolygonFeatureBuilder) CopyPropertiesWithMapper(feat *Feature, mapper *PropertyMapper) {
	C.mvt_polygon_feature_builder_copy_properties_with_mapper(v.m, feat.f, mapper.m)
}

func (v *PolygonFeatureBuilder) Commit() {
	C.mvt_polygon_feature_builder_commit(v.m)
}

func (v *PolygonFeatureBuilder) Rollback() {
	C.mvt_polygon_feature_builder_rollback(v.m)
}

func (v *PolygonFeatureBuilder) AddRing(count int) {
	C.mvt_polygon_feature_builder_add_ring(v.m, C.int(count))
}

func (v *PolygonFeatureBuilder) SetPoint(x, y int32) {
	C.mvt_polygon_feature_builder_set_point(v.m, C.int(x), C.int(y))
}

func (v *PolygonFeatureBuilder) CloseRing() {
	C.mvt_polygon_feature_builder_close_ring(v.m)
}

type GeometryFeatureBuilder struct {
	m *C.struct__mvt_geometry_feature_builder_t
}

func (v *GeometryFeatureBuilder) free() {
	C.mvt_geometry_feature_builder_free(v.m)
}

func (v *GeometryFeatureBuilder) SetID(id uint64) {
	C.mvt_geometry_feature_builder_set_id(v.m, C.ulong(id))
}

func (v *GeometryFeatureBuilder) CopyID(feat *Feature) {
	C.mvt_geometry_feature_builder_copy_id(v.m, feat.f)
}

func (v *GeometryFeatureBuilder) AddProperty(p *Property) {
	C.mvt_geometry_feature_builder_add_property(v.m, p.p)
}

func (v *GeometryFeatureBuilder) CopyProperties(feat *Feature) {
	C.mvt_geometry_feature_builder_copy_properties(v.m, feat.f)
}

func (v *GeometryFeatureBuilder) CopyPropertiesWithMapper(feat *Feature, mapper *PropertyMapper) {
	C.mvt_geometry_feature_builder_copy_properties_with_mapper(v.m, feat.f, mapper.m)
}

func (v *GeometryFeatureBuilder) Commit() {
	C.mvt_geometry_feature_builder_commit(v.m)
}

func (v *GeometryFeatureBuilder) Rollback() {
	C.mvt_geometry_feature_builder_rollback(v.m)
}

func (v *GeometryFeatureBuilder) SetGeometry(geom *Geometry) {
	C.mvt_geometry_feature_builder_set_geometry(v.m, geom.g)
}
