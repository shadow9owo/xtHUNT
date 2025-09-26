#include "raylib.h"
#include "globalvars.hpp"
#include "logger.hpp"
#include "Types.hpp"
#include "Utils.hpp"
#include "Render.hpp"
#include <iostream>
#include "Textures.hpp"
#include <cmath>
#include "IO.hpp"
#include <stdexcept>
#include <iostream>
#include <cstdlib>

#define ASSERT_RELEASE(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "FATAL ERROR: " << (msg) << " (" << __FILE__ << ":" << __LINE__ << ")\n"; \
            std::abort(); \
        } \
    } while(0)


namespace Renderer
{
    Camera2D cam;
    Font font;
    namespace UI_Elements
    {
        void RenderButton(Button Button)
        {
            DrawRectangle(Button.position.x,Button.position.y, Button.size.x, Button.size.y, Button.bgColor);
            DrawText(Button.text.c_str(), Button.position.x + Button.size.x / 8, Button.position.y + Button.size.y / 8, Button.fontSize, Button.fontColor);
        }

        bool IsButtonClicked(Button Button)
        {
            Rectangle MouseRect = {(float)Utils::GetMousePositionPro().x, (float)Utils::GetMousePositionPro().y, 4, 4};
            Rectangle ButtonRect = {(float)Button.position.x, (float)Button.position.y, (float)Button.size.x, (float)Button.size.y};

            if (CheckCollisionRecs(MouseRect, ButtonRect))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    return true;
                }
            }
            return false;
        }

        bool IsButtonHovered(Button Button)
        {
            Rectangle MouseRect = {(float)Utils::GetMousePositionPro().x, (float)Utils::GetMousePositionPro().y, 4, 4};
            Rectangle ButtonRect = {(float)Button.position.x, (float)Button.position.y, (float)Button.size.x, (float)Button.size.y};

            if (CheckCollisionRecs(MouseRect, ButtonRect))
            {
                return true;
            }
            return false;
        }

        void RenderCursor(bool hovering = false)
        {
            Vector2I mousePos = Utils::GetMousePositionPro();
            
            if (hovering || IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                Texture a = Textures::textures[TexturesEnum::CursorGrab].TextureData;

                DrawTexturePro(
                    a,
                    Rectangle{0, 0, (float)a.width, (float)a.height},
                    Rectangle{(float)mousePos.x, (float)mousePos.y, 32, 32},
                    Vector2{0, 0},
                    0.0f,
                    WHITE
                );
            }else {
                Texture a = Textures::textures[TexturesEnum::CursorHover].TextureData;

                DrawTexturePro(
                    a,
                    Rectangle{0, 0, (float)a.width, (float)a.height},
                    Rectangle{(float)mousePos.x, (float)mousePos.y, 32, 32},
                    Vector2{0, 0},
                    0.0f,
                    WHITE
                );
            }
        }
        void RenderToolTip(std::string text)
        {
            Vector2I mousePos = Utils::GetMousePositionPro();
            DrawText(text.c_str(), mousePos.x+2, mousePos.y+2, 24, BLACK);
            DrawText(text.c_str(), mousePos.x, mousePos.y, 24, WHITE);
        }

        void RenderMessage()
        {
            if (!DATA::Vars::Message.empty())
            {
                float offset = Utils::GetInternalRenderWidth() / 2 - MeasureText(DATA::Vars::Message.c_str(), 24) / 2;
                DrawText(DATA::Vars::Message.c_str(), offset + 2, 82, 24, BLACK); 
                DrawText(DATA::Vars::Message.c_str(), offset, 80, 24, WHITE); 
            }
            return;
        }
    }

    void RenderWorld()
    {
        switch (DATA::Vars::currentScene)
        {
            case Scene_MainMenu:
                //return earlier no need to init 2dcamera
                return;
            case Scene_Game:
                BeginMode2D(cam);
                // draw world
                switch (DATA::Vars::currentlocation)
                {
                    case Map::Map_Home:
                        DrawTexturePro(Textures::textures[texture_Home].TextureData,
                                   Rectangle{0, 0, (float)Textures::textures[texture_Home].TextureData.width, (float)Textures::textures[texture_Home].TextureData.height},
                                   Rectangle{0, 0, (float)Utils::GetInternalRenderWidth(), (float)Utils::GetInternalRenderHeight()},
                                   Vector2{0, 0}, 0.0f, WHITE);
                        break;
                        
                    case Map::Map_Hallway:
                        DrawTexturePro(Textures::textures[texture_hallway].TextureData,
                                   Rectangle{0, 0, (float)Textures::textures[texture_hallway].TextureData.width, (float)Textures::textures[texture_hallway].TextureData.height},
                                   Rectangle{0, 0, (float)Utils::GetInternalRenderWidth(), (float)Utils::GetInternalRenderHeight()},
                                   Vector2{0, 0}, 0.0f, WHITE);
                        break;
                    case Map::Map_outsidehome:
                            DrawTexturePro(Textures::textures[Texture_outside_home].TextureData,
                                   Rectangle{0, 0, (float)Textures::textures[Texture_outside_home].TextureData.width, (float)Textures::textures[Texture_outside_home].TextureData.height},
                                   Rectangle{0, 0, (float)Utils::GetInternalRenderWidth(), (float)Utils::GetInternalRenderHeight()},
                                   Vector2{0, 0}, 0.0f, WHITE);
                        break;
                    default:
                        break;
                }
                EndMode2D();
                return;
            default:
                LOGGER::LogERROR("something went really wrong i fucking hate this (Void Renderer::RenderWorld())");
                return;
        }
        return;
    }

    void RenderUIOverlay()
    {
        for (ClickableObject i : Utils::GetButtons(DATA::Vars::currentlocation))
        {
            Vector2I pos = Utils::GetMousePositionPro();
            Rectangle buttonRect = {
                (float)i.position.x, 
                (float)i.position.y, 
                (float)i.size.x, 
                (float)i.size.y
            };
            if (CheckCollisionRecs({(float)pos.x,(float)pos.y,4,4},buttonRect))
            {
                if (!DATA::Vars::paused)
                {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Utils::ObjectIDClicked((ObjectIDs)i.id);
                    }
                    Renderer::UI_Elements::RenderToolTip(Utils::ObjectIDToSTR((ObjectIDs)i.id));
                }
            }
        }
        UI_Elements::RenderMessage();
        return;
    }

    void paused() // render pause menu
    {
        DrawRectangle(0, 0, Utils::GetInternalRenderWidth(), Utils::GetInternalRenderHeight(), {0, 0, 0, 128});
        DrawText("Paused", 0,0, 48, WHITE);

        return;
    }

    void RenderUI()
    {
        Color partiallyvisible = {255,255,255,32};

        Button Startbtn = Button(Vector2I((Utils::GetInternalRenderWidth() - (int)MeasureTextEx(GetFontDefault(), "Start Game", 24.0f, 1.0f).x) / 2, 100), Vector2I((int)MeasureTextEx(GetFontDefault(), "Start Game", 24.0f, 1.0f).x + 40, 40), "Start Game", WHITE, {192,192,192,64}, 24);
        Button Exitbtn  = Button(Vector2I((Utils::GetInternalRenderWidth() - (int)MeasureTextEx(GetFontDefault(), "Exit Game", 24.0f, 1.0f).x) / 2, 150), Vector2I((int)MeasureTextEx(GetFontDefault(), "Exit Game", 24.0f, 1.0f).x + 40, 40), "Exit Game",  WHITE, {192,192,192,64}, 24);
        
        if (DATA::Vars::debug)
        {
            std::string mousePos = std::to_string(GetMouseX()) + "X " + std::to_string(GetMouseY()) + "Y";
            DrawText(mousePos.c_str(), 0, 0, 24, WHITE);
            for (ClickableObject i : Utils::GetButtons(DATA::Vars::currentlocation))
            {
                DrawRectangleLinesEx({(float)i.position.x,(float)i.position.y,(float)i.size.x,(float)i.size.y},8,GREEN);
            }
            
        }

        switch (DATA::Vars::currentScene)
        {
            case Scene_MainMenu:
                DrawTextPro(font, "XThunt", { (Utils::GetInternalRenderWidth() - MeasureTextEx(font, "XThunt", 72.0f, 0.2f).x) / 2.0f, 6 }, {0, 0}, 0.0f, 72.0f, 0.2f, WHITE);

                for (float y = 0; y < Utils::GetInternalRenderHeight(); y += 64)
                {
                    for (float x = 0; x < Utils::GetInternalRenderWidth(); x += 128)
                    {
                        if (DATA::Vars::UIfloattimer < 0.2f)
                        {
                            DrawTexturePro(Textures::textures[Eye2].TextureData,
                                Rectangle{0, 0, (float)Textures::textures[Eye2].TextureData.width, (float)Textures::textures[Eye2].TextureData.height},
                                Rectangle{x, y, 128, 64},
                                Vector2{0, 0}, 0.0f, partiallyvisible);
                        }
                        else
                        {
                            DrawTexturePro(Textures::textures[Eye].TextureData,
                                Rectangle{0, 0, (float)Textures::textures[Eye].TextureData.width, (float)Textures::textures[Eye].TextureData.height},
                                Rectangle{x, y, 128, 64},
                                Vector2{0, 0}, 0.0f, partiallyvisible);
                        }
                    }
                }
                
                if (Renderer::UI_Elements::IsButtonHovered(Startbtn))
                {
                    Button a = Startbtn;
                    a.bgColor = {192,192,192,128};
                    Renderer::UI_Elements::RenderButton(a);
                }
                else {
                    Renderer::UI_Elements::RenderButton(Startbtn);
                }

                if (Renderer::UI_Elements::IsButtonClicked(Startbtn))
                {                    
                    if (!IO::FolderExists("./saves"))
                    {
                        if (IO::CreateFolder("./saves"))
                        {
                            LOGGER::LogDEBUG("Created saves folder");
                        }else {
                            LOGGER::LogDEBUG("!!!Failed to create saves folder!!!"); //crashfast
                            DATA::Vars::halt = true;
                        }
                    }

                    DATA::LoadGameData();
                    DATA::Vars::currentlocation = Map::Map_Home;
                    DATA::Vars::currentScene = Scene_Game;
                    
                }
                
                if (Renderer::UI_Elements::IsButtonHovered(Exitbtn)) //cool hover effect
                {
                    Button a = Exitbtn;
                    a.bgColor = {192,192,192,128};
                    Renderer::UI_Elements::RenderButton(a);
                }
                else {
                    Renderer::UI_Elements::RenderButton(Exitbtn);
                }

                if (Renderer::UI_Elements::IsButtonClicked(Exitbtn))
                {
                    DATA::Vars::running = false;
                    LOGGER::LogDEBUG("Exiting game...");
                }

                DrawTextPro(GetFontDefault(),Utils::getinfo().c_str(),{0,720-24},{0,0},0,24,0.2f,WHITE);
                return;
            case Scene_Game:
                return;
            default:
                LOGGER::LogERROR("something went really wrong i fucking hate this (Void Renderer::RenderUI())");
                return;
        }

        return;
    }
}