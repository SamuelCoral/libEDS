cmake_minimum_required(VERSION 2.8)

project(libEDS)

include_directories(
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/examples"
)

add_subdirectory(src)
add_subdirectory(examples)

set (EDS_VERSION_MAJOR 1)
set (EDS_VERSION_MINOR 0)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/EDS_version.h.in"
    "${PROJECT_BINARY_DIR}/EDS_version.h"
)

