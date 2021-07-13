package wagyu

// #include <stdlib.h>
// #include <string.h>
// #include "wagyu_c_api.h"
// #cgo CFLAGS: -I ./
// #cgo CXXFLAGS:  -I ./ -std=c++14
import "C"
import (
	"reflect"
	"runtime"
	"unsafe"
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

func (v *Value) IsEmpty() bool {
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

func (v *PropertyMap) free() {
	C.mapbox_property_map_free(v.m)
}
