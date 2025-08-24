#include <string>
#include <raylib.h>
#include "json.hpp"

#pragma once

using json = nlohmann::json;

enum Character_Mood
{
    Mood_None = 0,
    Mood_Angry,
    Mood_Confused,
    Mood_Sad
};

//math struct
struct Vector2I
{
    int x;
    int y;

    Vector2I(int x, int y) : x(x), y(y) {}
};

//dialogue system structs
struct DialogueOption
{
    std::string text;        
    Character_Mood mood;     
    int nextIndex;           
};

struct DialogueText
{
    std::vector<DialogueOption> options;
};


enum Characters
{
    //NPCs
    Characters_Undefined = 0,
    Characters_None,
    Characters_sekta_priest,
    Characters_sekta_leader,
    Characters_sekta_follower_0,
    Characters_sekta_follower_1,
    Characters_sekta_follower_2,
    Characters_sekta_follower_3,
    Characters_crack_dealer_0,
    Characters_crack_dealer_1,
    Characters_crackhead_0,
    Characters_crackhead_1,
    Characters_crackhead_2,
    Characters_crackhead_3,
    Characters_storeclerk_0,
    Characters_storeclerk_1,
    Characters_storeclerk_2,
    Characters_storeclerk_3,
    Characters_job_boss,
    Characters_female_0,
    Characters_female_1,
    Characters_female_2,
    Characters_female_3,
    Characters_male_0,
    Characters_male_1,
    Characters_male_2,
    Characters_male_3
};

enum DialogueState
{
    DialogueState_Talking,
    DialogueState_Choice,
    DialogueState_Finished
};

enum DialogueID
{
    DialogueID_None = 0,
    DialogueID_Intro
};

struct DialogueTree
{
    std::vector<DialogueText> texts;
    Characters Character;
    Character_Mood mood;
    DialogueState state = DialogueState_Finished;
    int currentLine = 0;
    DialogueID id;
};


//UI elements structs

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

//game states

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

//inventory system structs

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

enum Game_Difficulty
{
    D_Undefined = 0,
    D_Normal = 1,
    D_Hard,
    D_Impossible // 2 lazy 2 implement you can change this in the ini file but prob will stay unimplemented so if youre reading this then yea there was suppoused to be an harder difficulty than hard
};

enum Map
{
    Map_None,
    Map_Home,
    Map_Hallway,
    Map_outsidehome
};

struct Npc_t
{
    Characters character;
    bool alive;
};

struct Population
{
    std::vector<Npc_t> npcs;
};

struct Game_State //save this
{
    Scenes currentScene;
    Map currentLocation;
    Inventory playerInventory;
    Population population;
    Game_Difficulty difficulty;

        json toJson() const {
        json j;
        j["currentScene"] = static_cast<int>(currentScene); 
        j["currentLocation"] = static_cast<int>(currentLocation);
        j["difficulty"] = static_cast<int>(difficulty);
        j["playerInventory"] = playerInventory.toJson();

        // Population
        json jPopulation = json::array();
        for (const auto& npc : population.npcs) {
            jPopulation.push_back({
                {"character", static_cast<int>(npc.character)},
                {"alive", npc.alive}
            });
        }
        j["population"] = jPopulation;

        return j;
    }

    void fromJson(const json& j) {
        currentScene = static_cast<Scenes>(j.value("currentScene", 0));
        currentLocation = static_cast<Map>(j.value("currentLocation", 0));
        difficulty = static_cast<Game_Difficulty>(j.value("difficulty", 0));

        if (j.contains("playerInventory"))
            playerInventory.fromJson(j["playerInventory"]);

        population.npcs.clear();
        if (j.contains("population")) {
            for (const auto& jNpc : j["population"]) {
                Npc_t npc;
                npc.character = static_cast<Characters>(jNpc.value("character", 0));
                npc.alive = jNpc.value("alive", true);
                population.npcs.push_back(npc);
            }
        }
    }
};

// textures

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