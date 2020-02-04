#ifndef GLDEMO_GLUTILS_HPP_INCLUDED
#define GLDEMO_GLUTILS_HPP_INCLUDED

#include <GL/glew.h>

class GLShader
{
public:
    GLShader() = default;
    GLShader(const GLShader&) = delete;
    GLShader(GLShader&&);
    ~GLShader();

    GLShader& operator =(const GLShader&) = delete;
    GLShader& operator =(GLShader&&);

    GLuint glObject() const { return m_shader; }

    static GLShader compile(GLenum type, const char* source);

private:
    GLuint m_shader = 0;
};

class GLProgram
{
public:
    GLProgram() = default;
    GLProgram(const GLProgram&) = delete;
    GLProgram(GLProgram&&);
    ~GLProgram();

    GLProgram& operator =(const GLProgram&) = delete;
    GLProgram& operator =(GLProgram&&);

    GLuint glObject() const { return m_program; }

    int getUniformLocation(const char* name) const;

    static GLProgram link(const GLShader& vertexShader, const GLShader& fragmentShader);

private:
    GLuint m_program = 0;
};

struct Vertex
{
    float x, y;
};

template<typename StructT, typename MemberT>
const void* offsetOf(const MemberT StructT::* member)
{
    const StructT* basePtr = nullptr;
    return &(basePtr->*member);
}

class QuadRenderer
{
public:
    QuadRenderer();
    QuadRenderer(const QuadRenderer&) = delete;
    QuadRenderer(QuadRenderer&&) = delete;
    ~QuadRenderer();

    QuadRenderer& operator =(const QuadRenderer&) = delete;
    QuadRenderer& operator =(QuadRenderer&&) = delete;

    void draw() const;

private:
    GLuint m_vao = 0;
    GLuint m_vertexBuffer = 0;
};

#endif // GLDEMO_GLUTILS_HPP_INCLUDED
