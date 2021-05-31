package draco

// #include "draco_api.h"
import "C"
import "runtime"

type PointCloudBuilder struct {
	ref *C.struct__draco_point_cloud_builder_t
}

func (m *PointCloudBuilder) free() {
	if m.ref != nil {
		C.draco_point_cloud_builder_free(m.ref)
	}
}

func NewPointCloudBuilder() *PointCloudBuilder {
	m := &PointCloudBuilder{ref: C.draco_new_point_cloud_builder()}
	runtime.SetFinalizer(m, (*PointCloudBuilder).free)
	return m
}

func (m *PointCloudBuilder) Start(size int) {
	C.draco_point_cloud_builder_start(m.ref, C.int(size))
}

func (m *PointCloudBuilder) SetAttribute(numPoints int, src interface{}, att GeometryAttrType, ncomp int8, dt DataType) {

}

func (m *PointCloudBuilder) GetPointCloud() *PointCloud {
	return &PointCloud{ref: C.draco_point_cloud_builder_get(m.ref)}
}
