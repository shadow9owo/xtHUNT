#include "globalvars.hpp" 
#include <iostream>
#include "raylib.h"
#include "ini.hpp"
#include "Render.hpp"
#include "Input.hpp"
#include "main.hpp"
#include "Textures.hpp"
#include "Utils.hpp"

namespace GAME { extern int run(); }

int main(int argc, char *argv[])
{
    DATA::Load();
    if (argc > 1)
    {
        if (std::string(argv[1]) == "--debug")
        {
            DATA::Vars::debug = true;
            std::cout << "le debugos estest onos >:D (yes this dosesnt have any meaning but its funny to me)" << std::endl; 
        }
    }
    GAME::run();
}

namespace GAME
{
    RenderTexture2D target; // hope the user doesnt change the ini values that will prob fuck up the scaling
    int run()
    {
        InitWindow(DATA::Vars::Consts::win[0], DATA::Vars::Consts::win[1], "xthunt");
        InitAudioDevice();

        Camera2D camera = { 0 };
        camera.target = (Vector2){0,0};
        camera.offset = (Vector2){0,0};
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

        Renderer::cam = camera;
        
        Textures::Load();

        Renderer::font = GetFontDefault();
        target = LoadRenderTexture(DATA::Vars::Consts::win[0], DATA::Vars::Consts::win[1]);

        if (!DATA::Vars::debug) //might be helpful 
        {
            HideCursor();
        }

        if (DATA::Vars::isfullscreen)
        {
            SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
            ToggleFullscreen();
        }
        else
        {
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

            ClearBackground(BLACK); 

            Renderer::RenderWorld();

            Renderer::RenderUI();
                            
            Renderer::UI_Elements::RenderCursor(false);
            
            Renderer::RenderUIOverlay();

            EndTextureMode();

            BeginDrawing();

            DrawTextureRec(target.texture,
                Rectangle{0, (float)target.texture.height, (float)target.texture.width, -(float)target.texture.height},
                Vector2{0, 0}, WHITE);
             //fixed aspect ratio

            EndDrawing();
        }

        DATA::Save();

        Textures::Unload();

        CloseWindow();
        CloseAudioDevice();
        
        return 0;
    }
}