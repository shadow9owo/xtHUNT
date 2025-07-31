#include <string>
#include <raylib.h>
#include "json.hpp"

#pragma once

using json = nlohmann::json;

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
    Scene_MainMenu,
    Scene_Game
};

enum ObjectIDs
{
    Object_None = 0,
    ObjectID_Home_Bed,
    ObjectID_Home_Sink,
    ObjectID_Home_Door,
    ObjectID_Hallway_Exit,
    ObjectID_Hallway_Door_bedroom,
    ObjectID_Hallway_Door_Broken
};

enum Items
{
    Item_None = 0
};

enum Map
{
    Map_None,
    Map_Home,
    Map_Hallway,
    Map_outsidehome
};

enum TexturesEnum
{
    TextureEnum_None,
    CursorHover,
    CursorGrab,
    texture_Home,
    texture_hallway,
    Texture_outside_home,
    Eye,
    Eye2
};

struct Inventory
{
    std::vector<int> Items;  

    json toJson() const {
        json j;
        j["Items"] = Items;
        return j;
    }
};

struct TextureStruct
{
    TexturesEnum texture;
    Texture2D TextureData;

    TextureStruct(TexturesEnum tex, Texture2D data) : texture(tex), TextureData(data) {}
};