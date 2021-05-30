cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Draco requires C++11.
set(CMAKE_CXX_STANDARD 11)
project(draco C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(draco_root "${CMAKE_CURRENT_SOURCE_DIR}")
set(draco_src_root "${draco_root}/src/draco")
set(draco_build "${CMAKE_CURRENT_BINARY_DIR}")

if("${draco_root}" STREQUAL "${draco_build}")
  message(
    FATAL_ERROR "Building from within the Draco source tree is not supported.\n"
                "Hint: Run these commands\n"
                "$ rm -rf CMakeCache.txt CMakeFiles\n"
                "$ mkdir -p ../draco_build\n" "$ cd ../draco_build\n"
                "And re-run CMake from the draco_build directory.")
endif()

include(CMakePackageConfigHelpers)
include("${draco_root}/cmake/draco_build_definitions.cmake")
include("${draco_root}/cmake/draco_cpu_detection.cmake")
include("${draco_root}/cmake/draco_emscripten.cmake")
include("${draco_root}/cmake/draco_flags.cmake")
include("${draco_root}/cmake/draco_helpers.cmake")
include("${draco_root}/cmake/draco_install.cmake")
include("${draco_root}/cmake/draco_intrinsics.cmake")
include("${draco_root}/cmake/draco_options.cmake")
include("${draco_root}/cmake/draco_sanitizer.cmake")
include("${draco_root}/cmake/draco_targets.cmake")
include("${draco_root}/cmake/draco_tests.cmake")
include("${draco_root}/cmake/draco_variables.cmake")

# C++ and linker flags.
draco_track_configuration_variable(DRACO_CXX_FLAGS)
draco_track_configuration_variable(DRACO_EXE_LINKER_FLAGS)

# Sanitizer integration.
draco_track_configuration_variable(DRACO_SANITIZE)

# Generated source file directory.
draco_track_configuration_variable(DRACO_GENERATED_SOURCES_DIRECTORY)

# Controls use of std::mutex and absl::Mutex in ThreadPool.
draco_track_configuration_variable(DRACO_THREADPOOL_USE_STD_MUTEX)

# Compiler/linker flags must be lists, but come in from the environment as
# strings. Break them up:
if(NOT "${DRACO_CXX_FLAGS}" STREQUAL "")
  separate_arguments(DRACO_CXX_FLAGS)
endif()
if(NOT "${DRACO_EXE_LINKER_FLAGS}" STREQUAL "")
  separate_arguments(DRACO_EXE_LINKER_FLAGS)
endif()

draco_reset_target_lists()
draco_setup_options()
draco_set_build_definitions()
draco_set_cxx_flags()
draco_generate_features_h()

# Draco source file listing variables.
list(APPEND draco_attributes_sources
            "${draco_src_root}/attributes/attribute_octahedron_transform.cc"
            "${draco_src_root}/attributes/attribute_octahedron_transform.h"
            "${draco_src_root}/attributes/attribute_quantization_transform.cc"
            "${draco_src_root}/attributes/attribute_quantization_transform.h"
            "${draco_src_root}/attributes/attribute_transform.cc"
            "${draco_src_root}/attributes/attribute_transform.h"
            "${draco_src_root}/attributes/attribute_transform_data.h"
            "${draco_src_root}/attributes/attribute_transform_type.h"
            "${draco_src_root}/attributes/geometry_attribute.cc"
            "${draco_src_root}/attributes/geometry_attribute.h"
            "${draco_src_root}/attributes/geometry_indices.h"
            "${draco_src_root}/attributes/point_attribute.cc"
            "${draco_src_root}/attributes/point_attribute.h")

list(
  APPEND
    draco_compression_attributes_dec_sources
    "${draco_src_root}/compression/attributes/attributes_decoder.cc"
    "${draco_src_root}/compression/attributes/attributes_decoder.h"
    "${draco_src_root}/compression/attributes/kd_tree_attributes_decoder.cc"
    "${draco_src_root}/compression/attributes/kd_tree_attributes_decoder.h"
    "${draco_src_root}/compression/attributes/kd_tree_attributes_shared.h"
    "${draco_src_root}/compression/attributes/mesh_attribute_indices_encoding_data.h"
    "${draco_src_root}/compression/attributes/normal_compression_utils.h"
    "${draco_src_root}/compression/attributes/point_d_vector.h"
    "${draco_src_root}/compression/attributes/sequential_attribute_decoder.cc"
    "${draco_src_root}/compression/attributes/sequential_attribute_decoder.h"
    "${draco_src_root}/compression/attributes/sequential_attribute_decoders_controller.cc"
    "${draco_src_root}/compression/attributes/sequential_attribute_decoders_controller.h"
    "${draco_src_root}/compression/attributes/sequential_integer_attribute_decoder.cc"
    "${draco_src_root}/compression/attributes/sequential_integer_attribute_decoder.h"
    "${draco_src_root}/compression/attributes/sequential_normal_attribute_decoder.cc"
    "${draco_src_root}/compression/attributes/sequential_normal_attribute_decoder.h"
    "${draco_src_root}/compression/attributes/sequential_quantization_attribute_decoder.cc"
    "${draco_src_root}/compression/attributes/sequential_quantization_attribute_decoder.h"
  )

list(
  APPEND
    draco_compression_attributes_enc_sources
    "${draco_src_root}/compression/attributes/attributes_encoder.cc"
    "${draco_src_root}/compression/attributes/attributes_encoder.h"
    "${draco_src_root}/compression/attributes/kd_tree_attributes_encoder.cc"
    "${draco_src_root}/compression/attributes/kd_tree_attributes_encoder.h"
    "${draco_src_root}/compression/attributes/linear_sequencer.h"
    "${draco_src_root}/compression/attributes/points_sequencer.h"
    "${draco_src_root}/compression/attributes/sequential_attribute_encoder.cc"
    "${draco_src_root}/compression/attributes/sequential_attribute_encoder.h"
    "${draco_src_root}/compression/attributes/sequential_attribute_encoders_controller.cc"
    "${draco_src_root}/compression/attributes/sequential_attribute_encoders_controller.h"
    "${draco_src_root}/compression/attributes/sequential_integer_attribute_encoder.cc"
    "${draco_src_root}/compression/attributes/sequential_integer_attribute_encoder.h"
    "${draco_src_root}/compression/attributes/sequential_normal_attribute_encoder.cc"
    "${draco_src_root}/compression/attributes/sequential_normal_attribute_encoder.h"
    "${draco_src_root}/compression/attributes/sequential_quantization_attribute_encoder.cc"
    "${draco_src_root}/compression/attributes/sequential_quantization_attribute_encoder.h"
  )


list(
  APPEND
    draco_compression_attributes_pred_schemes_dec_sources
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_constrained_multi_parallelogram_decoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_constrained_multi_parallelogram_shared.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_data.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_decoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_decoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_predictor_area.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_predictor_base.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_multi_parallelogram_decoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_parallelogram_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_parallelogram_shared.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_decoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_portable_decoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_portable_predictor.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_decoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_decoder_factory.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_decoder_interface.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_decoding_transform.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_delta_decoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_factory.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_interface.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_canonicalized_decoding_transform.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_canonicalized_transform_base.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_decoding_transform.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_transform_base.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_wrap_decoding_transform.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_wrap_transform_base.h"
  )

list(
  APPEND
    draco_compression_attributes_pred_schemes_enc_sources
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_constrained_multi_parallelogram_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_constrained_multi_parallelogram_shared.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_data.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_predictor_area.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_geometric_normal_predictor_base.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_multi_parallelogram_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_parallelogram_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_parallelogram_shared.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_portable_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/mesh_prediction_scheme_tex_coords_portable_predictor.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_delta_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_encoder.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_encoder_factory.cc"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_encoder_factory.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_encoder_interface.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_encoding_transform.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_factory.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_interface.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_canonicalized_encoding_transform.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_canonicalized_transform_base.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_encoding_transform.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_normal_octahedron_transform_base.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_wrap_encoding_transform.h"
    "${draco_src_root}/compression/attributes/prediction_schemes/prediction_scheme_wrap_transform_base.h"
  )

list(
  APPEND
    draco_compression_bit_coders_sources
    "${draco_src_root}/compression/bit_coders/adaptive_rans_bit_coding_shared.h"
    "${draco_src_root}/compression/bit_coders/adaptive_rans_bit_decoder.cc"
    "${draco_src_root}/compression/bit_coders/adaptive_rans_bit_decoder.h"
    "${draco_src_root}/compression/bit_coders/adaptive_rans_bit_encoder.cc"
    "${draco_src_root}/compression/bit_coders/adaptive_rans_bit_encoder.h"
    "${draco_src_root}/compression/bit_coders/direct_bit_decoder.cc"
    "${draco_src_root}/compression/bit_coders/direct_bit_decoder.h"
    "${draco_src_root}/compression/bit_coders/direct_bit_encoder.cc"
    "${draco_src_root}/compression/bit_coders/direct_bit_encoder.h"
    "${draco_src_root}/compression/bit_coders/folded_integer_bit_decoder.h"
    "${draco_src_root}/compression/bit_coders/folded_integer_bit_encoder.h"
    "${draco_src_root}/compression/bit_coders/rans_bit_decoder.cc"
    "${draco_src_root}/compression/bit_coders/rans_bit_decoder.h"
    "${draco_src_root}/compression/bit_coders/rans_bit_encoder.cc"
    "${draco_src_root}/compression/bit_coders/rans_bit_encoder.h"
    "${draco_src_root}/compression/bit_coders/symbol_bit_decoder.cc"
    "${draco_src_root}/compression/bit_coders/symbol_bit_decoder.h"
    "${draco_src_root}/compression/bit_coders/symbol_bit_encoder.cc"
    "${draco_src_root}/compression/bit_coders/symbol_bit_encoder.h")

list(APPEND draco_enc_config_sources
            "${draco_src_root}/compression/config/compression_shared.h"
            "${draco_src_root}/compression/config/draco_options.h"
            "${draco_src_root}/compression/config/encoder_options.h"
            "${draco_src_root}/compression/config/encoding_features.h")

list(APPEND draco_dec_config_sources
            "${draco_src_root}/compression/config/compression_shared.h"
            "${draco_src_root}/compression/config/decoder_options.h"
            "${draco_src_root}/compression/config/draco_options.h")

list(APPEND draco_compression_decode_sources
            "${draco_src_root}/compression/decode.cc"
            "${draco_src_root}/compression/decode.h")

list(APPEND draco_compression_encode_sources
            "${draco_src_root}/compression/encode.cc"
            "${draco_src_root}/compression/encode.h"
            "${draco_src_root}/compression/encode_base.h"
            "${draco_src_root}/compression/expert_encode.cc"
            "${draco_src_root}/compression/expert_encode.h")

list(
  APPEND
    draco_compression_mesh_traverser_sources
    "${draco_src_root}/compression/mesh/traverser/depth_first_traverser.h"
    "${draco_src_root}/compression/mesh/traverser/max_prediction_degree_traverser.h"
    "${draco_src_root}/compression/mesh/traverser/mesh_attribute_indices_encoding_observer.h"
    "${draco_src_root}/compression/mesh/traverser/mesh_traversal_sequencer.h"
    "${draco_src_root}/compression/mesh/traverser/traverser_base.h")

list(
  APPEND
    draco_compression_mesh_dec_sources
    "${draco_src_root}/compression/mesh/mesh_decoder.cc"
    "${draco_src_root}/compression/mesh/mesh_decoder.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_decoder.cc"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_decoder.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_decoder_impl.cc"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_decoder_impl.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_decoder_impl_interface.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_shared.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_traversal_decoder.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_traversal_predictive_decoder.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_traversal_valence_decoder.h"
    "${draco_src_root}/compression/mesh/mesh_sequential_decoder.cc"
    "${draco_src_root}/compression/mesh/mesh_sequential_decoder.h")

list(
  APPEND
    draco_compression_mesh_enc_sources
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_encoder.cc"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_encoder.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_encoder_impl.cc"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_encoder_impl.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_encoder_impl_interface.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_shared.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_traversal_encoder.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_traversal_predictive_encoder.h"
    "${draco_src_root}/compression/mesh/mesh_edgebreaker_traversal_valence_encoder.h"
    "${draco_src_root}/compression/mesh/mesh_encoder.cc"
    "${draco_src_root}/compression/mesh/mesh_encoder.h"
    "${draco_src_root}/compression/mesh/mesh_sequential_encoder.cc"
    "${draco_src_root}/compression/mesh/mesh_sequential_encoder.h")

list(
  APPEND
    draco_compression_point_cloud_dec_sources
    "${draco_src_root}/compression/point_cloud/point_cloud_decoder.cc"
    "${draco_src_root}/compression/point_cloud/point_cloud_decoder.h"
    "${draco_src_root}/compression/point_cloud/point_cloud_kd_tree_decoder.cc"
    "${draco_src_root}/compression/point_cloud/point_cloud_kd_tree_decoder.h"
    "${draco_src_root}/compression/point_cloud/point_cloud_sequential_decoder.cc"
    "${draco_src_root}/compression/point_cloud/point_cloud_sequential_decoder.h"
  )

list(
  APPEND
    draco_compression_point_cloud_enc_sources
    "${draco_src_root}/compression/point_cloud/point_cloud_encoder.cc"
    "${draco_src_root}/compression/point_cloud/point_cloud_encoder.h"
    "${draco_src_root}/compression/point_cloud/point_cloud_kd_tree_encoder.cc"
    "${draco_src_root}/compression/point_cloud/point_cloud_kd_tree_encoder.h"
    "${draco_src_root}/compression/point_cloud/point_cloud_sequential_encoder.cc"
    "${draco_src_root}/compression/point_cloud/point_cloud_sequential_encoder.h"
  )

list(APPEND draco_compression_entropy_sources
            "${draco_src_root}/compression/entropy/ans.h"
            "${draco_src_root}/compression/entropy/rans_symbol_coding.h"
            "${draco_src_root}/compression/entropy/rans_symbol_decoder.h"
            "${draco_src_root}/compression/entropy/rans_symbol_encoder.h"
            "${draco_src_root}/compression/entropy/shannon_entropy.cc"
            "${draco_src_root}/compression/entropy/shannon_entropy.h"
            "${draco_src_root}/compression/entropy/symbol_decoding.cc"
            "${draco_src_root}/compression/entropy/symbol_decoding.h"
            "${draco_src_root}/compression/entropy/symbol_encoding.cc"
            "${draco_src_root}/compression/entropy/symbol_encoding.h")

list(APPEND draco_core_sources
            "${draco_src_root}/core/bit_utils.cc"
            "${draco_src_root}/core/bit_utils.h"
            "${draco_src_root}/core/bounding_box.cc"
            "${draco_src_root}/core/bounding_box.h"
            "${draco_src_root}/core/cycle_timer.cc"
            "${draco_src_root}/core/cycle_timer.h"
            "${draco_src_root}/core/data_buffer.cc"
            "${draco_src_root}/core/data_buffer.h"
            "${draco_src_root}/core/decoder_buffer.cc"
            "${draco_src_root}/core/decoder_buffer.h"
            "${draco_src_root}/core/divide.cc"
            "${draco_src_root}/core/divide.h"
            "${draco_src_root}/core/draco_index_type.h"
            "${draco_src_root}/core/draco_index_type_vector.h"
            "${draco_src_root}/core/draco_types.cc"
            "${draco_src_root}/core/draco_types.h"
            "${draco_src_root}/core/encoder_buffer.cc"
            "${draco_src_root}/core/encoder_buffer.h"
            "${draco_src_root}/core/hash_utils.cc"
            "${draco_src_root}/core/hash_utils.h"
            "${draco_src_root}/core/macros.h"
            "${draco_src_root}/core/math_utils.h"
            "${draco_src_root}/core/options.cc"
            "${draco_src_root}/core/options.h"
            "${draco_src_root}/core/quantization_utils.cc"
            "${draco_src_root}/core/quantization_utils.h"
            "${draco_src_root}/core/status.h"
            "${draco_src_root}/core/status_or.h"
            "${draco_src_root}/core/varint_decoding.h"
            "${draco_src_root}/core/varint_encoding.h"
            "${draco_src_root}/core/vector_d.h")

list(APPEND draco_io_sources
            "${draco_src_root}/io/file_reader_factory.cc"
            "${draco_src_root}/io/file_reader_factory.h"
            "${draco_src_root}/io/file_reader_interface.h"
            "${draco_src_root}/io/file_utils.cc"
            "${draco_src_root}/io/file_utils.h"
            "${draco_src_root}/io/file_writer_factory.cc"
            "${draco_src_root}/io/file_writer_factory.h"
            "${draco_src_root}/io/file_writer_interface.h"
            "${draco_src_root}/io/file_writer_utils.h"
            "${draco_src_root}/io/file_writer_utils.cc"
            "${draco_src_root}/io/mesh_io.cc"
            "${draco_src_root}/io/mesh_io.h"
            "${draco_src_root}/io/obj_decoder.cc"
            "${draco_src_root}/io/obj_decoder.h"
            "${draco_src_root}/io/obj_encoder.cc"
            "${draco_src_root}/io/obj_encoder.h"
            "${draco_src_root}/io/parser_utils.cc"
            "${draco_src_root}/io/parser_utils.h"
            "${draco_src_root}/io/ply_decoder.cc"
            "${draco_src_root}/io/ply_decoder.h"
            "${draco_src_root}/io/ply_encoder.cc"
            "${draco_src_root}/io/ply_encoder.h"
            "${draco_src_root}/io/ply_property_reader.h"
            "${draco_src_root}/io/ply_property_writer.h"
            "${draco_src_root}/io/ply_reader.cc"
            "${draco_src_root}/io/ply_reader.h"
            "${draco_src_root}/io/point_cloud_io.cc"
            "${draco_src_root}/io/point_cloud_io.h"
            "${draco_src_root}/io/stdio_file_reader.cc"
            "${draco_src_root}/io/stdio_file_reader.h"
            "${draco_src_root}/io/stdio_file_writer.cc"
            "${draco_src_root}/io/stdio_file_writer.h")

list(APPEND draco_mesh_sources
            "${draco_src_root}/mesh/corner_table.cc"
            "${draco_src_root}/mesh/corner_table.h"
            "${draco_src_root}/mesh/corner_table_iterators.h"
            "${draco_src_root}/mesh/mesh.cc"
            "${draco_src_root}/mesh/mesh.h"
            "${draco_src_root}/mesh/mesh_are_equivalent.cc"
            "${draco_src_root}/mesh/mesh_are_equivalent.h"
            "${draco_src_root}/mesh/mesh_attribute_corner_table.cc"
            "${draco_src_root}/mesh/mesh_attribute_corner_table.h"
            "${draco_src_root}/mesh/mesh_cleanup.cc"
            "${draco_src_root}/mesh/mesh_cleanup.h"
            "${draco_src_root}/mesh/mesh_misc_functions.cc"
            "${draco_src_root}/mesh/mesh_misc_functions.h"
            "${draco_src_root}/mesh/mesh_stripifier.cc"
            "${draco_src_root}/mesh/mesh_stripifier.h"
            "${draco_src_root}/mesh/triangle_soup_mesh_builder.cc"
            "${draco_src_root}/mesh/triangle_soup_mesh_builder.h"
            "${draco_src_root}/mesh/valence_cache.h")

list(APPEND draco_point_cloud_sources
            "${draco_src_root}/point_cloud/point_cloud.cc"
            "${draco_src_root}/point_cloud/point_cloud.h"
            "${draco_src_root}/point_cloud/point_cloud_builder.cc"
            "${draco_src_root}/point_cloud/point_cloud_builder.h")

list(
  APPEND
    draco_points_common_sources
    "${draco_src_root}/compression/point_cloud/algorithms/point_cloud_compression_method.h"
    "${draco_src_root}/compression/point_cloud/algorithms/point_cloud_types.h"
    "${draco_src_root}/compression/point_cloud/algorithms/quantize_points_3.h"
    "${draco_src_root}/compression/point_cloud/algorithms/queuing_policy.h")

list(
  APPEND
    draco_points_dec_sources
    "${draco_src_root}/compression/point_cloud/algorithms/dynamic_integer_points_kd_tree_decoder.cc"
    "${draco_src_root}/compression/point_cloud/algorithms/dynamic_integer_points_kd_tree_decoder.h"
    "${draco_src_root}/compression/point_cloud/algorithms/float_points_tree_decoder.cc"
    "${draco_src_root}/compression/point_cloud/algorithms/float_points_tree_decoder.h"
  )

list(
  APPEND
    draco_points_enc_sources
    "${draco_src_root}/compression/point_cloud/algorithms/dynamic_integer_points_kd_tree_encoder.cc"
    "${draco_src_root}/compression/point_cloud/algorithms/dynamic_integer_points_kd_tree_encoder.h"
    "${draco_src_root}/compression/point_cloud/algorithms/float_points_tree_encoder.cc"
    "${draco_src_root}/compression/point_cloud/algorithms/float_points_tree_encoder.h"
  )

list(APPEND draco_metadata_sources
            "${draco_src_root}/metadata/geometry_metadata.cc"
            "${draco_src_root}/metadata/geometry_metadata.h"
            "${draco_src_root}/metadata/metadata.cc"
            "${draco_src_root}/metadata/metadata.h")

list(APPEND draco_metadata_enc_sources
            "${draco_src_root}/metadata/metadata_encoder.cc"
            "${draco_src_root}/metadata/metadata_encoder.h")

list(APPEND draco_metadata_dec_sources
            "${draco_src_root}/metadata/metadata_decoder.cc"
            "${draco_src_root}/metadata/metadata_decoder.h")

list(APPEND draco_animation_sources
            "${draco_src_root}/animation/keyframe_animation.cc"
            "${draco_src_root}/animation/keyframe_animation.h")

list(APPEND draco_animation_enc_sources
            "${draco_src_root}/animation/keyframe_animation_encoder.cc"
            "${draco_src_root}/animation/keyframe_animation_encoder.h")

list(APPEND draco_animation_dec_sources
            "${draco_src_root}/animation/keyframe_animation_decoder.cc"
            "${draco_src_root}/animation/keyframe_animation_decoder.h")

list(
  APPEND draco_js_dec_sources
         "${draco_src_root}/javascript/emscripten/decoder_webidl_wrapper.cc"
         "${draco_src_root}/javascript/emscripten/draco_decoder_glue_wrapper.cc"
  )

list(
  APPEND draco_js_enc_sources
         "${draco_src_root}/javascript/emscripten/draco_encoder_glue_wrapper.cc"
         "${draco_src_root}/javascript/emscripten/encoder_webidl_wrapper.cc")

list(
  APPEND
    draco_animation_js_dec_sources
    "${draco_src_root}/javascript/emscripten/animation_decoder_webidl_wrapper.cc"
    "${draco_src_root}/javascript/emscripten/draco_animation_decoder_glue_wrapper.cc"
  )

list(
  APPEND
    draco_animation_js_enc_sources
    "${draco_src_root}/javascript/emscripten/animation_encoder_webidl_wrapper.cc"
    "${draco_src_root}/javascript/emscripten/draco_animation_encoder_glue_wrapper.cc"
  )

list(APPEND draco_unity_plug_sources
            "${draco_src_root}/unity/draco_unity_plugin.cc"
            "${draco_src_root}/unity/draco_unity_plugin.h")

list(APPEND draco_maya_plug_sources
            "${draco_src_root}/maya/draco_maya_plugin.cc"
            "${draco_src_root}/maya/draco_maya_plugin.h")

  draco_add_library(NAME draco_attributes TYPE OBJECT SOURCES
                    ${draco_attributes_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME
                    draco_compression_attributes_dec
                    OBJECT
                    ${draco_compression_attributes_dec_sources}
                    TYPE
                    OBJECT
                    SOURCES
                    ${draco_compression_attributes_dec_sources}
                    DEFINES
                    ${draco_defines}
                    INCLUDES
                    ${draco_include_paths})
  draco_add_library(NAME draco_compression_attributes_enc TYPE OBJECT SOURCES
                    ${draco_compression_attributes_enc_sources} DEFINES
                    ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_attributes_pred_schemes_dec TYPE
                    OBJECT SOURCES
                    ${draco_compression_attributes_pred_schemes_dec_sources})
  draco_add_library(NAME draco_compression_attributes_pred_schemes_enc TYPE
                    OBJECT SOURCES
                    ${draco_compression_attributes_pred_schemes_enc_sources}
                    DEFINES ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_bit_coders TYPE OBJECT SOURCES
                    ${draco_compression_bit_coders_sources} DEFINES
                    ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_enc_config TYPE OBJECT SOURCES
                    ${draco_enc_config_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_dec_config TYPE OBJECT SOURCES
                    ${draco_dec_config_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_decode TYPE OBJECT SOURCES
                    ${draco_compression_decode_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_encode TYPE OBJECT SOURCES
                    ${draco_compression_encode_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_entropy TYPE OBJECT SOURCES
                    ${draco_compression_entropy_sources} DEFINES
                    ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_mesh_traverser TYPE OBJECT SOURCES
                    ${draco_compression_mesh_traverser_sources} DEFINES
                    ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_mesh_dec TYPE OBJECT SOURCES
                    ${draco_compression_mesh_dec_sources} DEFINES
                    ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_mesh_enc TYPE OBJECT SOURCES
                    ${draco_compression_mesh_enc_sources} DEFINES
                    ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_point_cloud_dec TYPE OBJECT SOURCES
                    ${draco_compression_point_cloud_dec_sources} DEFINES
                    ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_compression_point_cloud_enc TYPE OBJECT SOURCES
                    ${draco_compression_point_cloud_enc_sources} DEFINES
                    ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_core TYPE OBJECT SOURCES ${draco_core_sources}
                    DEFINES ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_io TYPE OBJECT SOURCES ${draco_io_sources}
                    DEFINES ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_mesh TYPE OBJECT SOURCES ${draco_mesh_sources}
                    DEFINES ${draco_defines} INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_metadata_dec TYPE OBJECT SOURCES
                    ${draco_metadata_dec_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_metadata_enc TYPE OBJECT SOURCES
                    ${draco_metadata_enc_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_metadata TYPE OBJECT SOURCES
                    ${draco_metadata_sources} DEFINES ${draco_defines} INCLUDES
                    ${draco_include_paths})
  draco_add_library(NAME draco_animation_dec TYPE OBJECT SOURCES
                    ${draco_animation_dec_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_animation_enc TYPE OBJECT SOURCES
                    ${draco_animation_enc_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME draco_animation TYPE OBJECT SOURCES
                    ${draco_animation_sources} DEFINES ${draco_defines} INCLUDES
                    ${draco_include_paths})
  draco_add_library(NAME draco_point_cloud TYPE OBJECT SOURCES
                    ${draco_point_cloud_sources} DEFINES ${draco_defines}
                    INCLUDES ${draco_include_paths})
  draco_add_library(NAME
                    draco_points_dec
                    TYPE
                    OBJECT
                    SOURCES
                    ${draco_points_common_sources}
                    ${draco_points_dec_sources}
                    DEFINES
                    ${draco_defines}
                    INCLUDES
                    ${draco_include_paths})
  draco_add_library(NAME
                    draco_points_enc
                    TYPE
                    OBJECT
                    SOURCES
                    ${draco_points_common_sources}
                    ${draco_points_enc_sources}
                    DEFINES
                    ${draco_defines}
                    INCLUDES
                    ${draco_include_paths})

  set(draco_object_library_deps
      draco_attributes
      draco_compression_attributes_dec
      draco_compression_attributes_enc
      draco_compression_attributes_pred_schemes_dec
      draco_compression_attributes_pred_schemes_enc
      draco_compression_bit_coders
      draco_compression_decode
      draco_compression_encode
      draco_compression_entropy
      draco_compression_mesh_dec
      draco_compression_mesh_enc
      draco_compression_point_cloud_dec
      draco_compression_point_cloud_enc
      draco_core
      draco_dec_config
      draco_enc_config
      draco_io
      draco_mesh
      draco_metadata
      draco_metadata_dec
      draco_metadata_enc
      draco_animation
      draco_animation_dec
      draco_animation_enc
      draco_point_cloud
      draco_points_dec
      draco_points_enc)

  draco_add_library(NAME
                      draco_static
                      OUTPUT_NAME
                      draco
                      TYPE
                      STATIC
                      DEFINES
                      ${draco_defines}
                      INCLUDES
                      ${draco_include_paths}
                      OBJLIB_DEPS
                      ${draco_object_library_deps})

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
SET_TARGET_PROPERTIES(draco_attributes PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_attributes_dec PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_attributes_enc PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_bit_coders PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_decode PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_encode PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_entropy PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_mesh_dec PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_mesh_enc PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_point_cloud_dec PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_point_cloud_enc PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_core PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_dec_config PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_enc_config PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_io PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_mesh PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_metadata PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_metadata_dec PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_metadata_enc PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_animation PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_animation_dec PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_animation_enc PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_point_cloud PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_points_dec PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_points_enc PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_static PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_attributes_pred_schemes_enc PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_attributes_pred_schemes_dec PROPERTIES FOLDER external/draco)
SET_TARGET_PROPERTIES(draco_compression_mesh_traverser PROPERTIES FOLDER external/draco)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
                    