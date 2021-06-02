#include "draco_api.h"

#include "draco/mesh/triangle_soup_mesh_builder.h"

#include <array>
#include <vector>
#include <iostream>

std::vector<std::array<float, 3>> pos{
    {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 1.f, 0.f},
    {1.f, 0.f, 0.f}, {1.f, 1.f, 0.f}, {0.f, 1.f, 1.f}, {1.f, 0.f, 1.f},
    {0.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {1.f, 0.f, 1.f}, {0.f, 1.f, 1.f},
    {0.f, 1.f, 0.f}, {1.f, 1.f, 0.f}, {0.f, 1.f, 1.f}, {0.f, 1.f, 1.f},
    {1.f, 1.f, 0.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 1.f}, {1.f, 0.f, 0.f},
    {0.f, 0.f, 0.f}, {1.f, 0.f, 1.f}, {1.f, 0.f, 0.f}, {0.f, 0.f, 1.f},
    {1.f, 0.f, 0.f}, {1.f, 0.f, 1.f}, {1.f, 1.f, 0.f}, {1.f, 1.f, 0.f},
    {1.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f},
    {0.f, 0.f, 0.f}, {0.f, 1.f, 1.f}, {0.f, 0.f, 1.f}, {0.f, 1.f, 0.f}};

std::vector<std::array<uint16_t, 3>> face{
    {0, 1, 2},    {3, 4, 5},    {6, 7, 8},    {9, 10, 11},
    {12, 13, 14}, {15, 16, 17}, {18, 19, 20}, {21, 22, 23},
    {24, 25, 26}, {27, 28, 29}, {30, 31, 32}, {33, 34, 35},
};

std::vector<std::array<float, 2>> texcoords{
    {0, 0.5},   {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5},
    {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5},
    {0, 0.5},   {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5},
    {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5},
    {0, 0.5},   {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5},
    {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5},
};

draco_mesh_t *test_mesh() {
    using namespace draco;
    TriangleSoupMeshBuilder mb;
      mb.Start(12);
      const int pos_att_id =
          mb.AddAttribute(GeometryAttribute::POSITION, 3, DT_FLOAT32);
      // clang-format off
      // Front face.
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(0),
                                   Vector3f(0.f, 0.f, 0.f).data(),
                                   Vector3f(1.f, 0.f, 0.f).data(),
                                   Vector3f(0.f, 1.f, 0.f).data());
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(1),
                                   Vector3f(0.f, 1.f, 0.f).data(),
                                   Vector3f(1.f, 0.f, 0.f).data(),
                                   Vector3f(1.f, 1.f, 0.f).data());

      // Back face.
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(2),
                                   Vector3f(0.f, 1.f, 1.f).data(),
                                   Vector3f(1.f, 0.f, 1.f).data(),
                                   Vector3f(0.f, 0.f, 1.f).data());
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(3),
                                   Vector3f(1.f, 1.f, 1.f).data(),
                                   Vector3f(1.f, 0.f, 1.f).data(),
                                   Vector3f(0.f, 1.f, 1.f).data());

      // Top face.
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(4),
                                   Vector3f(0.f, 1.f, 0.f).data(),
                                   Vector3f(1.f, 1.f, 0.f).data(),
                                   Vector3f(0.f, 1.f, 1.f).data());
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(5),
                                   Vector3f(0.f, 1.f, 1.f).data(),
                                   Vector3f(1.f, 1.f, 0.f).data(),
                                   Vector3f(1.f, 1.f, 1.f).data());

      // Bottom face.
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(6),
                                   Vector3f(0.f, 0.f, 1.f).data(),
                                   Vector3f(1.f, 0.f, 0.f).data(),
                                   Vector3f(0.f, 0.f, 0.f).data());
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(7),
                                   Vector3f(1.f, 0.f, 1.f).data(),
                                   Vector3f(1.f, 0.f, 0.f).data(),
                                   Vector3f(0.f, 0.f, 1.f).data());

      // Right face.
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(8),
                                   Vector3f(1.f, 0.f, 0.f).data(),
                                   Vector3f(1.f, 0.f, 1.f).data(),
                                   Vector3f(1.f, 1.f, 0.f).data());
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(9),
                                   Vector3f(1.f, 1.f, 0.f).data(),
                                   Vector3f(1.f, 0.f, 1.f).data(),
                                   Vector3f(1.f, 1.f, 1.f).data());

      // Left face.
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(10),
                                   Vector3f(0.f, 1.f, 0.f).data(),
                                   Vector3f(0.f, 0.f, 1.f).data(),
                                   Vector3f(0.f, 0.f, 0.f).data());
      mb.SetAttributeValuesForFace(pos_att_id, FaceIndex(11),
                                   Vector3f(0.f, 1.f, 1.f).data(),
                                   Vector3f(0.f, 0.f, 1.f).data(),
                                   Vector3f(0.f, 1.f, 0.f).data());
      // clang-format on

      std::unique_ptr<Mesh> mesh = mb.Finalize();
    
    return reinterpret_cast<draco_mesh_t *>(mesh.release());
}

int main(int argc, char **argv) {
  draco_mesh_builder_t *builder = draco_new_mesh_builder();

  draco_mesh_builder_start(builder, face.size());
  draco_mesh_set_attribute(face.size(), builder, pos.data(), 0, 3, 9);
  draco_mesh_set_attribute(face.size(), builder, texcoords.data(), 3, 2, 9);
  draco_mesh_t *mesh = draco_mesh_builder_get(builder);
    
    //draco_mesh_t *mesh = test_mesh();

  draco_encoder_t *enc = draco_new_encoder();

  size_t size;
  char *data;

  draco_status_t *state = draco_encoder_encode_mesh(enc, mesh, &data, &size);

  assert(draco_status_ok(state));
  draco_status_free(state);

  draco_encoder_free(enc);
  draco_mesh_free(mesh);
  draco_mesh_builder_free(builder);

  draco_decoder_t *denc = draco_new_decoder();

  draco_mesh_t *outmesh = draco_new_mesh();

  state = draco_decoder_decode_mesh(denc, data, size, outmesh);
  assert(draco_status_ok(state));
  draco_status_free(state);

  int facesize = draco_mesh_num_faces(outmesh);
  assert(facesize == face.size());

  std::vector<std::array<uint32_t, 3>> outface;
  outface.resize(facesize);

  draco_mesh_get_indices(outmesh, facesize * 3 * 4,
                         reinterpret_cast<uint32_t *>(outface.data()));

  int32_t posid = draco_point_cloud_get_named_attribute_id(
      reinterpret_cast<draco_point_cloud_t *>(outmesh), DRACO_GAT_POSITION);

  const draco_point_attr_t *posattr = draco_point_cloud_get_attribute(
      reinterpret_cast<draco_point_cloud_t *>(outmesh), posid);

  size_t vertssize = draco_point_cloud_num_points(
      reinterpret_cast<draco_point_cloud_t *>(outmesh));

  std::vector<std::array<float, 3>> outverts;
  outverts.resize(vertssize);

  assert(draco_point_cloud_get_attribute_data(
      reinterpret_cast<draco_point_cloud_t *>(outmesh), posattr,
      DRACO_DT_FLOAT32, vertssize * 3 * 4, outverts.data()));
    
  for (int f = 0; f < facesize; f++) {
      std::cout << "{";
    for (int i = 0; i < 3; i++) {
        std::cout << "[";
      std::array<float, 3> p2 = outverts[outface[f][i]];
       std::cout << p2[0] << ", "<< p2[1] << ", "<< p2[2];
        std::cout << "]," << std::endl;
    }
      std::cout << "}" << std::endl;
  }

  draco_mesh_free(outmesh);
  draco_decoder_free(denc);

  free(data);
}
