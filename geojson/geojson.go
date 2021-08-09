package geojson

// #include <stdlib.h>
// #include <string.h>
// #include "geojson_c_api.h"
// #cgo CFLAGS: -I ../
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"runtime"
	"unsafe"

	"github.com/flywave/go-geom"
)

type GeoJSON struct {
	m *C.struct__mapbox_geojson_t
}

func Parse(json string) *GeoJSON {
	cjson := C.CString(json)
	defer C.free(unsafe.Pointer(cjson))
	geojson := &GeoJSON{m: C.mapbox_geojson_parse(cjson)}
	runtime.SetFinalizer(geojson, (*GeoJSON).free)
	return geojson
}

func NewGeoJSONFromGeometry(geom *Geometry) *GeoJSON {
	geojson := &GeoJSON{m: C.mapbox_geojson_from_geometry(geom.g)}
	runtime.SetFinalizer(geojson, (*GeoJSON).free)
	return geojson
}

func NewGeoJSONFromFeature(feat *Feature) *GeoJSON {
	geojson := &GeoJSON{m: C.mapbox_geojson_from_feature(feat.f)}
	runtime.SetFinalizer(geojson, (*GeoJSON).free)
	return geojson
}

func NewGeoJSONFromFeatureCollection(feat *FeatureCollection) *GeoJSON {
	geojson := &GeoJSON{m: C.mapbox_geojson_from_feature_collection(feat.fc)}
	runtime.SetFinalizer(geojson, (*GeoJSON).free)
	return geojson
}

func NewGeoJSONFromGeomGeometry(geom geom.Geometry) *GeoJSON {
	g := NewGeomGeometry(geom)
	geojson := &GeoJSON{m: C.mapbox_geojson_from_geometry(g.g)}
	runtime.SetFinalizer(geojson, (*GeoJSON).free)
	return geojson
}

func NewGeoJSONFromGeomFeature(feat *geom.Feature) *GeoJSON {
	f := NewGeomFeature(feat)
	geojson := &GeoJSON{m: C.mapbox_geojson_from_feature(f.f)}
	runtime.SetFinalizer(geojson, (*GeoJSON).free)
	return geojson
}

func NewGeoJSONFromGeomFeatureCollection(feat *geom.FeatureCollection) *GeoJSON {
	ffeat := NewGeomFeatureCollection(feat)
	geojson := &GeoJSON{m: C.mapbox_geojson_from_feature_collection(ffeat.fc)}
	runtime.SetFinalizer(geojson, (*GeoJSON).free)
	return geojson
}

func (e *GeoJSON) free() {
	if e.m != nil {
		C.mapbox_geojson_free(e.m)
	}
}

func (e *GeoJSON) GetNative() unsafe.Pointer {
	return unsafe.Pointer(e.m)
}

func (e *GeoJSON) Empty() bool {
	return bool(C.mapbox_geojson_is_empty(e.m))
}

func (e *GeoJSON) IsGeometry() bool {
	return bool(C.mapbox_geojson_is_geometry(e.m))
}

func (e *GeoJSON) GetGeometry() *Geometry {
	return &Geometry{g: C.mapbox_geojson_get_geometry(e.m)}
}

func (e *GeoJSON) SetGeometry(geom *Geometry) {
	C.mapbox_geojson_set_geometry(e.m, geom.g)
}

func (e *GeoJSON) IsFeature() bool {
	return bool(C.mapbox_geojson_is_feature(e.m))
}

func (e *GeoJSON) GetFeature() *Feature {
	return &Feature{f: C.mapbox_geojson_get_feature(e.m)}
}

func (e *GeoJSON) SetFeature(feat *Feature) {
	C.mapbox_geojson_set_feature(e.m, feat.f)
}

func (e *GeoJSON) IsFeatureCollection() bool {
	return bool(C.mapbox_geojson_is_feature_collection(e.m))
}

func (e *GeoJSON) GetFeatureCollection() *FeatureCollection {
	return &FeatureCollection{fc: C.mapbox_geojson_get_feature_collection(e.m)}
}

func (e *GeoJSON) SetFeatureCollection(feat *FeatureCollection) {
	C.mapbox_geojson_set_feature_collection(e.m, feat.fc)
}

func (e *GeoJSON) Get() interface{} {
	if e.IsFeature() {
		return e.GetFeature()
	} else if e.IsGeometry() {
		return e.GetGeometry()
	} else if e.IsFeatureCollection() {
		return e.GetFeatureCollection()
	}
	return nil
}

func (e *GeoJSON) Stringify() string {
	cjson := C.mapbox_geojson_stringify(e.m)
	defer C.free(unsafe.Pointer(cjson))
	return C.GoString(cjson)
}
