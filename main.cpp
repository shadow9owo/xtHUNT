#include <iostream>
#include "raylib.h"
#include "./Data/globalvars.hpp" 
#include "ini.hpp"
#include "Render.hpp"

namespace GAME { extern int run(); }

int main()
{
    GAME::run();
}

namespace GAME
{
    int run()
    {
        InitWindow(DATA::Vars::Consts::win[0], DATA::Vars::Consts::win[1], "xthunt");

        DATA::Load();

        SetTargetFPS(300);     

        SetExitKey(0);

        while (DATA::Vars::running)
        {
            if (WindowShouldClose()) 
            {
                DATA::Vars::running = false;
            }

            BeginDrawing();

            Renderer::RenderUI();

            ClearBackground(BLACK); 

            Renderer::RenderWorld();
            
            EndDrawing();
        }

        DATA::Save();
        
        return 0;
    }
}