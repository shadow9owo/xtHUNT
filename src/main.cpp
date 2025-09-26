#include "globalvars.hpp" 
#include <iostream>
#include "raylib.h"
#include "ini.hpp"
#include "Render.hpp"
#include "Input.hpp"
#include "main.hpp"
#include "Textures.hpp"
#include "Utils.hpp"
#include "logger.hpp"
#include "Npc.hpp"

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
        camera.target = {0,0};
        camera.offset = {0,0};
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

        Npc::InitPopulation();

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

            if (DATA::Vars::halt && DATA::Vars::savefilecorruptionprevention)
            {
                EndTextureMode();
                for (size_t i = 0; i < 10; i++)
                {
                    LOGGER::LogERROR("!!!FATAL ERROR ENCOUNTERED GAME HALTED TO PREVENT CORRUPTION!!!");
                }
                LOGGER::LogERROR("if this is a mistake you can disable this feature in the ini file.");
                
                while (DATA::Vars::running) //good enough prob wont fix
                {
                    BeginTextureMode(target);
                    ClearBackground(BLACK); 
                    LOGGER::RenderLogs();
                    EndTextureMode();

                    BeginDrawing();

                    DrawTexturePro(target.texture,{0,0,(float)target.texture.width,-(float)target.texture.height}
                    ,{0,0,(float)Utils::getscreensize().x,(float)Utils::getscreensize().y},
                    {0,0},0,WHITE);

                    EndDrawing();

                    if (WindowShouldClose()) 
                    {
                        DATA::Vars::running = false;
                    }
                }
            }

            Renderer::RenderWorld();

            Renderer::RenderUI();

            Renderer::RenderUIOverlay();

            if (DATA::Vars::currentScene == Scene_Game)
            {
                if (DATA::Vars::gamestate.difficulty == D_Undefined)
                {
                    DialogueTree difficultyDialogue {
                    {
                                DialogueText{{
                                    {"Choose your difficulty", Mood_None, -1},
                                    {"Normal", Mood_None, -1},
                                    {"Hard", Mood_None, -1},
                                    {"Impossible", Mood_None, -1}
                                }}
                    },
                    Characters_None,
                    Mood_None,
                    DialogueState_Talking,
                    0,
                    DialogueID_Intro
                };
                Npc::InitDialogue(difficultyDialogue);
                    
            }

            int clicked = -1;
            int choice = -1;

            if (Npc::currentDialogue.state != DialogueState_Finished 
                && !Npc::currentDialogue.texts.empty())
            {
                clicked = Npc::RenderDialogue(); 
            
                if (clicked > 0)
                {
                    choice = Npc::DialogueCallBack(DialogueID_Intro, clicked);
                    DATA::Vars::Message = ""; 
                }
            }

            if (choice > 0)
            {
                Npc::HandleDialogue(Npc::currentDialogue.id, choice);
            }


            }
            
            Renderer::UI_Elements::RenderCursor(false);
            
            LOGGER::RenderLogs();

            if (DATA::Vars::paused) 
            { 
                if (DATA::Vars::currentScene == Scene_Game)
                {
                    Renderer::paused();
                }else 
                {
                    DATA::Vars::paused = false;
                }
            }

            EndTextureMode();

            Utils::updatetimers();

            BeginDrawing();

            //target.texture
            DrawTexturePro(target.texture,{0,0,(float)target.texture.width,-(float)target.texture.height}
            ,{0,0,(float)Utils::getscreensize().x,(float)Utils::getscreensize().y},
            {0,0},0,WHITE);
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