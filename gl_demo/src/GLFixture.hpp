#ifndef GLDEMO_GLFIXTURE_HPP_INCLUDED
#define GLDEMO_GLFIXTURE_HPP_INCLUDED

#include <ImageApprovals.hpp>
#include <memory>

class GLFixture
{
public:
    GLFixture();
    GLFixture(const GLFixture&) = delete;
    GLFixture(GLFixture&&) = delete;
    ~GLFixture();

    GLFixture& operator =(const GLFixture&) = delete;
    GLFixture& operator =(GLFixture&&) = delete;

    ImageApprovals::Image getRenderedImage() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

#endif // GLDEMO_GLFIXTURE_HPP_INCLUDED