cmake_minimum_required(VERSION 3.10)

project(ImageApprovalsDemos)

include("conan.cmake")

conan_cmake_run(
    REQUIRES "approvaltests.cpp/8.2.0"
             "doctest/2.3.6"
             "sdl2/2.0.10@bincrafters/stable"
             "glew/2.1.0@bincrafters/stable"
             "openexr/2.4.0"
             "libpng/1.6.37"
    BASIC_SETUP
    GENERATORS "cmake_find_package"
    BUILD missing
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")

set(ImageApprovals_ENABLE_TESTS OFF CACHE BOOL "")
set(ImageApprovals_RUN_CONAN OFF CACHE BOOL "")

add_subdirectory(ImageApprovals)

enable_testing()

add_subdirectory(gl_demo)
