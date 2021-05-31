package draco

// #include "draco_api.h"
import "C"
import (
	"errors"
	"runtime"
	"unsafe"

	vec2d "github.com/flywave/go3d/float64/vec2"
	vec3d "github.com/flywave/go3d/float64/vec3"
	vec4d "github.com/flywave/go3d/float64/vec4"
	"github.com/flywave/go3d/vec2"
	"github.com/flywave/go3d/vec3"
	"github.com/flywave/go3d/vec4"
)

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

func (m *PointCloudBuilder) SetAttribute(numPoints int, src interface{}, att GeometryAttrType) error {
	var ncomp int8
	var dt DataType
	var pt unsafe.Pointer
	switch data := src.(type) {
	case []int8:
		ncomp = 1
		dt = DT_INT8
		pt = unsafe.Pointer(&data[0])
		break
	case []uint8:
		ncomp = 1
		dt = DT_UINT8
		pt = unsafe.Pointer(&data[0])
		break
	case []int16:
		ncomp = 1
		dt = DT_INT16
		pt = unsafe.Pointer(&data[0])
		break
	case []uint16:
		ncomp = 1
		dt = DT_UINT16
		pt = unsafe.Pointer(&data[0])
		break
	case []int32:
		ncomp = 1
		dt = DT_INT32
		pt = unsafe.Pointer(&data[0])
		break
	case []uint32:
		ncomp = 1
		dt = DT_UINT32
		pt = unsafe.Pointer(&data[0])
		break
	case []int64:
		ncomp = 1
		dt = DT_INT64
		pt = unsafe.Pointer(&data[0])
		break
	case []uint64:
		ncomp = 1
		dt = DT_UINT64
		pt = unsafe.Pointer(&data[0])
		break
	case []float32:
		ncomp = 1
		dt = DT_FLOAT32
		pt = unsafe.Pointer(&data[0])
		break
	case []float64:
		ncomp = 1
		dt = DT_FLOAT64
		pt = unsafe.Pointer(&data[0])
		break
	case []bool:
		ncomp = 1
		dt = DT_BOOL
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]int8:
		ncomp = 2
		dt = DT_INT8
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]uint8:
		ncomp = 2
		dt = DT_UINT8
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]int16:
		ncomp = 2
		dt = DT_INT16
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]uint16:
		ncomp = 2
		dt = DT_UINT16
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]int32:
		ncomp = 2
		dt = DT_INT32
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]uint32:
		ncomp = 2
		dt = DT_UINT32
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]int64:
		ncomp = 2
		dt = DT_INT64
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]uint64:
		ncomp = 2
		dt = DT_UINT64
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]float32:
		ncomp = 2
		dt = DT_FLOAT32
		pt = unsafe.Pointer(&data[0])
		break
	case []vec2.T:
		ncomp = 2
		dt = DT_FLOAT32
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]float64:
		ncomp = 2
		dt = DT_FLOAT64
		pt = unsafe.Pointer(&data[0])
		break
	case []vec2d.T:
		ncomp = 2
		dt = DT_FLOAT64
		pt = unsafe.Pointer(&data[0])
		break
	case [][2]bool:
		ncomp = 2
		dt = DT_BOOL
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]int8:
		ncomp = 3
		dt = DT_INT8
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]uint8:
		ncomp = 3
		dt = DT_UINT8
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]int16:
		ncomp = 3
		dt = DT_INT16
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]uint16:
		ncomp = 3
		dt = DT_UINT16
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]int32:
		ncomp = 3
		dt = DT_INT32
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]uint32:
		ncomp = 3
		dt = DT_UINT32
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]int64:
		ncomp = 3
		dt = DT_INT64
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]uint64:
		ncomp = 3
		dt = DT_UINT64
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]float32:
		ncomp = 3
		dt = DT_FLOAT32
		pt = unsafe.Pointer(&data[0])
		break
	case []vec3.T:
		ncomp = 3
		dt = DT_FLOAT32
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]float64:
		ncomp = 3
		dt = DT_FLOAT64
		pt = unsafe.Pointer(&data[0])
		break
	case []vec3d.T:
		ncomp = 3
		dt = DT_FLOAT64
		pt = unsafe.Pointer(&data[0])
		break
	case [][3]bool:
		ncomp = 3
		dt = DT_BOOL
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]int8:
		ncomp = 4
		dt = DT_INT8
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]uint8:
		ncomp = 4
		dt = DT_UINT8
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]int16:
		ncomp = 4
		dt = DT_INT16
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]uint16:
		ncomp = 4
		dt = DT_UINT16
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]int32:
		ncomp = 4
		dt = DT_INT32
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]uint32:
		ncomp = 4
		dt = DT_UINT32
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]int64:
		ncomp = 4
		dt = DT_INT64
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]uint64:
		ncomp = 4
		dt = DT_UINT64
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]float32:
		ncomp = 4
		dt = DT_FLOAT32
		pt = unsafe.Pointer(&data[0])
		break
	case []vec4.T:
		ncomp = 4
		dt = DT_FLOAT32
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]float64:
		ncomp = 4
		dt = DT_FLOAT64
		pt = unsafe.Pointer(&data[0])
		break
	case []vec4d.T:
		ncomp = 4
		dt = DT_FLOAT64
		pt = unsafe.Pointer(&data[0])
		break
	case [][4]bool:
		ncomp = 4
		dt = DT_BOOL
		pt = unsafe.Pointer(&data[0])
		break
	default:
		return errors.New("data not support")
	}
	C.draco_point_cloud_set_attribute(C.int(numPoints), m.ref, pt, C.uint(att), C.schar(ncomp), C.uint(dt))
	return nil
}

func (m *PointCloudBuilder) GetPointCloud() *PointCloud {
	pc := &PointCloud{ref: C.draco_point_cloud_builder_get(m.ref)}
	runtime.SetFinalizer(pc, (*PointCloud).free)
	return pc
}
