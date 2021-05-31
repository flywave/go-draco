#include <cstring>

#include "draco/attributes/point_attribute.h"
#include "draco/compression/decode.h"
#include "draco/compression/encode.h"
#include "draco/mesh/mesh.h"
#include "draco/mesh/triangle_soup_mesh_builder.h"
#include "draco/point_cloud/point_cloud.h"
#include "draco/point_cloud/point_cloud_builder.h"
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

void draco_status_free(draco_status_t *status) {
  delete reinterpret_cast<draco::Status *>(status);
}

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

void draco_decoder_free(draco_decoder_t *decoder) {
  delete reinterpret_cast<draco::Decoder *>(decoder);
}

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

void draco_mesh_free(draco_mesh_t *mesh) {
  delete reinterpret_cast<draco::Mesh *>(mesh);
}

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

void draco_point_cloud_free(draco_point_cloud_t *pc) {
  delete reinterpret_cast<draco::PointCloud *>(pc);
}

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

draco_encoder_t *draco_new_encoder() {
  return reinterpret_cast<draco_encoder_t *>(new draco::Encoder());
}

void draco_encoder_free(draco_encoder_t *encoder) {
  delete reinterpret_cast<draco::Encoder *>(encoder);
}

void draco_encoder_set_attribute_quantization(draco_encoder_t *encoder,
                                              uint32_t att, int bits) {
  draco::Encoder *enc = reinterpret_cast<draco::Encoder *>(encoder);
  enc->SetAttributeQuantization(
      static_cast<draco::GeometryAttribute::Type>(att), bits);
}

static draco::Status encode_to_buffer(draco::Encoder &encoder,
                                      draco::Mesh *mesh,
                                      draco::EncoderBuffer *buffer) {
  return encoder.EncodeMeshToBuffer(*mesh, buffer);
}

static draco::Status encode_to_buffer(draco::Encoder &encoder,
                                      draco::PointCloud *mesh,
                                      draco::EncoderBuffer *buffer) {
  return encoder.EncodePointCloudToBuffer(*mesh, buffer);
}

draco_status_t *draco_encoder_encode_mesh(draco_encoder_t *encoder,
                                          draco_mesh_t *in_mesh,
                                          char **out_data, size_t *data_size) {
  draco::Encoder *enc = reinterpret_cast<draco::Encoder *>(encoder);
  draco::Mesh *m = reinterpret_cast<draco::Mesh *>(in_mesh);
  draco::EncoderBuffer buffer;

  draco::Status status = encode_to_buffer(*enc, m, &buffer);
  *out_data = (char *)malloc(static_cast<int>(buffer.size()));
  if (*out_data) {
    memcpy(*out_data, buffer.data(), buffer.size());
    *data_size = static_cast<int>(buffer.size());
  }
  return reinterpret_cast<draco_status_t *>(new draco::Status(status));
}

draco_status_t *draco_encoder_encode_point_cloud(draco_encoder_t *encoder,
                                                 draco_point_cloud_t *in_pc,
                                                 char **out_data,
                                                 size_t *data_size) {
  draco::Encoder *enc = reinterpret_cast<draco::Encoder *>(encoder);
  draco::PointCloud *pc = reinterpret_cast<draco::PointCloud *>(in_pc);

  draco::EncoderBuffer buffer;

  draco::Status status = encode_to_buffer(*enc, pc, &buffer);

  *out_data = (char *)malloc(static_cast<int>(buffer.size()));
  if (*out_data) {
    memcpy(*out_data, buffer.data(), buffer.size());
    *data_size = static_cast<int>(buffer.size());
  }
  return reinterpret_cast<draco_status_t *>(new draco::Status(status));
}

template <class T>
int draco_set_mesh_attribute(int num_faces, draco::TriangleSoupMeshBuilder &mb,
                             const T *src, draco::GeometryAttribute::Type att,
                             int8_t ncomp, draco::DataType dt) {
  int att_id = -1;
  if (src) {
    att_id = mb.AddAttribute(att, ncomp, dt);
    for (int f = 0; f < num_faces; ++f, src += (3 * ncomp)) {
      mb.SetAttributeValuesForFace(att_id, draco::FaceIndex(f), src, src + ncomp,
                                   src + (2 * ncomp));
    }
  }
  return att_id;
};

template <class T>
int draco_set_mesh_attribute(int num_points, draco::PointCloudBuilder &pcb,
                             const T *src, draco::GeometryAttribute::Type att,
                             int8_t ncomp, draco::DataType dt) {
  int att_id = -1;
  if (src) {
    att_id = pcb.AddAttribute(att, ncomp, dt);
    for (draco::PointIndex i(0); i < num_points; ++i) {
      pcb.SetAttributeValueForPoint(att_id, i, src + (i.value() * ncomp));
    }
  }
  return att_id;
}

draco_point_cloud_builder_t *draco_new_point_cloud_builder() {
  return reinterpret_cast<draco_point_cloud_builder_t *>(
      new draco::PointCloudBuilder());
}

void draco_point_cloud_builder_free(draco_point_cloud_builder_t *builder) {
  delete reinterpret_cast<draco::PointCloudBuilder *>(builder);
}

void draco_point_cloud_builder_start(draco_point_cloud_builder_t *builder,
                                     int size) {
  draco::PointCloudBuilder *b =
      reinterpret_cast<draco::PointCloudBuilder *>(builder);
  b->Start(size);
}

static std::unique_ptr<draco::Mesh>
finalize_builder(draco::TriangleSoupMeshBuilder &builder) {
  return builder.Finalize();
}

static std::unique_ptr<draco::PointCloud>
finalize_builder(draco::PointCloudBuilder &builder) {
  constexpr bool duplicate_points = false;
  return builder.Finalize(duplicate_points);
}

draco_point_cloud_t *
draco_point_cloud_builder_get(draco_point_cloud_builder_t *builder) {
  draco::PointCloudBuilder *b =
      reinterpret_cast<draco::PointCloudBuilder *>(builder);
  return reinterpret_cast<draco_point_cloud_t *>(
      finalize_builder(*b).release());
}

int draco_point_cloud_set_attribute(int num_points,
                                    draco_point_cloud_builder_t *builder,
                                    const void *src, uint32_t att, int8_t ncomp,
                                    uint32_t dt) {
  draco::PointCloudBuilder *b =
      reinterpret_cast<draco::PointCloudBuilder *>(builder);
  draco::DataType datatype = static_cast<draco::DataType>(dt);
  draco::GeometryAttribute::Type attrtype =
      static_cast<draco::GeometryAttribute::Type>(att);

  switch (static_cast<draco::DataType>(dt)) {
  case draco::DataType::DT_INT8:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const int8_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_UINT8:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const uint8_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_INT16:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const int16_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_UINT16:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const uint16_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_INT32:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const int32_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_UINT32:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const uint32_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_INT64:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const int64_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_UINT64:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const uint64_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_FLOAT32:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const float *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_FLOAT64:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const double *>(src), attrtype,
                             ncomp, datatype);

    break;
  case draco::DataType::DT_BOOL:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const bool *>(src), attrtype,
                             ncomp, datatype);
    break;
  default:
    break;
  }
}

draco_mesh_builder_t *draco_new_mesh_builder() {
  return reinterpret_cast<draco_mesh_builder_t *>(
      new draco::TriangleSoupMeshBuilder());
}

void draco_mesh_builder_free(draco_mesh_builder_t *builder) {
  delete reinterpret_cast<draco::TriangleSoupMeshBuilder *>(builder);
}

void draco_mesh_builder_start(draco_mesh_builder_t *builder, int size) {
  draco::TriangleSoupMeshBuilder *b =
      reinterpret_cast<draco::TriangleSoupMeshBuilder *>(builder);
  b->Start(size);
}

draco_mesh_t *draco_mesh_builder_get(draco_mesh_builder_t *builder) {
  draco::TriangleSoupMeshBuilder *b =
      reinterpret_cast<draco::TriangleSoupMeshBuilder *>(builder);
  return reinterpret_cast<draco_mesh_t *>(finalize_builder(*b).release());
}

int draco_mesh_set_attribute(int num_points, draco_mesh_builder_t *builder,
                             const void *src, uint32_t att, int8_t ncomp,
                             uint32_t dt) {
  draco::TriangleSoupMeshBuilder *b =
      reinterpret_cast<draco::TriangleSoupMeshBuilder *>(builder);
  draco::DataType datatype = static_cast<draco::DataType>(dt);
  draco::GeometryAttribute::Type attrtype =
      static_cast<draco::GeometryAttribute::Type>(att);

  switch (static_cast<draco::DataType>(dt)) {
  case draco::DataType::DT_INT8:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const int8_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_UINT8:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const uint8_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_INT16:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const int16_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_UINT16:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const uint16_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_INT32:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const int32_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_UINT32:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const uint32_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_INT64:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const int64_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_UINT64:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const uint64_t *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_FLOAT32:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const float *>(src), attrtype,
                             ncomp, datatype);
    break;
  case draco::DataType::DT_FLOAT64:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const double *>(src), attrtype,
                             ncomp, datatype);

    break;
  case draco::DataType::DT_BOOL:
    draco_set_mesh_attribute(num_points, *b,
                             reinterpret_cast<const bool *>(src), attrtype,
                             ncomp, datatype);
    break;
  default:
    break;
  }
}