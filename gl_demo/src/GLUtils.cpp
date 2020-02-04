#include "GLUtils.hpp"
#include <stdexcept>
#include <string>

GLShader::GLShader(GLShader&& other)
{
    *this = std::move(other);
}

GLShader::~GLShader()
{
    if(m_shader)
    {
        glDeleteShader(m_shader);
    }
}

GLShader& GLShader::operator =(GLShader&& rhs)
{
    if(this != &rhs)
    {
        if(m_shader)
        {
            glDeleteShader(m_shader);
        }

        m_shader = rhs.m_shader;
        rhs.m_shader = 0;
    }

    return *this;
}

GLShader GLShader::compile(GLenum type, const char* source)
{
    std::string typeStr;
    switch(type)
    {
    case GL_VERTEX_SHADER:
        typeStr = "vertex";
        break;
    case GL_FRAGMENT_SHADER:
        typeStr = "fragment";
        break;
    default:
        throw std::runtime_error("invalid shader type!");
    }

    GLShader sh;
    sh.m_shader = glCreateShader(type);
    glShaderSource(sh.m_shader, 1, &source, nullptr);
    glCompileShader(sh.m_shader);

    int ok = GL_FALSE;
    glGetShaderiv(sh.m_shader, GL_COMPILE_STATUS, &ok);
    if(!ok)
    {
        throw std::runtime_error("Failed to compile a " + typeStr + " shader!");
    }

    return sh;
}

GLProgram::GLProgram(GLProgram&& other)
{
    *this = std::move(other);
}

GLProgram::~GLProgram()
{
    if(m_program)
    {
        glDeleteProgram(m_program);
    }
}

GLProgram& GLProgram::operator =(GLProgram&& rhs)
{
    if(this != &rhs)
    {
        if(m_program)
        {
            glDeleteProgram(m_program);
        }

        m_program = rhs.m_program;
        rhs.m_program = 0;
    }

    return *this;
}

int GLProgram::getUniformLocation(const char* name) const
{
    if(m_program)
    {
        return glGetUniformLocation(m_program, name);
    }

    return -1;
}

GLProgram GLProgram::link(const GLShader& vertexShader, const GLShader& fragmentShader)
{
    GLProgram prog;
    prog.m_program = glCreateProgram();

    glAttachShader(prog.m_program, vertexShader.glObject());
    glAttachShader(prog.m_program, fragmentShader.glObject());

    glBindAttribLocation(prog.m_program, 0, "in_pos");
    glBindFragDataLocation(prog.m_program, 0, "out_color");

    glLinkProgram(prog.m_program);

    glDetachShader(prog.m_program, vertexShader.glObject());
    glDetachShader(prog.m_program, fragmentShader.glObject());

    int ok = GL_FALSE;
    glGetProgramiv(prog.m_program, GL_LINK_STATUS, &ok);
    if(!ok)
    {
        throw std::runtime_error("Failed to link a program!");
    }

    return prog;
}

QuadRenderer::QuadRenderer()
{
    const Vertex vertices[]{
        { -1.0f, 1.0f },
        { -1.0f, -1.0f },
        { 1.0f, 1.0f },

        { 1.0f, 1.0f },
        { -1.0f, -1.0f },
        { 1.0f, -1.0f }
    };

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetOf(&Vertex::x));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

QuadRenderer::~QuadRenderer()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vertexBuffer);
}

void QuadRenderer::draw() const
{
    glBindVertexArray(m_vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
