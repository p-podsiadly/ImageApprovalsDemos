#include "Mandelbrot.hpp"

MandelbrotRenderer::MandelbrotRenderer()
{
    const char* vertexShaderSrc = 
        "#version 330 core\n"
        "in vec2 in_pos;\n"
        "out vec2 pos;\n"
        "void main() {\n"
        "  gl_Position = vec4(in_pos, 0.0, 1.0);\n"
        "  pos = in_pos;\n"
        "}";

    const char* fragmentShaderSrc =
        "#version 330 core\n"
        "in vec2 pos;\n"
        "out vec4 out_color;\n"

        "vec2 complexSquare(vec2 c) {\n"
        "  return vec2(c.x * c.x - c.y * c.y, 2.0 * c.x * c.y);\n"
        "}\n"

        "float convergence(vec2 pos, int maxIterations) {\n"
        "  vec2 z = pos;\n"
        "  int i = 0;\n"
        "  for( ; i < maxIterations; ++i) {\n"
        "    z = complexSquare(z) + pos;\n"
        "    if(length(z) >= 2.0) {\n"
        "      break;\n"
        "    }\n"
        "  }\n"
        "  return float(i);\n"
        "}\n"

        "vec3 shadeToColor(float shade) {\n"
        "  return vec3(\n"
        "    exp(-1.0 * abs(shade - 0.25) * 2.2),\n"
        "    exp(-1.0 * abs(shade - 0.5) * 2.2),\n"
        "    exp(-1.0 * abs(shade - 0.75) * 2.2)\n"
        "  );\n"
        "}\n"

        "void main() {\n"
        "  int maxIter = 50;"
        "  float shade = convergence(pos, maxIter);\n"
        "  out_color = vec4(shadeToColor(shade / float(maxIter)), 1.0);\n"
        "}";
    
    auto vertexShader = GLShader::compile(GL_VERTEX_SHADER, vertexShaderSrc);
    auto fragmentShader = GLShader::compile(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    m_program = GLProgram::link(vertexShader, fragmentShader);
}

void MandelbrotRenderer::drawFrame()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_quadRenderer.draw(m_program);
}