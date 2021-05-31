package draco

// #include <stdlib.h>
// #include <string.h>
// #include "draco_api.h"
// #cgo CFLAGS: -I ./lib
// #cgo CXXFLAGS: -I ./lib
// #cgo linux LDFLAGS:  -L ./lib -Wl,--start-group  -lstdc++ -lm -pthread -ldraco -lc_draco -Wl,--end-group
// #cgo windows LDFLAGS: -L ./lib -ldraco -lc_draco
// #cgo darwin LDFLAGS: -L　./lib -ldraco -lc_draco
import "C"
import (
	"runtime"
	"unsafe"
)

func GetEncodedGeometryType(data []byte) EncodedGeometryType {
	egt := C.draco_get_encoded_geometry_type((*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)))
	return EncodedGeometryType(egt)
}

type Decoder struct {
	ref *C.struct__draco_decoder_t
}

func (d *Decoder) free() {
	if d.ref != nil {
		C.draco_decoder_free(d.ref)
	}
}

func NewDecoder() *Decoder {
	d := &Decoder{C.draco_new_decoder()}
	runtime.SetFinalizer(d, (*Decoder).free)
	return d
}

func (d *Decoder) DecodeMesh(m *Mesh, data []byte) error {
	s := C.draco_decoder_decode_mesh(d.ref, (*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)), m.ref)
	return newError(s)
}

func (d *Decoder) DecodePointCloud(pc *PointCloud, data []byte) error {
	s := C.draco_decoder_decode_point_cloud(d.ref, (*C.char)(unsafe.Pointer(&data[0])), C.size_t(len(data)), pc.ref)
	return newError(s)
}
