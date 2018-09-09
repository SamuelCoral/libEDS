cmake_minimum_required(VERSION 2.8)

project(libEDS)

include_directories (
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/EDS"
)

add_subdirectory (EDS)

set (EDS_VERSION_MAJOR 1)
set (EDS_VERSION_MINOR 0)

configure_file (
    "${PROJECT_SOURCE_DIR}/EDS_version.h.in"
    "${PROJECT_BINARY_DIR}/EDS_version.h"
)

add_executable (test_eds test.cpp)
add_executable (vector_field vector_field.cpp)
add_executable (idx_img idx_img.c)
target_link_libraries (test_eds EDS)
target_link_libraries (vector_field EDS)
target_link_libraries (idx_img EDS)
target_link_libraries(idx_img m)
