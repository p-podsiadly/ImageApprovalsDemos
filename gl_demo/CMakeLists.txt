cmake_minimum_required(VERSION 3.10)

project(GLDemo)

find_package(ImageApprovals REQUIRED)
find_package(doctest REQUIRED)
find_package(sdl2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

set(sources
    "src/Demo.cpp"
    "src/Demo.hpp"
    "src/GLFixture.cpp"
    "src/GLFixture.hpp"
    "src/main.cpp"
    "src/Tests.cpp"
)

add_executable(GLDemo ${sources})

target_link_libraries(
    GLDemo
    PRIVATE
        ImageApprovals::ImageApprovals
        doctest::doctest
        sdl2::sdl2
        GLEW::GLEW
        OpenGL::GL
        "$<$<CXX_COMPILER_ID:MSVC>:-IGNORE:4099>"
)

target_compile_options(GLDemo PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/FC>")

doctest_discover_tests(GLDemo TEST_PREFIX "GLDemo/")
