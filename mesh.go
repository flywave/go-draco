package draco

// #include "draco_api.h"
import "C"
import (
	"runtime"
	"unsafe"
)

type Mesh struct {
	PointCloud
}

func (m *Mesh) free() {
	if m.ref != nil {
		C.draco_mesh_free(m.ref)
	}
}

func NewMesh() *Mesh {
	m := &Mesh{PointCloud{C.draco_new_mesh()}}
	runtime.SetFinalizer(m, (*Mesh).free)
	return m
}

func (m *Mesh) NumFaces() uint32 {
	return uint32(C.draco_mesh_num_faces(m.ref))
}

func (m *Mesh) Faces(buffer []uint32) []uint32 {
	n := m.NumFaces()
	if len(buffer) < int(n) {
		buffer = append(buffer, make([]uint32, int(n)-len(buffer))...)
	}
	C.draco_mesh_get_indices(m.ref, C.size_t(n*3*4), (*C.uint32_t)(unsafe.Pointer(&buffer[0])))
	return buffer[:n]
}
