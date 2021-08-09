package vtile

// #include <stdlib.h>
// #include <string.h>
// #include "vtile_c_api.h"
// #cgo CFLAGS: -I ../
// #cgo CXXFLAGS:  -I ../ -std=c++14
import "C"
import (
	"reflect"
	"runtime"
	"unsafe"
)

type Layer struct {
	l *C.struct__mvt_layer_t
}

func NewLayer() *Layer {
	ret := &Layer{l: C.mvt_layer_new()}
	runtime.SetFinalizer(ret, (*Layer).free)
	return ret
}

func NewLayerWithData(data []byte) *Layer {
	ret := &Layer{l: C.mvt_layer_new_with_data((*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)))}
	runtime.SetFinalizer(ret, (*Layer).free)
	return ret
}

func (v *Layer) free() {
	if v.l != nil {
		C.mvt_vector_layer_free(v.l)
	}
}

func (v *Layer) Valid() bool {
	return bool(C.mvt_layer_valid(v.l))
}

func (v *Layer) Empty() bool {
	return bool(C.mvt_layer_empty(v.l))
}

func (v *Layer) GetData() []byte {
	var si C.size_t
	cdata := C.mvt_layer_get_data(v.l, &si)

	var dataSlice []byte
	dataHeader := (*reflect.SliceHeader)((unsafe.Pointer(&dataSlice)))
	dataHeader.Cap = int(si)
	dataHeader.Len = int(si)
	dataHeader.Data = uintptr(unsafe.Pointer(cdata))

	ret := make([]byte, int(si))
	copy(ret, dataSlice)
	return ret
}

func (v *Layer) GetName() string {
	return C.GoString(C.mvt_layer_get_name(v.l))
}

func (v *Layer) GetVersion() uint32 {
	return uint32(C.mvt_layer_version(v.l))
}

func (v *Layer) GetExtent() uint32 {
	return uint32(C.mvt_layer_extent(v.l))
}

func (v *Layer) FeatureCount() int {
	return int(C.mvt_layer_num_features(v.l))
}

func (v *Layer) KeyTable() []string {
	var si C.size_t
	kt := C.mvt_layer_key_table(v.l, &si)
	defer C.mvt_layer_free_key_table(kt, si)

	var ktSlice []*C.char
	ktHeader := (*reflect.SliceHeader)((unsafe.Pointer(&ktSlice)))
	ktHeader.Cap = int(si)
	ktHeader.Len = int(si)
	ktHeader.Data = uintptr(unsafe.Pointer(kt))

	ret := make([]string, int(si))
	for i := range ktSlice {
		ret[i] = C.GoString(ktSlice[i])
	}
	return ret
}

func (v *Layer) GetKey(i int) string {
	cstr := C.mvt_layer_get_key(v.l, C.int(i))
	defer C.free(unsafe.Pointer(cstr))
	return C.GoString(cstr)
}

func (v *Layer) KeyTableCount() int {
	return int(C.mvt_layer_key_table_size(v.l))
}

func (v *Layer) ValueTable() []PropertyValue {
	var si C.size_t
	vt := C.mvt_layer_value_table(v.l, &si)
	defer C.mvt_layer_free_value_table(vt, si)

	var vtSlice []*C.struct__mvt_property_value_t
	vtHeader := (*reflect.SliceHeader)((unsafe.Pointer(&vtSlice)))
	vtHeader.Cap = int(si)
	vtHeader.Len = int(si)
	vtHeader.Data = uintptr(unsafe.Pointer(vt))

	ret := make([]PropertyValue, int(si))
	for i := range vtSlice {
		ret[i].v = vtSlice[i]
		runtime.SetFinalizer(&ret[i], (*PropertyValue).free)
	}
	return ret
}

func (v *Layer) KeyValueCount() int {
	return int(C.mvt_layer_key_value_size(v.l))
}

func (v *Layer) GetValue(i int) *PropertyValue {
	ret := &PropertyValue{v: C.mvt_layer_get_value(v.l, C.int(i))}
	runtime.SetFinalizer(ret, (*PropertyValue).free)
	return ret
}

func (v *Layer) NextFeature() *Feature {
	ret := &Feature{f: C.mvt_vector_layer_next_feature(v.l)}
	runtime.SetFinalizer(ret, (*Feature).free)
	return ret
}

func (v *Layer) ResetFeature() {
	C.mvt_layer_reset_feature(v.l)
}

func (v *Layer) GetFeature(index int) *Feature {
	ret := &Feature{f: C.mvt_vector_layer_get_feature_by_id(v.l, C.ulong(index))}
	runtime.SetFinalizer(ret, (*Feature).free)
	return ret
}
