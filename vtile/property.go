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

type Property struct {
	p *C.struct__mvt_property_t
}

func NewProperty() *Property {
	ret := &Property{p: C.mvt_property_new()}
	runtime.SetFinalizer(ret, (*Property).free)
	return ret
}

func (v *Property) free() {
	C.mvt_property_free(v.p)
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
