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

struct ClickableObject
{
    Vector2I position;
    Vector2I size;
    int id;
    Color fontColor;
    Color bgColor;
    int fontSize;

    ClickableObject(Vector2I pos, Vector2I sz, int id2, Color fColor = WHITE, Color bColor = BLACK, int fSize = 12)
        : position(pos), size(sz), id(id2), fontColor(fColor), bgColor(bColor), fontSize(fSize) {}
};

enum Scenes
{
    MainMenu,
    Game
};

enum ObjectIDs
{
    Home_Bed = 1,
    Home_Sink,
    Home_Door,
    Hallway_Exit,
    Hallway_Door_bedroom,
    Hallway_Door_Broken
};

enum Items
{
    Item_None = 0
};

enum Map
{
    Map_None,
    Home,
    Hallway
};

enum TexturesEnum
{
    CursorHover,
    CursorGrab,
    texture_Home,
    texture_hallway
};

struct TextureStruct
{
    TexturesEnum texture;
    Texture2D TextureData;

    TextureStruct(TexturesEnum tex, Texture2D data) : texture(tex), TextureData(data) {}
};