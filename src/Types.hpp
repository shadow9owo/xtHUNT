#include <string>
#include <raylib.h>

#pragma once

struct Vector2I
{
    int x;
    int y;

    Vector2I(int x, int y) : x(x), y(y) {}
};

struct Button
{
    Vector2I position;
    Vector2I size;
    std::string text;
    Color fontColor;
    Color bgColor;
    int fontSize;

    Button(Vector2I pos, Vector2I sz, std::string txt, Color fColor = WHITE, Color bColor = BLACK, int fSize = 12)
        : position(pos), size(sz), text(std::move(txt)), fontColor(fColor), bgColor(bColor), fontSize(fSize) {}
};

enum Scenes
{
    MainMenu,
    Game
};

enum TexturesEnum
{
    CursorHover,
    CursorGrab
};

struct TextureStruct
{
    TexturesEnum texture;
    Texture2D TextureData;

    TextureStruct(TexturesEnum tex, Texture2D data) : texture(tex), TextureData(data) {}
};