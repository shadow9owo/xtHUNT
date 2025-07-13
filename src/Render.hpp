#include "raylib.h"
#include <string>
#include "Types.hpp"

namespace Renderer
{
    extern Camera2D cam;
    extern Font font;
    namespace UI_Elements
    {
        extern void RenderButton(Button Button);
        extern bool IsButtonClicked(Button Button);
        extern bool IsButtonHovered(Button Button);
        extern void RenderCursor(bool hovering);
        extern void RenderToolTip(std::string text);
    }

    extern void RenderWorld();
    extern void RenderUIOverlay();
    extern void RenderUI();
}