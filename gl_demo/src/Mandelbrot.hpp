#ifndef GLDEMO_MANDELBROT_HPP_INCLUDED
#define GLDEMO_MANDELBROT_HPP_INCLUDED

#include "GLUtils.hpp"

class MandelbrotRenderer
{
public:
    MandelbrotRenderer();
    MandelbrotRenderer(const MandelbrotRenderer&) = delete;
    MandelbrotRenderer(MandelbrotRenderer&&) = delete;
    ~MandelbrotRenderer() = default;

    MandelbrotRenderer& operator =(const MandelbrotRenderer&) = delete;
    MandelbrotRenderer& operator =(MandelbrotRenderer&&) = delete;

    void drawFrame();

private:
    GLProgram m_program;
    QuadRenderer m_quadRenderer;
};

#endif // GLDEMO_MANDELBROT_HPP_INCLUDED