#ifndef DRACO_C_API_H_
#define DRACO_C_API_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define FLYWAVE_I3S_API __declspec(dllexport)
#else
#define FLYWAVE_I3S_API
#endif

typedef enum {
  DRACO_EGT_INVALID = -1,
  DRACO_EGT_POINT_CLOUD,
  DRACO_EGT_TRIANGULAR_MESH
} draco_encoded_geometry_type;

typedef enum {
  DRACO_GAT_INVALID = -1,
  DRACO_GAT_POSITION,
  DRACO_GAT_NORMAL,
  DRACO_GAT_COLOR,
  DRACO_GAT_TEX_COORD,
  DRACO_GAT_GENERIC
} draco_geometry_attr_type;

typedef enum {
  DRACO_DT_INVALID,
  DRACO_DT_INT8,
  DRACO_DT_UINT8,
  DRACO_DT_INT16,
  DRACO_DT_UINT16,
  DRACO_DT_INT32,
  DRACO_DT_UINT32,
  DRACO_DT_INT64,
  DRACO_DT_UINT64,
  DRACO_DT_FLOAT32,
  DRACO_DT_FLOAT64,
  DRACO_DT_BOOL
} draco_data_type;

typedef const char *draco_string;

typedef struct _draco_status_t draco_status_t;

FLYWAVE_I3S_API void draco_status_free(draco_status_t *status);

FLYWAVE_I3S_API int draco_status_code(const draco_status_t *status);

FLYWAVE_I3S_API bool draco_status_ok(const draco_status_t *status);

FLYWAVE_I3S_API size_t
draco_status_error_msg_length(const draco_status_t *status);

FLYWAVE_I3S_API size_t draco_status_error_msg(const draco_status_t *status,
                                              char *msg, size_t length);

typedef struct _draco_point_attr_t draco_point_attr_t;

FLYWAVE_I3S_API size_t draco_point_attr_size(const draco_point_attr_t *pa);

FLYWAVE_I3S_API draco_geometry_attr_type
draco_point_attr_type(const draco_point_attr_t *pa);

FLYWAVE_I3S_API draco_data_type
draco_point_data_type(const draco_point_attr_t *pa);

FLYWAVE_I3S_API int8_t
draco_point_attr_num_components(const draco_point_attr_t *pa);

FLYWAVE_I3S_API bool draco_point_attr_normalized(const draco_point_attr_t *pa);

FLYWAVE_I3S_API int64_t
draco_point_attr_byte_stride(const draco_point_attr_t *pa);

FLYWAVE_I3S_API int64_t
draco_point_attr_byte_offset(const draco_point_attr_t *pa);

FLYWAVE_I3S_API uint32_t
draco_point_attr_unique_id(const draco_point_attr_t *pa);

typedef struct _draco_point_cloud_t draco_point_cloud_t;

FLYWAVE_I3S_API draco_point_cloud_t *draco_new_point_cloud();

FLYWAVE_I3S_API void draco_point_cloud_free(draco_point_cloud_t *pc);

FLYWAVE_I3S_API uint32_t
draco_point_cloud_num_points(const draco_point_cloud_t *pc);

FLYWAVE_I3S_API int32_t
draco_point_cloud_num_attrs(const draco_point_cloud_t *pc);

FLYWAVE_I3S_API const draco_point_attr_t *
draco_point_cloud_get_attribute(const draco_point_cloud_t *pc, int32_t att_id);

FLYWAVE_I3S_API int32_t draco_point_cloud_get_named_attribute_id(
    const draco_point_cloud_t *pc, draco_geometry_attr_type geo_type);

FLYWAVE_I3S_API const draco_point_attr_t *
draco_point_cloud_get_attribute_by_unique_id(const draco_point_cloud_t *pc,
                                             uint32_t unique_id);

FLYWAVE_I3S_API bool draco_point_cloud_get_attribute_data(
    const draco_point_cloud_t *pc, const draco_point_attr_t *pa,
    draco_data_type data_type, const size_t out_size, void *out_values);

typedef struct _draco_point_cloud_t draco_mesh_t;

FLYWAVE_I3S_API draco_mesh_t *draco_new_mesh();

FLYWAVE_I3S_API void draco_mesh_free(draco_mesh_t *mesh);

FLYWAVE_I3S_API uint32_t draco_mesh_num_faces(const draco_mesh_t *mesh);

FLYWAVE_I3S_API bool draco_mesh_get_indices(const draco_mesh_t *mesh,
                                            const size_t out_size,
                                            uint32_t *out_values);

FLYWAVE_I3S_API draco_encoded_geometry_type
draco_get_encoded_geometry_type(const char *data, size_t data_size);

typedef struct _draco_decoder_t draco_decoder_t;

FLYWAVE_I3S_API draco_decoder_t *draco_new_decoder();

FLYWAVE_I3S_API void draco_free(draco_decoder_t *decoder);

FLYWAVE_I3S_API draco_status_t *
draco_decoder_decode_mesh(draco_decoder_t *decoder, const char *data,
                          size_t data_size, draco_mesh_t *out_mesh);

FLYWAVE_I3S_API draco_status_t *
draco_decoder_decode_point_cloud(draco_decoder_t *decoder, const char *data,
                                 size_t data_size, draco_point_cloud_t *out_pc);

#ifdef __cplusplus
}
#endif

#endif // DRACO_C_API_H_