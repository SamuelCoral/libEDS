cmake_minimum_required(VERSION 3.5)

project(libEDS)



# Instrucciones de la biblioteca
add_library (EDS
    src/EDS/EDS_tipos.c
    src/EDS/EDS_bmp.c
    src/EDS/EDS_color.c
    src/EDS/EDS_dibujo.c
)

add_compile_definitions(EDS_EXPORTS)

set (EDS_VERSION_MAJOR 1)
set (EDS_VERSION_MINOR 0)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/EDS/EDS_version.h.in"
    "${PROJECT_BINARY_DIR}/EDS_version.h"
)

include_directories(
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_BINARY_DIR}"
)



# Ejemplos de implementación de la biblioteca

add_subdirectory(examples/test)
add_subdirectory(examples/vector_field)
add_subdirectory(examples/idx_img)
