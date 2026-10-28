#include <doctest.h>

#include <limits>

#include "Core/Platform/WindowPixelDensity.h"

TEST_CASE("points convert to drawable pixels by the pixel density [platform][hidpi]")
{
    CHECK(Core::Platform::PointsToPixels(512.0f, 2.0f) == doctest::Approx(1024.0f));
    CHECK(Core::Platform::PixelsToPoints(1024.0f, 2.0f) == doctest::Approx(512.0f));
    CHECK(Core::Platform::PointsToPixels(300.0f, 1.0f) == doctest::Approx(300.0f));
}

TEST_CASE("an unknown pixel density converts one to one [platform][hidpi]")
{
    CHECK(Core::Platform::UsablePixelDensity(0.0f) == doctest::Approx(1.0f));
    CHECK(Core::Platform::UsablePixelDensity(-2.0f) == doctest::Approx(1.0f));
    CHECK(Core::Platform::UsablePixelDensity(std::numeric_limits<float>::quiet_NaN()) == doctest::Approx(1.0f));
    CHECK(Core::Platform::PixelsToPoints(640.0f, 0.0f) == doctest::Approx(640.0f));
}
