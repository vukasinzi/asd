cmake_minimum_required(VERSION 3.16)
project(prp_projekat C)

set(CMAKE_C_STANDARD 17)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE HDR_FILES "${CMAKE_SOURCE_DIR}/header/*.h")

add_executable(main ${SRC_FILES} ${HDR_FILES}
        src/vektor.c
        src/vektor.h)
target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/header")
