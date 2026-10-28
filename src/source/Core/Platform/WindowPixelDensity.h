#pragma once

#include <cmath>

namespace Core::Platform
{
// The game draws its 2D layer, lays out its UI and reads the mouse in the drawable's pixels, while
// SDL gives the window's size, the mouse position and cursor warps in points. On a high-density
// display (macOS Retina, Wayland at 200 %) one point is several pixels.

// SDL's pixels per point, or 1 when it is unknown (no window, or an error's 0).
[[nodiscard]] inline float UsablePixelDensity(float density)
{
    return std::isfinite(density) && density > 0.0f ? density : 1.0f;
}

// A position or a length in points, in drawable pixels.
[[nodiscard]] inline float PointsToPixels(float points, float density)
{
    return points * UsablePixelDensity(density);
}

// A position or a length in drawable pixels, in points.
[[nodiscard]] inline float PixelsToPoints(float pixels, float density)
{
    return pixels / UsablePixelDensity(density);
}

// The game window's pixels per point; 1 without a window.
float GameWindowPixelDensity();
} // namespace Core::Platform
