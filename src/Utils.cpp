#include "Types.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include "globalvars.hpp"
#include "main.hpp"
#include "logger.hpp"
#include "cmath"
#include "main.hpp"

namespace Utils
{
    Vector2I GetMousePositionPro()
    {
        if (DATA::Vars::isfullscreen)
        {
            return {
                (int)(GetMouseX() / ((float)GetScreenWidth() / GAME::target.texture.width)),
                (int)(GetMouseY() / ((float)GetScreenHeight() / GAME::target.texture.height))
            };
        }
        else {
            return {
                GetMouseX(),
                GetMouseY()
            };
        }
    }
    std::vector<ClickableObject> GetButtons(Map map)
    {
        std::vector<ClickableObject> buffer;
        if (buffer.size() > 0)
        {
            buffer.clear();
        }
        switch (DATA::Vars::currentlocation)
        {
            case Map::Map_Home:      
                buffer.push_back(ClickableObject(Vector2I(105 , 436), Vector2I(467 , 191), ObjectID_Home_Bed, WHITE, {192, 192, 192, 64}, 24)); //initial size - initial position
                buffer.push_back(ClickableObject(Vector2I(663 , 256 ), Vector2I(159  , 347 ), ObjectID_Home_Door, WHITE, {192, 192, 192, 64}, 24));
                buffer.push_back(ClickableObject(Vector2I(1034  , 414 ), Vector2I(207  , 116 ), ObjectID_Home_Sink, WHITE, {192, 192, 192, 64}, 24));
                return buffer;
            case Map::Map_Hallway:
                buffer.push_back(ClickableObject(Vector2I(0 , 190), Vector2I(51 , 518), ObjectID_Hallway_Door_bedroom, WHITE, {192, 192, 192, 64}, 24)); //initial size - initial position
                buffer.push_back(ClickableObject(Vector2I(522 , 173 ), Vector2I(212  , 395 ), ObjectID_Hallway_Exit, WHITE, {192, 192, 192, 64}, 24));
                buffer.push_back(ClickableObject(Vector2I(1233  , 209 ), Vector2I(41  , 486 ), ObjectID_Hallway_Door_Broken, WHITE, {192, 192, 192, 64}, 24));
                return buffer;
            case Map::Map_outsidehome:
                buffer.push_back(ClickableObject(Vector2I(564 , 153), Vector2I(75  , 83), ObjectID_HomeEntrace, WHITE, {192, 192, 192, 64}, 24));
                buffer.push_back(ClickableObject(Vector2I(259  , 265), Vector2I(155  , 121), ObjectID_HomeEntrance_trashcan, WHITE, {192, 192, 192, 64}, 24));
                return buffer;
            case Map::Map_None:
                return {};
            default:
                LOGGER::Log("Unknown map in Utils::GetButtons()");
                return {};
        }
        return {};
    }
    std::string ObjectIDToSTR(ObjectIDs id)
    {
        switch (id)
        {
            case ObjectID_Home_Door:
                return "Click To Interact With The Door";
            case ObjectID_Home_Sink:
                return "Click to interact with the Sink";
            case ObjectID_Home_Bed:
                return "Click To interact with the Bed";
            case ObjectID_Hallway_Exit:
                return "Click To Exit The House";
            case ObjectID_HomeEntrace:
                return "Click To Enter The House";
            case ObjectID_HomeEntrance_trashcan:
                return "Click To search the trash";
            case ObjectID_Hallway_Door_bedroom:
                return "Click To Enter The Bedroom";
            case ObjectID_Hallway_Door_Broken:
                return "Click To Interact with the broken door";
            case Object_None:
                break;
        }
        return "";
    }

    std::string search(ObjectIDs object)
    {
        switch (object)
        {
        case ObjectID_HomeEntrance_trashcan:
            return "todo implement";
            break;
        default:
            break;
        }
        return "undefined";
    }

    void ObjectIDClicked(ObjectIDs id)
    {
        switch (id)
        {
            case ObjectIDs::ObjectID_Home_Bed:
                SetMessage("its just a bed");
                return;
            case ObjectIDs::ObjectID_Home_Sink:
                SetMessage("Its broken and leaking.");
                return;
            case ObjectIDs::ObjectID_Home_Door:
                DATA::Vars::currentlocation = Map::Map_Hallway;
                return;
            case ObjectIDs::ObjectID_Hallway_Exit:
                DATA::Vars::currentlocation = Map::Map_outsidehome;
                return;
            case ObjectIDs::ObjectID_Hallway_Door_bedroom:
                DATA::Vars::currentlocation = Map::Map_Home;
                return;
            case ObjectIDs::ObjectID_Hallway_Door_Broken:
                SetMessage("its stuck");
                return;
            case ObjectIDs::ObjectID_HomeEntrace:
                DATA::Vars::currentlocation = Map::Map_Hallway;
                return;
            case ObjectIDs::ObjectID_HomeEntrance_trashcan:
                SetMessage(search(id));
                return;
            case ObjectIDs::Object_None:
                return;
            default:
                return;
        }
    }

    void SetMessage(std::string message)
    {
        DATA::Vars::Message = message;
        return;
    }
    void ClearMessage()
    {
        DATA::Vars::Message = "";
        return;
    }

    Vector2I GetSizeFromPositions(const std::vector<Vector2I>& vec)
    {
        if (vec.size() < 2)
            return { 0, 0 };

        int minX = std::min(vec[0].x, vec[1].x);
        int maxX = std::max(vec[0].x, vec[1].x);
        int minY = std::min(vec[0].y, vec[1].y);
        int maxY = std::max(vec[0].y, vec[1].y);

        return { maxX - minX, maxY - minY };
    }

    void updatetimers()
    {
        if (DATA::Vars::UIfloattimer <= 0)
        {
            DATA::Vars::UIfloattimer = 1;
        }
        else 
        {
            DATA::Vars::UIfloattimer = DATA::Vars::UIfloattimer - GetFrameTime();
        }
        return;
    }

    std::string getinfo()
    {
        if (DATA::Vars::debug)
        {
            return "debug enabled";
        }else {
            return "alpha build";
        }
        return "";
    }

    Vector2I getscreensize()
    {
        if (DATA::Vars::isfullscreen)
        {
            return {GetMonitorWidth(0), GetMonitorHeight(0)};
        }else 
        {
            return {DATA::Vars::Consts::win[0],DATA::Vars::Consts::win[1]};
        }
        return {0,0};
    }

    int GetInternalRenderWidth() { return GAME::target.texture.width; }
    int GetInternalRenderHeight() { return GAME::target.texture.height; }
}