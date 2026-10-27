#include <doctest.h>
#include <SDL3/SDL_video.h>

#include "Core/Platform/sdl3/SDLWindowFlags.h"

#if defined(__APPLE__)
TEST_CASE("SDL windows request a 1x drawable on Apple [platform][sdl]")
{
    // The 2D pipeline doesn't handle a pixel density above 1 yet (Retina, see SDLWindowFlags.h).
    const SDL_WindowFlags flags = Core::Platform::BuildSDLWindowFlags(false, false);

    CHECK((flags & SDL_WINDOW_HIGH_PIXEL_DENSITY) == 0);
}
#else
TEST_CASE("SDL windows always request high pixel density [platform][sdl]")
{
    const SDL_WindowFlags flags = Core::Platform::BuildSDLWindowFlags(false, false);

    CHECK((flags & SDL_WINDOW_HIGH_PIXEL_DENSITY) != 0);
}
#endif

TEST_CASE("SDL window flags preserve fullscreen and resizable requests [platform][sdl]")
{
    const SDL_WindowFlags flags = Core::Platform::BuildSDLWindowFlags(true, true);

    CHECK((flags & SDL_WINDOW_FULLSCREEN) != 0);
    CHECK((flags & SDL_WINDOW_RESIZABLE) != 0);
}

TEST_CASE("SDL startup focus follows the input-focus window flag [platform][sdl]")
{
    const SDL_WindowFlags unfocusedFullscreen = SDL_WINDOW_FULLSCREEN;
    const SDL_WindowFlags focusedFullscreen = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_FOCUS;

    CHECK_FALSE(Core::Platform::HasSDLWindowInputFocus(unfocusedFullscreen));
    CHECK(Core::Platform::HasSDLWindowInputFocus(focusedFullscreen));
}
