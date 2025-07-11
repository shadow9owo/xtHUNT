#include "globalvars.hpp" 
#include <iostream>
#include "raylib.h"
#include "ini.hpp"
#include "Render.hpp"
#include "Input.hpp"

namespace GAME { extern int run(); }

int main()
{
    GAME::run();
}

namespace GAME
{
    RenderTexture2D target;
    int run()
    {
        InitWindow(DATA::Vars::Consts::win[0], DATA::Vars::Consts::win[1], "xthunt");

        DATA::Load();

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

        SetTargetFPS(300); //cap fps 

        SetExitKey(0);

        while (DATA::Vars::running)
        {
            if (WindowShouldClose()) 
            {
                DATA::Vars::running = false;
            }

            INPUT::HandleInput();

            BeginTextureMode(target);

            Renderer::RenderUI();

            ClearBackground(BLACK); 

            Renderer::RenderWorld();
            
            EndTextureMode();

            BeginDrawing();

            ClearBackground(BLACK); 
            DrawTextureRec(target.texture, Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0, 0}, WHITE); //fixed aspect ratio

            EndDrawing();
        }

        DATA::Save();
        
        return 0;
    }
}