#include "Input.hpp"
#include "raylib.h"
#include "globalvars.hpp"
#include "Utils.hpp"
#include "logger.hpp"

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
        if (IsMouseButtonDown(1))
        {
            Utils::ClearMessage();
        }

        if (DATA::Vars::debug)
        {
            if (IsMouseButtonPressed(0))
            {
                if (DATA::Vars::placementbuffer.size() > 1)
                {
                    DATA::Vars::placementbuffer.clear();
                    LOGGER::Log("cleared buffer");
                }
                LOGGER::Log("added pos to buffer");
                DATA::Vars::placementbuffer.push_back(Utils::GetMousePositionPro());
            }
            if (DATA::Vars::placementbuffer.size() > 1 && IsKeyPressed(KEY_C))
            {
                LOGGER::Log("clipboard set");
                std::string result =
                    std::to_string(DATA::Vars::placementbuffer.at(0).x) + "X\n" +
                    std::to_string(DATA::Vars::placementbuffer.at(0).y) + "Y\n" +
                    std::to_string(Utils::GetSizeFromPositions(DATA::Vars::placementbuffer).x) + "X\n" +
                    std::to_string(Utils::GetSizeFromPositions(DATA::Vars::placementbuffer).y) + "Y"; 

                SetClipboardText(result.c_str());          
            }
        }
    }
}
