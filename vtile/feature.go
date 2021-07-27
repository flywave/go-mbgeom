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

type Feature struct {
	f *C.struct__mvt_feature_t
}

func NewFeature() *Feature {
	ret := &Feature{f: C.mvt_feature_new()}
	runtime.SetFinalizer(ret, (*Feature).free)
	return ret
}

func NewFeatureWithData(layer *Layer, data []byte) *Feature {
	ret := &Feature{f: C.mvt_feature_new_with_data(layer.l, (*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)))}
	runtime.SetFinalizer(ret, (*Feature).free)
	return ret
}

func (v *Feature) free() {
	C.mvt_feature_free(v.f)
}

func (v *Feature) Valid() bool {
	return bool(C.mvt_feature_valid(v.f))
}

func (v *Feature) Empty() bool {
	return bool(C.mvt_feature_empty(v.f))
}

func (v *Feature) GetID() uint64 {
	return uint64(C.mvt_feature_get_id(v.f))
}

func (v *Feature) HasID() bool {
	return bool(C.mvt_feature_has_id(v.f))
}

func (v *Feature) GetGeometryType() GeomType {
	gt := C.mvt_feature_get_geometry_type(v.f)
	return GeomType(gt)
}

func (v *Feature) GetGeometry() *Geometry {
	ret := &Geometry{g: C.mvt_feature_get_geometry(v.f)}
	runtime.SetFinalizer(ret, (*Geometry).free)
	return ret
}

func (v *Feature) PropertiesCount() int {
	return int(C.mvt_feature_num_properties(v.f))
}

func (v *Feature) NextProperty() *Property {
	ret := &Property{p: C.mvt_feature_next_property(v.f)}
	runtime.SetFinalizer(ret, (*Property).free)
	return ret
}

func (v *Feature) ResetProperty() {
	C.mvt_feature_reset_property(v.f)
}

func (v *Feature) NextPropertyIndexes() (k, val uint32) {
	var key, value C.uint
	ret := bool(C.mvt_feature_next_property_indexes(v.f, &key, &value))
	if ret {
		k = uint32(key)
		val = uint32(value)
	}
	return
}
