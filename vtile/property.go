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
	"reflect"
)

type Property struct {
	p *C.struct__mvt_property_t
}

func NewProperty() *Property {
	ret := &Property{p: C.mvt_property_new()}
	runtime.SetFinalizer(ret, (*Property).free)
	return ret
}

func NewPropertyWithKeyValue(key string, val *PropertyValue) *Property {
	ckey := C.CString(key)
	defer C.free(unsafe.Pointer(ckey))
	ret := &Property{p: C.mvt_property_new_with_keyvalue(ckey, val.v)}
	runtime.SetFinalizer(ret, (*Property).free)
	return ret
}

func (v *Property) free() {
	C.mvt_property_free(v.p)
}

func (v *Property) Valid() bool {
	return bool(C.mvt_property_valid(v.p))
}

func (v *Property) Key() string {
	ckey := C.mvt_feature_get_key(v.p)
	defer C.free(unsafe.Pointer(ckey))
	return C.GoString(ckey)
}

func (v *Property) Value() *PropertyValue {
	ret := &PropertyValue{v: C.mvt_feature_get_value(v.p)}
	runtime.SetFinalizer(ret, (*PropertyValue).free)
	return ret
}

type PropertyValue struct {
	v *C.struct__mvt_property_value_t
}

func NewPropertyValue() *PropertyValue {
	ret := &PropertyValue{v: C.mvt_property_value_new()}
	runtime.SetFinalizer(ret, (*PropertyValue).free)
	return ret
}

func NewPropertyValueWithData(data []byte) *PropertyValue {
	ret := &PropertyValue{v: C.mvt_property_value_new_with_data((*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)))}
	runtime.SetFinalizer(ret, (*PropertyValue).free)
	return ret
}

func (v *PropertyValue) free() {
	C.mvt_property_value_free(v.v)
}

func (v *PropertyValue) Valid() bool {
	return bool(C.mvt_property_value_valid(v.v))
}

func (v *PropertyValue) Type() PropertyValueType {
	return PropertyValueType(C.mvt_property_value_get_type(v.v))
}

func (v *PropertyValue) GetData() []byte {
	var si C.size_t
	cdata := C.mvt_property_value_get_data(v.v, &si)

	var dataSlice []byte
	dataHeader := (*reflect.SliceHeader)((unsafe.Pointer(&dataSlice)))
	dataHeader.Cap = int(si)
	dataHeader.Len = int(si)
	dataHeader.Data = uintptr(unsafe.Pointer(cdata))

	ret := make([]byte, int(si))
	copy(ret, dataSlice)
	return ret
}

func (v *PropertyValue) GetString() string {
	return C.GoString(C.mvt_property_value_get_string(v.v))
}

func (v *PropertyValue) GetFloat() float32 {
	return float32(C.mvt_property_value_get_float(v.v))
}

func (v *PropertyValue) GetDouble() float64 {
	return float64(C.mvt_property_value_get_double(v.v))
}

func (v *PropertyValue) GetInt64() int64 {
	return int64(C.mvt_property_value_get_int(v.v))
}

func (v *PropertyValue) GetUInt64() uint64 {
	return uint64(C.mvt_property_value_get_int(v.v))
}

func (v *PropertyValue) GetSInt64() int64 {
	return int64(C.mvt_property_value_get_sint(v.v))
}

func (v *PropertyValue) GetBool() bool {
	return bool(C.mvt_property_value_get_bool(v.v))
}