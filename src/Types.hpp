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
    ObjectID_Hallway_Door_Broken,
    ObjectID_HomeEntrace,
    ObjectID_HomeEntrance_trashcan
};

enum Item_Type
{
    None = 0,
    Weapon,
    Food,
    Tool,
    Health
};

enum Item_ID
{
    Item_None = 0,
    Item_Stick
};

enum Item_Rarity
{
    Item_Rarity_Common = 0,
    Item_Rarity_Uncommon,
    Item_Rarity_Rare,
    Item_Rarity_Secret
};

struct Item
{
    Item_ID id;
    Item_Type type;
    Item_Rarity rarity;
    short amount;
    bool equipped;
};

struct Inventory
{
    std::vector<Item> items;

    void addItem(const Item& item) {
        items.push_back(item);
    }

    Item* getItem(Item_ID itemId) {
        for (auto& item : items) {
            if (item.id == itemId) return &item;
        }
        return nullptr;
    }

    void removeItem(Item_ID itemId) {
        items.erase(std::remove_if(items.begin(), items.end(),
            [itemId](const Item& item) { return item.id == itemId; }), items.end());
    }

    void useItem(Item_ID itemId) {
        Item* item = getItem(itemId);
        if (!item) return;
        item->equipped = true;
    }

    json toJson() const {
        json j = json::array();
        for (const auto& item : items) {
            j.push_back({
                {"id", static_cast<int>(item.id)},
                {"type", static_cast<int>(item.type)},
                {"rarity", static_cast<int>(item.rarity)},
                {"amount", item.amount},
                {"equipped", item.equipped}
            });
        }
        return j;
    }

    void fromJson(const json& j) {
        items.clear();
        for (const auto& jitem : j) {
            Item item;
            item.id = static_cast<Item_ID>(jitem.value("id", 0));
            item.type = static_cast<Item_Type>(jitem.value("type", 0));
            item.rarity = static_cast<Item_Rarity>(jitem.value("rarity", 0));
            item.amount = jitem.value("amount", 1);
            item.equipped = jitem.value("equipped", false);
            addItem(item);
        }
    }
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

struct TextureStruct
{
    TexturesEnum texture;
    Texture2D TextureData;

    TextureStruct(TexturesEnum tex, Texture2D data) : texture(tex), TextureData(data) {}
};

enum Sprites
{
    Sprite_None,
    Sprite_Home,
    Sprite_Hallway,
    Sprite_OutsideHome
};