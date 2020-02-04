cmake_minimum_required(VERSION 3.10)

project(ImageApprovalsDemos)

include("conan.cmake")

conan_cmake_run(
    REQUIRES "imageapprovals/master@ppodsiadly/testing"
             "approvaltests.cpp/8.1.0"
             "doctest/2.3.6"
             "sdl2/2.0.10@bincrafters/stable"
             "glew/2.1.0@bincrafters/stable"
    BASIC_SETUP
    GENERATORS "cmake_find_package"
    BUILD missing
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")

enable_testing()

add_subdirectory(gl_demo)
