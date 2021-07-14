package geojson

// #include <stdlib.h>
// #include <string.h>
// #include "geojson_c_api.h"
// #cgo CFLAGS: -I ../
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"reflect"
	"runtime"
	"unsafe"

	"github.com/flywave/go-geom"
)

type Value struct {
	v *C.struct__mapbox_value_t
}

func NewValue() *Value {
	ret := &Value{v: C.mapbox_value_new()}
	runtime.SetFinalizer(ret, (*Value).free)
	return ret
}

func NewValueFromBool(b bool) *Value {
	ret := &Value{v: C.mapbox_value_from_bool(C.bool(b))}
	runtime.SetFinalizer(ret, (*Value).free)
	return ret
}

func NewValueFromUInt(b uint64) *Value {
	ret := &Value{v: C.mapbox_value_from_uint(C.ulong(b))}
	runtime.SetFinalizer(ret, (*Value).free)
	return ret
}

func NewValueFromInt(b int64) *Value {
	ret := &Value{v: C.mapbox_value_from_int(C.long(b))}
	runtime.SetFinalizer(ret, (*Value).free)
	return ret
}

func NewValueFromDouble(b float64) *Value {
	ret := &Value{v: C.mapbox_value_from_double(C.double(b))}
	runtime.SetFinalizer(ret, (*Value).free)
	return ret
}

func NewValueFromString(b string) *Value {
	cstr := C.CString(b)
	defer C.free(unsafe.Pointer(cstr))
	ret := &Value{v: C.mapbox_value_from_string(cstr)}
	runtime.SetFinalizer(ret, (*Value).free)
	return ret
}

func NewValueFromValues(vals []Value) *Value {
	cvals := make([]*C.struct__mapbox_value_t, len(vals))
	for i := range cvals {
		cvals[i] = vals[i].v
	}
	ret := &Value{v: C.mapbox_value_from_values(&cvals[0], C.int(len(vals)))}
	runtime.SetFinalizer(ret, (*Value).free)
	return ret
}

func NewValueFromKeyValues(maps map[string]Value) *Value {
	ckeys := make([]*C.char, len(maps))
	cvals := make([]*C.struct__mapbox_value_t, len(maps))
	i := 0
	for k, v := range maps {
		cvals[i] = v.v
		ckeys[i] = C.CString(k)
		i++
	}
	defer func() {
		for j := range ckeys {
			C.free(unsafe.Pointer(ckeys[j]))
		}
	}()
	ret := &Value{v: C.mapbox_value_from_keyvalues(&ckeys[0], &cvals[0], C.int(len(maps)))}
	runtime.SetFinalizer(ret, (*Value).free)
	return ret
}

func (v *Value) free() {
	C.mapbox_value_free(v.v)
}

func (v *Value) Empty() bool {
	return bool(C.mapbox_value_is_empty(v.v))
}

func (v *Value) IsNull() bool {
	return bool(C.mapbox_value_is_null(v.v))
}

func (v *Value) IsBool() bool {
	return bool(C.mapbox_value_is_bool(v.v))
}

func (v *Value) IsUint() bool {
	return bool(C.mapbox_value_is_uint(v.v))
}

func (v *Value) IsInt() bool {
	return bool(C.mapbox_value_is_int(v.v))
}

func (v *Value) IsDouble() bool {
	return bool(C.mapbox_value_is_double(v.v))
}

func (v *Value) IsString() bool {
	return bool(C.mapbox_value_is_string(v.v))
}

func (v *Value) IsVector() bool {
	return bool(C.mapbox_value_is_vector(v.v))
}

func (v *Value) IsMap() bool {
	return bool(C.mapbox_value_is_map(v.v))
}

func (v *Value) Get() interface{} {
	if v.IsBool() {
		return bool(C.mapbox_value_cast_bool(v.v))
	} else if v.IsUint() {
		return uint64(C.mapbox_value_cast_uint(v.v))
	} else if v.IsInt() {
		return int64(C.mapbox_value_cast_int(v.v))
	} else if v.IsDouble() {
		return float64(C.mapbox_value_cast_double(v.v))
	} else if v.IsString() {
		cstr := C.mapbox_value_cast_string(v.v)
		defer C.free(unsafe.Pointer(cstr))
		return C.GoString(cstr)
	} else if v.IsVector() {
		var count C.int
		cvals := C.mapbox_value_cast_vector(v.v, &count)

		defer C.mapbox_values_free(cvals)

		var valSlice []*C.struct__mapbox_value_t
		valHeader := (*reflect.SliceHeader)((unsafe.Pointer(&valSlice)))
		valHeader.Cap = int(count)
		valHeader.Len = int(count)
		valHeader.Data = uintptr(unsafe.Pointer(cvals))

		vals := make([]Value, int(count))
		for i := range vals {
			vals[i].v = valSlice[i]
			runtime.SetFinalizer(&vals[i], (*Value).free)
		}
		return vals
	} else if v.IsMap() {
		ret := &PropertyMap{m: C.mapbox_value_cast_map(v.v)}
		runtime.SetFinalizer(ret, (*PropertyMap).free)
		return ret
	}
	return nil
}

type PropertyMap struct {
	m *C.struct__mapbox_property_map_t
}

func NewPropertyMap() *PropertyMap {
	ret := &PropertyMap{m: C.mapbox_property_map_new()}
	runtime.SetFinalizer(ret, (*PropertyMap).free)
	return ret
}

func (v *PropertyMap) free() {
	C.mapbox_property_map_free(v.m)
}

func (v *PropertyMap) Get(key string) *Value {
	cstr := C.CString(key)
	defer C.free(unsafe.Pointer(cstr))
	ret := &Value{v: C.mapbox_property_map_get(v.m, cstr)}
	runtime.SetFinalizer(ret, (*Value).free)
	return ret
}

func (v *PropertyMap) Set(key string, val *Value) {
	cstr := C.CString(key)
	defer C.free(unsafe.Pointer(cstr))
	C.mapbox_property_map_set(v.m, cstr, val.v)
}

func (v *PropertyMap) Has(key string) bool {
	cstr := C.CString(key)
	defer C.free(unsafe.Pointer(cstr))
	return bool(C.mapbox_property_map_has(v.m, cstr))
}

func (v *PropertyMap) Empty() bool {
	return bool(C.mapbox_property_map_empty(v.m))
}

func (v *PropertyMap) Count() int {
	return int(C.mapbox_property_map_count(v.m))
}

func (v *PropertyMap) Keys() []string {
	var count C.int
	ckeys := C.mapbox_property_map_keys(v.m, &count)
	defer C.mapbox_property_map_free_keys(ckeys, count)

	keys := make([]string, int(count))

	var valSlice []*C.char
	valHeader := (*reflect.SliceHeader)((unsafe.Pointer(&valSlice)))
	valHeader.Cap = int(count)
	valHeader.Len = int(count)
	valHeader.Data = uintptr(unsafe.Pointer(ckeys))

	for i := range keys {
		keys[i] = C.GoString(valSlice[i])
	}
	return keys
}

func (v *PropertyMap) RawMap() map[string]interface{} {
	ret := make(map[string]interface{})
	keys := v.Keys()
	for i := range keys {
		ret[keys[i]] = v.Get(keys[i]).Get()
	}
	return ret
}

type Identifier struct {
	m *C.struct__mapbox_identifier_t
}

func (v *Identifier) free() {
	C.mapbox_identifier_free(v.m)
}

func NewIdentifierFromUInt(b uint64) *Identifier {
	ret := &Identifier{m: C.mapbox_identifier_from_uint(C.ulong(b))}
	runtime.SetFinalizer(ret, (*Identifier).free)
	return ret
}

func NewIdentifierFromInt(b int64) *Identifier {
	ret := &Identifier{m: C.mapbox_identifier_from_int(C.long(b))}
	runtime.SetFinalizer(ret, (*Identifier).free)
	return ret
}

func NewIdentifierFromDouble(b float64) *Identifier {
	ret := &Identifier{m: C.mapbox_identifier_from_double(C.double(b))}
	runtime.SetFinalizer(ret, (*Identifier).free)
	return ret
}

func NewIdentifierFromString(b string) *Identifier {
	cstr := C.CString(b)
	defer C.free(unsafe.Pointer(cstr))
	ret := &Identifier{m: C.mapbox_identifier_from_string(cstr)}
	runtime.SetFinalizer(ret, (*Identifier).free)
	return ret
}

func (v *Identifier) IsUint() bool {
	return bool(C.mapbox_identifier_is_uint(v.m))
}

func (v *Identifier) IsInt() bool {
	return bool(C.mapbox_identifier_is_int(v.m))
}

func (v *Identifier) IsDouble() bool {
	return bool(C.mapbox_identifier_is_double(v.m))
}

func (v *Identifier) IsString() bool {
	return bool(C.mapbox_identifier_is_string(v.m))
}

func (v *Identifier) Get() interface{} {
	if v.IsUint() {
		return uint64(C.mapbox_identifier_cast_uint(v.m))
	} else if v.IsInt() {
		return int64(C.mapbox_identifier_cast_int(v.m))
	} else if v.IsDouble() {
		return float64(C.mapbox_identifier_cast_double(v.m))
	} else if v.IsString() {
		cstr := C.mapbox_identifier_cast_string(v.m)
		defer C.free(unsafe.Pointer(cstr))
		return C.GoString(cstr)
	}
	return nil
}

type Feature struct {
	f *C.struct__mapbox_feature_t
}

func (v *Feature) free() {
	C.mapbox_feature_free(v.f)
}

func NewFeature(geom *Geometry) *Feature {
	ret := &Feature{f: C.mapbox_feature_new(geom.g)}
	runtime.SetFinalizer(ret, (*Feature).free)
	return ret
}

func (v *Feature) GetNative() unsafe.Pointer {
	return unsafe.Pointer(v.f)
}

func (v *Feature) SetIdentifier(id *Identifier) {
	C.mapbox_feature_set_identifier(v.f, id.m)
}

func (v *Feature) GetIdentifier() *Identifier {
	ret := &Identifier{m: C.mapbox_feature_get_identifier(v.f)}
	runtime.SetFinalizer(ret, (*Identifier).free)
	return ret
}

func (v *Feature) SetGeometry(geom *Geometry) {
	C.mapbox_feature_set_geometry(v.f, geom.g)
}

func (v *Feature) GetGeometry() *Geometry {
	g := &Geometry{g: C.mapbox_feature_get_geometry(v.f)}
	runtime.SetFinalizer(g, (*Geometry).free)
	return g
}

func (v *Feature) SetPropertyMap(props *PropertyMap) {
	C.mapbox_feature_set_property_map(v.f, props.m)
}

func (v *Feature) GetPropertyMap() *PropertyMap {
	ret := &PropertyMap{m: C.mapbox_feature_get_property_map(v.f)}
	runtime.SetFinalizer(ret, (*PropertyMap).free)
	return ret
}

func (v *Feature) Equal(b *Feature) bool {
	return bool(C.mapbox_feature_equal(v.f, b.f))
}

func (v *Feature) ToGeom() *geom.Feature {
	return &geom.Feature{ID: v.GetIdentifier().Get(), Geometry: v.GetGeometry(), Properties: v.GetPropertyMap().RawMap()}
}

type FeatureCollection struct {
	fc *C.struct__mapbox_feature_collection_t
}

func NewFeatureCollection() *FeatureCollection {
	ret := &FeatureCollection{fc: C.mapbox_feature_collection_new()}
	runtime.SetFinalizer(ret, (*FeatureCollection).free)
	return ret
}

func (v *FeatureCollection) GetNative() unsafe.Pointer {
	return unsafe.Pointer(v.fc)
}

func (v *FeatureCollection) free() {
	C.mapbox_feature_collection_free(v.fc)
}

func (v *FeatureCollection) Empty() bool {
	return bool(C.mapbox_feature_collection_empty(v.fc))
}

func (v *FeatureCollection) Append(feat *Feature) {
	C.mapbox_feature_collection_append(v.fc, feat.f)
}

func (v *FeatureCollection) Set(i int, feat *Feature) {
	C.mapbox_feature_collection_update(v.fc, C.int(i), feat.f)
}

func (v *FeatureCollection) Count() int {
	return int(C.mapbox_feature_collection_get_count(v.fc))
}

func (v *FeatureCollection) Get(i int) *Feature {
	return &Feature{f: C.mapbox_feature_collection_get(v.fc, C.int(i))}
}

func (v *FeatureCollection) ToGeom() *geom.FeatureCollection {
	ret := &geom.FeatureCollection{}
	ret.Features = make([]*geom.Feature, v.Count())
	for i := range ret.Features {
		ret.Features[i] = v.Get(i).ToGeom()
	}
	return ret
}
