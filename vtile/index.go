package vtile

// #include <stdlib.h>
// #include <string.h>
// #include "vtile_c_api.h"
// #cgo CFLAGS: -I ../ -std=c11
// #cgo CXXFLAGS:  -I ../ -std=c++14
// #cgo darwin CXXFLAGS: -Wno-enum-constexpr-conversion -Wno-c++11-narrowing
import "C"
import (
	"runtime"
	"unsafe"
)

type KeyIndex struct {
	idx *C.struct__mvt_key_index_t
}

func NewKeyIndex(lb *LayerBuilder) *KeyIndex {
	ret := &KeyIndex{idx: C.mvt_key_index_new(lb.m)}
	runtime.SetFinalizer(ret, (*KeyIndex).free)
	return ret
}

func (v *KeyIndex) Get(key string) uint32 {
	ckey := C.CString(key)
	defer C.free(unsafe.Pointer(ckey))
	return uint32(C.mvt_key_index_get(v.idx, ckey))
}

func (v *KeyIndex) free() {
	if v.idx != nil {
		C.mvt_key_index_free(v.idx)
	}
}

type Int32ValueIndex struct {
	idx *C.struct__mvt_int32_value_index_t
}

func NewInt32ValueIndex(lb *LayerBuilder) *Int32ValueIndex {
	ret := &Int32ValueIndex{idx: C.mvt_int32_value_index_new(lb.m)}
	runtime.SetFinalizer(ret, (*Int32ValueIndex).free)
	return ret
}

func (v *Int32ValueIndex) Get(val int32) uint32 {
	return uint32(C.mvt_int32_value_index_get(v.idx, C.int(val)))
}

func (v *Int32ValueIndex) free() {
	if v.idx != nil {
		C.mvt_int32_value_index_free(v.idx)
	}
}

type Int64ValueIndex struct {
	idx *C.struct__mvt_int64_value_index_t
}

func NewInt64ValueIndex(lb *LayerBuilder) *Int64ValueIndex {
	ret := &Int64ValueIndex{idx: C.mvt_int64_value_index_new(lb.m)}
	runtime.SetFinalizer(ret, (*Int64ValueIndex).free)
	return ret
}

func (v *Int64ValueIndex) Get(val int64) uint32 {
	return uint32(C.mvt_int64_value_index_get(v.idx, C.int64_t(val)))
}

func (v *Int64ValueIndex) free() {
	if v.idx != nil {
		C.mvt_int64_value_index_free(v.idx)
	}
}

type UInt64ValueIndex struct {
	idx *C.struct__mvt_uint64_value_index_t
}

func NewUInt64ValueIndex(lb *LayerBuilder) *UInt64ValueIndex {
	ret := &UInt64ValueIndex{idx: C.mvt_uint64_value_index_new(lb.m)}
	runtime.SetFinalizer(ret, (*UInt64ValueIndex).free)
	return ret
}

func (v *UInt64ValueIndex) Get(val uint64) uint32 {
	return uint32(C.mvt_uint64_value_index_get(v.idx, C.uint64_t(val)))
}

func (v *UInt64ValueIndex) free() {
	if v.idx != nil {
		C.mvt_uint64_value_index_free(v.idx)
	}
}

type UInt32ValueIndex struct {
	idx *C.struct__mvt_uint32_value_index_t
}

func NewUInt32ValueIndex(lb *LayerBuilder) *UInt32ValueIndex {
	ret := &UInt32ValueIndex{idx: C.mvt_uint32_value_index_new(lb.m)}
	runtime.SetFinalizer(ret, (*UInt32ValueIndex).free)
	return ret
}

func (v *UInt32ValueIndex) Get(val uint32) uint32 {
	return uint32(C.mvt_uint32_value_index_get(v.idx, C.uint(val)))
}

func (v *UInt32ValueIndex) free() {
	if v.idx != nil {
		C.mvt_uint32_value_index_free(v.idx)
	}
}

type FloatValueIndex struct {
	idx *C.struct__mvt_float_value_index_t
}

func NewFloatValueIndex(lb *LayerBuilder) *FloatValueIndex {
	ret := &FloatValueIndex{idx: C.mvt_float_value_index_new(lb.m)}
	runtime.SetFinalizer(ret, (*FloatValueIndex).free)
	return ret
}

func (v *FloatValueIndex) Get(val float32) uint32 {
	return uint32(C.mvt_float_value_index_get(v.idx, C.float(val)))
}

func (v *FloatValueIndex) free() {
	if v.idx != nil {
		C.mvt_float_value_index_free(v.idx)
	}
}

type DoubleValueIndex struct {
	idx *C.struct__mvt_double_value_index_t
}

func NewDoubleValueIndex(lb *LayerBuilder) *DoubleValueIndex {
	ret := &DoubleValueIndex{idx: C.mvt_double_value_index_new(lb.m)}
	runtime.SetFinalizer(ret, (*DoubleValueIndex).free)
	return ret
}

func (v *DoubleValueIndex) Get(val float64) uint32 {
	return uint32(C.mvt_double_value_index_get(v.idx, C.double(val)))
}

func (v *DoubleValueIndex) free() {
	if v.idx != nil {
		C.mvt_double_value_index_free(v.idx)
	}
}

type StringValueIndex struct {
	idx *C.struct__mvt_string_value_index_t
}

func NewStringValueIndex(lb *LayerBuilder) *StringValueIndex {
	ret := &StringValueIndex{idx: C.mvt_string_value_index_new(lb.m)}
	runtime.SetFinalizer(ret, (*StringValueIndex).free)
	return ret
}

func (v *StringValueIndex) Get(val string) uint32 {
	cval := C.CString(val)
	defer C.free(unsafe.Pointer(cval))
	return uint32(C.mvt_string_value_index_get(v.idx, cval))
}

func (v *StringValueIndex) free() {
	if v.idx != nil {
		C.mvt_string_value_index_free(v.idx)
	}
}

type BoolValueIndex struct {
	idx *C.struct__mvt_bool_value_index_t
}

func NewBoolValueIndex(lb *LayerBuilder) *BoolValueIndex {
	ret := &BoolValueIndex{idx: C.mvt_bool_value_index_new(lb.m)}
	runtime.SetFinalizer(ret, (*BoolValueIndex).free)
	return ret
}

func (v *BoolValueIndex) Get(val bool) uint32 {
	return uint32(C.mvt_bool_value_index_get(v.idx, C.bool(val)))
}

func (v *BoolValueIndex) free() {
	if v.idx != nil {
		C.mvt_bool_value_index_free(v.idx)
	}
}
