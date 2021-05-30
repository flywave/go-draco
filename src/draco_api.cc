#include <cstring>

#include "draco/attributes/point_attribute.h"
#include "draco/compression/decode.h"
#include "draco/mesh/mesh.h"
#include "draco/point_cloud/point_cloud.h"
#include "draco_api.h"

draco_encoded_geometry_type draco_get_encoded_geometry_type(const char *data,
                                                            size_t data_size) {
  draco::DecoderBuffer buffer;
  buffer.Init(data, data_size);
  auto type = draco::Decoder::GetEncodedGeometryType(&buffer);
  if (!type.ok()) {
    return DRACO_EGT_INVALID;
  }
  return static_cast<draco_encoded_geometry_type>(type.value());
}

void draco_status_free(draco_status_t *status) { free(status); }

int draco_status_code(const draco_status_t *status) {
  return reinterpret_cast<const draco::Status *>(status)->code();
}

bool draco_status_ok(const draco_status_t *status) {
  return reinterpret_cast<const draco::Status *>(status)->ok();
}

size_t draco_status_error_msg_length(const draco_status_t *status) {
  auto msg =
      reinterpret_cast<const draco::Status *>(status)->error_msg_string();
  return msg.size() + 1;
}

size_t draco_status_error_msg(const draco_status_t *status, char *msg,
                              size_t length) {
  if (msg == nullptr) {
    return 0;
  }
  auto msg_ =
      reinterpret_cast<const draco::Status *>(status)->error_msg_string();
  if (msg_.size() >= length) {
    return 0;
  }
  memcpy(msg, msg_.c_str(), length);
  return msg_.size() + 1;
}

draco_decoder_t *draco_new_decoder() {
  return reinterpret_cast<draco_decoder_t *>(new draco::Decoder());
}

void draco_free(draco_decoder_t *decoder) { free(decoder); }

draco_status_t *draco_decoder_decode_mesh(draco_decoder_t *decoder,
                                          const char *data, size_t data_size,
                                          draco_mesh_t *out_mesh) {
  draco::DecoderBuffer buffer;
  buffer.Init(data, data_size);
  auto m = reinterpret_cast<draco::Mesh *>(out_mesh);
  const auto &last_status_ =
      reinterpret_cast<draco::Decoder *>(decoder)->DecodeBufferToGeometry(
          &buffer, m);
  return reinterpret_cast<draco_status_t *>(new draco::Status(last_status_));
}

draco_status_t *draco_decoder_decode_point_cloud(draco_decoder_t *decoder,
                                                 const char *data,
                                                 size_t data_size,
                                                 draco_point_cloud_t *out_pc) {
  draco::DecoderBuffer buffer;
  buffer.Init(data, data_size);
  auto m = reinterpret_cast<draco::PointCloud *>(out_pc);
  const auto &last_status_ =
      reinterpret_cast<draco::Decoder *>(decoder)->DecodeBufferToGeometry(
          &buffer, m);
  return reinterpret_cast<draco_status_t *>(new draco::Status(last_status_));
}

draco_mesh_t *draco_new_mesh() {
  return reinterpret_cast<draco_mesh_t *>(new draco::Mesh());
}

void draco_mesh_free(draco_mesh_t *mesh) { free(mesh); }

uint32_t draco_mesh_num_faces(const draco_mesh_t *mesh) {
  return reinterpret_cast<const draco::Mesh *>(mesh)->num_faces();
}

bool get_triangles_array(const draco::Mesh *m, const size_t out_size,
                       uint32_t *out_values) {
  const uint32_t num_faces = m->num_faces();
  if (num_faces * 3 * sizeof(uint32_t) != out_size) {
    return false;
  }

  for (uint32_t face_id = 0; face_id < num_faces; ++face_id) {
    const draco::Mesh::Face &face = m->face(draco::FaceIndex(face_id));
    out_values[face_id * 3 + 0] = face[0].value();
    out_values[face_id * 3 + 1] = face[1].value();
    out_values[face_id * 3 + 2] = face[2].value();
  }
  return true;
}

bool draco_mesh_get_indices(const draco_mesh_t *mesh, const size_t out_size,
                            uint32_t *out_values) {
  auto m = reinterpret_cast<const draco::Mesh *>(mesh);
  if (m->num_points() > std::numeric_limits<uint32_t>::max()) {
    return false;
  }

  return get_triangles_array(m, out_size, out_values);
}

size_t draco_point_attr_size(const draco_point_attr_t *attr) {
  return reinterpret_cast<const draco::PointAttribute *>(attr)->size();
}

draco_geometry_attr_type draco_point_attr_type(const draco_point_attr_t *attr) {
  auto attr_type =
      reinterpret_cast<const draco::PointAttribute *>(attr)->attribute_type();
  return static_cast<draco_geometry_attr_type>(attr_type);
}

draco_data_type draco_point_data_type(const draco_point_attr_t *attr) {
  auto attr_type =
      reinterpret_cast<const draco::PointAttribute *>(attr)->data_type();
  return static_cast<draco_data_type>(attr_type);
}

int8_t draco_point_attr_num_components(const draco_point_attr_t *attr) {
  return reinterpret_cast<const draco::PointAttribute *>(attr)
      ->num_components();
}

bool draco_point_attr_normalized(const draco_point_attr_t *attr) {
  return reinterpret_cast<const draco::PointAttribute *>(attr)->normalized();
}

int64_t draco_point_attr_byte_stride(const draco_point_attr_t *attr) {
  return reinterpret_cast<const draco::PointAttribute *>(attr)->byte_stride();
}

int64_t draco_point_attr_byte_offset(const draco_point_attr_t *attr) {
  return reinterpret_cast<const draco::PointAttribute *>(attr)->byte_offset();
}

uint32_t draco_point_attr_unique_id(const draco_point_attr_t *attr) {
  return reinterpret_cast<const draco::PointAttribute *>(attr)->unique_id();
}

draco_point_cloud_t *draco_new_point_cloud() {
  return reinterpret_cast<draco_point_cloud_t *>(new draco::PointCloud());
}

void draco_point_cloud_free(draco_point_cloud_t *pc) { free(pc); }

uint32_t draco_point_cloud_num_points(const draco_point_cloud_t *pc) {
  return reinterpret_cast<const draco::PointCloud *>(pc)->num_points();
}

int32_t draco_point_cloud_num_attrs(const draco_point_cloud_t *pc) {
  return reinterpret_cast<const draco::PointCloud *>(pc)->num_attributes();
}

const draco_point_attr_t *
draco_point_cloud_get_attribute(const draco_point_cloud_t *pc, int32_t att_id) {
  auto m = reinterpret_cast<const draco::PointCloud *>(pc);
  if (att_id < 0 || att_id > m->num_attributes()) {
    return nullptr;
  }
  auto attr = m->attribute(att_id);
  return reinterpret_cast<const draco_point_attr_t *>(attr);
}

int32_t
draco_point_cloud_get_named_attribute_id(const draco_point_cloud_t *pc,
                                         draco_geometry_attr_type geo_type) {
  auto type = static_cast<draco::GeometryAttribute::Type>(geo_type);
  return reinterpret_cast<const draco::PointCloud *>(pc)->GetNamedAttributeId(
      type);
}

const draco_point_attr_t *
draco_point_cloud_get_attribute_by_unique_id(const draco_point_cloud_t *pc,
                                             uint32_t unique_id) {
  auto m = reinterpret_cast<const draco::PointCloud *>(pc);
  auto attr = m->GetAttributeByUniqueId(unique_id);
  return reinterpret_cast<const draco_point_attr_t *>(attr);
}

template <class T>
static bool get_attribute_data_array_for_all_points(
    const draco::PointCloud *pc, const draco::PointAttribute *pa,
    draco::DataType type, size_t out_size, void *out_values) {
  const int components = pa->num_components();
  const int num_points = pc->num_points();
  const int data_size = num_points * components * sizeof(T);
  if (data_size != out_size) {
    return false;
  }
  const bool requested_type_matches = pa->data_type() == type;
  if (requested_type_matches && pa->is_mapping_identity()) {
    const auto ptr = pa->GetAddress(draco::AttributeValueIndex(0));
    ::memcpy(out_values, ptr, data_size);
    return true;
  }

  std::vector<T> values(components);
  int entry_id = 0;

  T *const typed_output = reinterpret_cast<T *>(out_values);
  for (draco::PointIndex i(0); i < num_points; ++i) {
    const draco::AttributeValueIndex val_index = pa->mapped_index(i);
    if (requested_type_matches) {
      pa->GetValue(val_index, values.data());
    } else {
      if (!pa->ConvertValue<T>(val_index, values.data())) {
        return false;
      }
    }
    for (int j = 0; j < components; ++j) {
      typed_output[entry_id++] = values[j];
    }
  }
  return true;
}

bool draco_point_cloud_get_attribute_data(const draco_point_cloud_t *pc,
                                         const draco_point_attr_t *pa,
                                         draco_data_type data_type,
                                         const size_t out_size,
                                         void *out_values) {
  auto pcc = reinterpret_cast<const draco::PointCloud *>(pc);
  auto pac = reinterpret_cast<const draco::PointAttribute *>(pa);
  switch (data_type) {
  case DRACO_DT_INT8:
    return get_attribute_data_array_for_all_points<int8_t>(
        pcc, pac, draco::DT_INT8, out_size, out_values);
  case DRACO_DT_INT16:
    return get_attribute_data_array_for_all_points<int16_t>(
        pcc, pac, draco::DT_INT16, out_size, out_values);
  case DRACO_DT_INT32:
    return get_attribute_data_array_for_all_points<int32_t>(
        pcc, pac, draco::DT_INT32, out_size, out_values);
  case DRACO_DT_UINT8:
    return get_attribute_data_array_for_all_points<uint8_t>(
        pcc, pac, draco::DT_UINT8, out_size, out_values);
  case DRACO_DT_UINT16:
    return get_attribute_data_array_for_all_points<uint16_t>(
        pcc, pac, draco::DT_UINT16, out_size, out_values);
  case DRACO_DT_UINT32:
    return get_attribute_data_array_for_all_points<uint32_t>(
        pcc, pac, draco::DT_UINT32, out_size, out_values);
  case DRACO_DT_FLOAT32:
    return get_attribute_data_array_for_all_points<float>(
        pcc, pac, draco::DT_FLOAT32, out_size, out_values);
  case DRACO_DT_FLOAT64:
    return get_attribute_data_array_for_all_points<double>(
        pcc, pac, draco::DT_FLOAT64, out_size, out_values);
  default:
    return false;
  }
}