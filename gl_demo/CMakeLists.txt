cmake_minimum_required(VERSION 3.10)

project(GLDemo)

find_package(PNG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(sources
    "src/GLFixture.cpp"
    "src/GLFixture.hpp"
    "src/GLUtils.cpp"
    "src/GLUtils.hpp"
    "src/main.cpp"
    "src/Mandelbrot.cpp"
    "src/Mandelbrot.hpp"
    "src/Tests.cpp"
)

add_executable(GLDemo ${sources})

target_include_directories(
    GLDemo
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/ApprovalTests.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/ImageApprovals"
)

target_link_libraries(
    GLDemo
    PRIVATE
        PNG::PNG
        SDL2::SDL2
        GLEW::GLEW
        OpenGL::GL
        "$<$<CXX_COMPILER_ID:MSVC>:-IGNORE:4099>"
)

target_compile_options(GLDemo PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/FC>")

add_test(NAME GLDemo COMMAND GLDemo)
