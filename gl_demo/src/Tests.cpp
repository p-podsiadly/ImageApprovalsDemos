#include "GLFixture.hpp"
#include <doctest/doctest.h>
#include <ApprovalTests.hpp>
#include <GL/glew.h>

using namespace ImageApprovals;
using namespace ApprovalTests;

TEST_CASE_FIXTURE(GLFixture, "Clearing color buffer with fixed color")
{
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto image = getRenderedImage();

    Approvals::verify(ImageWriter(image));
}