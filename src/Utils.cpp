#include "Types.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include "globalvars.hpp"
#include "main.hpp"

namespace Utils
{
    Vector2I GetMousePositionPro()
    {
        if (DATA::Vars::isfullscreen)
        {
            return {
                (int)(GetMouseX() / ((float)GetScreenWidth() / GAME::target.texture.width)),
                (int)(GetMouseY() / ((float)GetScreenHeight() / GAME::target.texture.height))
            };
        }
        else {
            return {
                GetMouseX(),
                GetMouseY()
            };
        }
    }
}