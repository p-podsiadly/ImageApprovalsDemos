#include "GLFixture.hpp"
#include <SDL.h>
#include <GL/glew.h>

using namespace ImageApprovals;

namespace
{
    struct Deleter
    {
        void operator ()(SDL_Window* w) const
        { SDL_DestroyWindow(w); }

        void operator ()(SDL_GLContext ctx) const
        { SDL_GL_DeleteContext(ctx); }
    };

    using GuardedWindow = std::unique_ptr<SDL_Window, Deleter>;
    using GuardedGLContext = std::unique_ptr<std::remove_pointer_t<SDL_GLContext>, Deleter>;
}

struct GLFixture::Impl
{
    const uint32_t wndWidth = 256;
    const uint32_t wndHeight = 256;

    GuardedWindow window;
    GuardedGLContext glContext;

    Impl()
    {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_GL_ResetAttributes();
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        window.reset(SDL_CreateWindow("GLFixture", 0, 0, wndWidth, wndHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN));
        if(!window)
        {
            throw std::runtime_error("Could not create SDL window!");
        }

        glContext.reset(SDL_GL_CreateContext(window.get()));
        if(!glContext)
        {
            throw std::runtime_error("Could not create OpenGL context!");
        }

        if(glewInit() != GLEW_OK)
        {
            throw std::runtime_error("Could not initialize GLEW!");
        }

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    ~Impl()
    {
        window.reset();
        glContext.reset();
        SDL_Quit();
    }

    Image getRenderedImage() const
    {
        Image img(
            PixelFormat::getRgbAlphaU8(),
            ColorSpace::getLinear(),
            Size(wndWidth, wndHeight),
            4);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        glReadPixels(
            0, 0, wndWidth, wndHeight,
            GL_RGBA, GL_UNSIGNED_BYTE,
            img.getPixelData());

        return img;
    }
};

GLFixture::GLFixture()
    : m_impl(std::make_unique<Impl>())
{}

GLFixture::~GLFixture() = default;

Image GLFixture::getRenderedImage() const
{
    return m_impl->getRenderedImage();
}