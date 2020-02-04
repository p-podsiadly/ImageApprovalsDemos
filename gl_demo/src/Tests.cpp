#include "GLFixture.hpp"
#include "Mandelbrot.hpp"
#include <doctest/doctest.h>
#include <ApprovalTests.hpp>

using namespace ImageApprovals;
using namespace ApprovalTests;

TEST_CASE_FIXTURE(GLFixture, "Clearing color buffer with fixed color")
{
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto image = getRenderedImage();

    Approvals::verify(ImageWriter(image));
}

TEST_CASE_FIXTURE(GLFixture, "GLProgram and QuadRenderer")
{
    const char* vertexShaderSrc =
        "#version 330 core\n"
        "in vec2 in_pos;\n"
        "out vec3 color;\n"
        "void main() {\n"
        "  gl_Position = vec4(in_pos, 0.0, 1.0);\n"
        "  color = vec3((in_pos + vec2(1.0)) * 0.5, 0.0);\n"
        "}";

    const char* fragmentShaderSrc =
        "#version 330 core\n"
        "in vec3 color;\n"
        "out vec4 out_color;\n"
        "void main() {\n"
        "  out_color = vec4(color, 1.0);\n"
        "}";
    
    auto vertexShader = GLShader::compile(GL_VERTEX_SHADER, vertexShaderSrc);
    auto fragmentShader = GLShader::compile(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    auto program = GLProgram::link(vertexShader, fragmentShader);

    QuadRenderer renderer;

    renderer.draw(program);

    auto image = getRenderedImage();
    Approvals::verify(ImageWriter(image));
}

TEST_CASE_FIXTURE(GLFixture, "MandelbrotRenderer")
{
    MandelbrotRenderer mandelbrotRenderer;

    mandelbrotRenderer.drawFrame();

    auto image = getRenderedImage();
    Approvals::verify(ImageWriter(image));
}
