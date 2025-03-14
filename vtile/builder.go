package vtile

// #include <stdlib.h>
// #include <string.h>
// #include "vtile_c_api.h"
// #cgo CFLAGS: -I ../ -std=c11
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"reflect"
	"runtime"
	"unsafe"
)

type TileBuilder struct {
	m *C.struct__mvt_tile_builder_t
}

func NewTileBuilder() *TileBuilder {
	ret := &TileBuilder{m: C.mvt_tile_builder_new()}
	runtime.SetFinalizer(ret, (*TileBuilder).free)
	return ret
}

func (v *TileBuilder) free() {
	if v.m != nil {
		C.mvt_tile_builder_free(v.m)
	}
}

func (v *TileBuilder) AddExistingLayer(layer *Layer) {
	C.mvt_tile_builder_add_existing_layer(v.m, layer.l)
}

func (v *TileBuilder) Serialize() []byte {
	var si C.size_t
	cdata := C.mvt_tile_builder_serialize(v.m, &si)
	defer C.free(unsafe.Pointer(cdata))

	var dSlice []byte
	dHeader := (*reflect.SliceHeader)((unsafe.Pointer(&dSlice)))
	dHeader.Cap = int(si)
	dHeader.Len = int(si)
	dHeader.Data = uintptr(unsafe.Pointer(cdata))

	ret := make([]byte, int(si))
	copy(ret, dSlice)
	return ret
}

func (v *TileBuilder) GetLayerBuilder(name string, version, extent uint32) *LayerBuilder {
	cname := C.CString(name)
	C.free(unsafe.Pointer(cname))
	ret := &LayerBuilder{m: C.mvt_tile_builder_get_layer_builder(v.m, cname, C.uint(version), C.uint(extent))}
	runtime.SetFinalizer(ret, (*LayerBuilder).free)
	return ret
}

type LayerBuilder struct {
	m *C.struct__mvt_layer_builder_t
}

func (v *LayerBuilder) free() {
	if v.m != nil {
		C.mvt_layer_builder_free(v.m)
	}
}

func (v *LayerBuilder) AddKey(name string) {
	cname := C.CString(name)
	C.free(unsafe.Pointer(cname))
	C.mvt_layer_builder_add_key(v.m, cname)
}

func (v *LayerBuilder) AddValue(value *PropertyValue) {
	C.mvt_layer_builder_add_value(v.m, value.v)
}

func (v *LayerBuilder) AddFeature(feat *Feature) {
	C.mvt_layer_builder_add_feature(v.m, feat.f)
}

func (v *LayerBuilder) GetPointFeatureBuilder() *PointFeatureBuilder {
	ret := &PointFeatureBuilder{m: C.mvt_layer_builder_get_point_feature_builder(v.m)}
	runtime.SetFinalizer(ret, (*PointFeatureBuilder).free)
	return ret
}

func (v *LayerBuilder) GetLineStringFeatureBuilder() *LineStringFeatureBuilder {
	ret := &LineStringFeatureBuilder{m: C.mvt_layer_builder_get_linestring_feature_builder(v.m)}
	runtime.SetFinalizer(ret, (*LineStringFeatureBuilder).free)
	return ret
}

func (v *LayerBuilder) GetPolygonFeatureBuilder() *PolygonFeatureBuilder {
	ret := &PolygonFeatureBuilder{m: C.mvt_layer_builder_get_polygon_feature_builder(v.m)}
	runtime.SetFinalizer(ret, (*PolygonFeatureBuilder).free)
	return ret
}

func (v *LayerBuilder) GetGeometryFeatureBuilder() *GeometryFeatureBuilder {
	ret := &GeometryFeatureBuilder{m: C.mvt_layer_builder_get_geometry_feature_builder(v.m)}
	runtime.SetFinalizer(ret, (*GeometryFeatureBuilder).free)
	return ret
}
