package draco

// #include "draco_api.h"
import "C"
import "runtime"

type MeshBuilder struct {
	ref *C.struct__draco_mesh_builder_t
}

func (m *MeshBuilder) free() {
	if m.ref != nil {
		C.draco_mesh_builder_free(m.ref)
	}
}

func NewMeshBuilder() *MeshBuilder {
	m := &MeshBuilder{ref: C.draco_new_mesh_builder()}
	runtime.SetFinalizer(m, (*MeshBuilder).free)
	return m
}

func (m *MeshBuilder) Start(size int) {
	C.draco_mesh_builder_start(m.ref, C.int(size))
}

func (m *MeshBuilder) SetAttribute(numPoints int, src interface{}, att GeometryAttrType, ncomp int8, dt DataType) {

}

func (m *MeshBuilder) GetMesh() *Mesh {
	return &Mesh{PointCloud{ref: C.draco_mesh_builder_get(m.ref)}}
}
