#include "raylib.h"
#include "globalvars.hpp"
#include "logger.hpp"
#include "Types.hpp"
#include "Utils.hpp"
#include "Render.hpp"
#include <iostream>
#include "Textures.hpp"

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
            DrawText(text.c_str(), mousePos.x, mousePos.y, 24, WHITE);
        }
    }

    void RenderWorld()
    {
        switch (DATA::Vars::currentScene)
        {
            case MainMenu:
                //return earlier no need to init 2dcamera
                return;
            case Game:
                BeginMode2D(cam);
                // draw world
                switch (DATA::Vars::currentlocation)
                {
                case Map::Home:
                    DrawTexturePro(Textures::textures[texture_Home].TextureData,
                               Rectangle{0, 0, (float)Textures::textures[texture_Home].TextureData.width, (float)Textures::textures[texture_Home].TextureData.height},
                               Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                               Vector2{0, 0}, 0.0f, WHITE);
                    break;
                
                default:
                    break;
                }
                EndMode2D();
                return;
            default:
                LOGGER::Log("something went really wrong i fucking hate this (Void Renderer::RenderWorld())");
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
                Renderer::UI_Elements::RenderToolTip(Utils::ObjectIDToSTR((ObjectIDs)i.id));
            }
        }
        return;
    }

    void RenderUI()
    {
        Button Exitbtn = Button(Vector2I(2, 100), Vector2I(MeasureText("Exit Game",24) * 1.5f, 40), "Exit Game",WHITE, {192,192,192,64}, 24);
        Button Startbtn = Button(Vector2I(2, 50), Vector2I(MeasureText("Start Game",24) * 1.5f, 40), "Start Game", WHITE, {192,192,192,64}, 24);
        
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
            case MainMenu:
                DrawTextPro(font,"code name xthunt (change later)",{2,6},{0,0},0,24,0.2f,WHITE);
                
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
                    DATA::Vars::currentlocation = Map::Home;
                    DATA::Vars::currentScene = Game;
                    LOGGER::Log("Starting game...");
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
                    LOGGER::Log("Exiting game...");
                }
                return;
            case Game:
                return;
            default:
                LOGGER::Log("something went really wrong i fucking hate this (Void Renderer::RenderUI())");
                return;
        }
        return;
    }
}