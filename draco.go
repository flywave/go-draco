package draco

// #include "draco_api.h"
import "C"
import (
	"fmt"
	"reflect"
	"unsafe"
)

type EncodedGeometryType int

const (
	EGT_INVALID EncodedGeometryType = iota - 1
	EGT_POINT_CLOUD
	EGT_TRIANGULAR_MESH
)

type GeometryAttrType int

const (
	GAT_INVALID GeometryAttrType = iota - 1
	GAT_POSITION
	GAT_NORMAL
	GAT_COLOR
	GAT_TEX_COORD
	GAT_GENERIC
)

type DataType int

const (
	DT_INVALID DataType = iota
	DT_INT8
	DT_UINT8
	DT_INT16
	DT_UINT16
	DT_INT32
	DT_UINT32
	DT_INT64
	DT_UINT64
	DT_FLOAT32
	DT_FLOAT64
	DT_BOOL
)

func (dt DataType) Size() uint32 {
	switch dt {
	case DT_INT8, DT_UINT8, DT_BOOL:
		return 1
	case DT_INT16, DT_UINT16:
		return 2
	case DT_INT32, DT_UINT32, DT_FLOAT32:
		return 4
	case DT_INT64, DT_UINT64, DT_FLOAT64:
		return 8
	default:
		panic("draco-go: unsupported data type")
	}
}

func (dt DataType) goType() reflect.Type {
	switch dt {
	case DT_BOOL:
		return reflect.TypeOf((*bool)(nil)).Elem()
	case DT_INT8:
		return reflect.TypeOf((*int8)(nil)).Elem()
	case DT_UINT8:
		return reflect.TypeOf((*uint8)(nil)).Elem()
	case DT_INT16:
		return reflect.TypeOf((*int16)(nil)).Elem()
	case DT_UINT16:
		return reflect.TypeOf((*uint16)(nil)).Elem()
	case DT_INT32:
		return reflect.TypeOf((*int32)(nil)).Elem()
	case DT_UINT32:
		return reflect.TypeOf((*uint32)(nil)).Elem()
	case DT_FLOAT32:
		return reflect.TypeOf((*float32)(nil)).Elem()
	case DT_INT64:
		return reflect.TypeOf((*int64)(nil)).Elem()
	case DT_UINT64:
		return reflect.TypeOf((*uint64)(nil)).Elem()
	case DT_FLOAT64:
		return reflect.TypeOf((*float64)(nil)).Elem()
	default:
		panic("draco-go: unsupported data type")
	}
}

type Error struct {
	Code    int
	Message string
}

func (e *Error) Error() string {
	return fmt.Sprintf("draco: [%d] %s", e.Code, e.Message)
}

func newError(s *C.struct__draco_status_t) error {
	defer C.draco_status_free(s)
	if C.draco_status_ok(s) {
		return nil
	}
	errLen := C.draco_status_error_msg_length(s)
	errMsg := make([]C.char, errLen)
	errMsgPtr := (*C.char)(unsafe.Pointer(&errMsg[0]))
	C.draco_status_error_msg(s, errMsgPtr, errLen)
	return &Error{
		Code:    int(C.draco_status_code(s)),
		Message: C.GoStringN(errMsgPtr, C.int(errLen)-1),
	}
}

type PointAttr struct {
	ref *C.struct__draco_point_attr_t
}

func (pa *PointAttr) Type() GeometryAttrType {
	return GeometryAttrType(C.draco_point_attr_type(pa.ref))
}

func (pa *PointAttr) DataType() DataType {
	return DataType(C.draco_point_data_type(pa.ref))
}

func (pa *PointAttr) NumComponents() int8 {
	return int8(C.draco_point_attr_num_components(pa.ref))
}

func (pa *PointAttr) Normalized() bool {
	return bool(C.draco_point_attr_normalized(pa.ref))
}

func (pa *PointAttr) ByteStride() int64 {
	return int64(C.draco_point_attr_byte_stride(pa.ref))
}

func (pa *PointAttr) ByteOffset() int64 {
	return int64(C.draco_point_attr_byte_offset(pa.ref))
}

func (pa *PointAttr) UniqueID() uint32 {
	return uint32(C.draco_point_attr_unique_id(pa.ref))
}
