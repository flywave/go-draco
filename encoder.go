package draco

// #include <stdlib.h>
// #include <string.h>
// #include "draco_api.h"
// #cgo CFLAGS: -I ./lib
// #cgo CXXFLAGS: -I ./lib
import "C"
import (
	"reflect"
	"runtime"
	"unsafe"
)

type Encoder struct {
	ref *C.struct__draco_encoder_t
}

func (e *Encoder) free() {
	if e.ref != nil {
		C.draco_encoder_free(e.ref)
	}
}

func NewEncoder() *Encoder {
	d := &Encoder{C.draco_new_encoder()}
	runtime.SetFinalizer(d, (*Encoder).free)
	return d
}

func (d *Encoder) SetAttributeQuantization(attr GeometryAttrType, bits int32) {
	C.draco_encoder_set_attribute_quantization(d.ref, C.uint(attr), C.int(bits))
}

func (d *Encoder) EncodeMesh(m *Mesh) (error, []byte) {
	var data *C.char
	var size C.size_t
	defer C.free(unsafe.Pointer(data))
	s := C.draco_encoder_encode_mesh(d.ref, m.ref, &data, &size)

	var bufSlice []byte
	bufHeader := (*reflect.SliceHeader)((unsafe.Pointer(&bufSlice)))
	bufHeader.Cap = int(size)
	bufHeader.Len = int(size)
	bufHeader.Data = uintptr(unsafe.Pointer(data))

	ret := make([]byte, int(size))
	copy(bufSlice, ret)
	return newError(s), ret
}

func (d *Encoder) EncodePointCloud(pc *PointCloud) (error, []byte) {
	var data *C.char
	var size C.size_t
	defer C.free(unsafe.Pointer(data))
	s := C.draco_encoder_encode_point_cloud(d.ref, pc.ref, &data, &size)

	var bufSlice []byte
	bufHeader := (*reflect.SliceHeader)((unsafe.Pointer(&bufSlice)))
	bufHeader.Cap = int(size)
	bufHeader.Len = int(size)
	bufHeader.Data = uintptr(unsafe.Pointer(data))

	ret := make([]byte, int(size))
	copy(bufSlice, ret)
	return newError(s), ret
}
