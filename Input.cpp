#include "Input.hpp"
#include "raylib.h"
#include "globalvars.hpp"

namespace INPUT
{
    void HandleInput()
    {
        if (IsKeyPressed(KEY_F11))
        {
            DATA::Vars::isfullscreen = !DATA::Vars::isfullscreen;

            if (DATA::Vars::isfullscreen)
            {
                SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
                ToggleFullscreen();
            }
            else
            {
                ToggleFullscreen();
                SetWindowSize(DATA::Vars::Consts::win[0], DATA::Vars::Consts::win[1]);
            }
        }
    }
}
