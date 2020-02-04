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

    void setCenter(float x, float y)
    {
        m_centerX = x;
        m_centerY = y;
    }

    void setZoom(float zoom)
    {
        m_zoom = zoom;
    }

    void drawFrame();

private:
    float m_centerX = 0.0f, m_centerY = 0.0f;
    float m_zoom = 1.0f;
    GLProgram m_program;
    int m_tformUniformLoc = -1;
    QuadRenderer m_quadRenderer;
};

#endif // GLDEMO_MANDELBROT_HPP_INCLUDED