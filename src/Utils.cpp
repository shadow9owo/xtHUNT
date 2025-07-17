#include "Types.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include "globalvars.hpp"
#include "main.hpp"
#include "logger.hpp"
#include "cmath"

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
            case Map::Home:      
                buffer.push_back(ClickableObject(Vector2I(105 , 436), Vector2I(467 , 191), Home_Bed, WHITE, {192, 192, 192, 64}, 24)); //initial size - initial position
                buffer.push_back(ClickableObject(Vector2I(663 , 256 ), Vector2I(159  , 347 ), Home_Door, WHITE, {192, 192, 192, 64}, 24));
                buffer.push_back(ClickableObject(Vector2I(1034  , 414 ), Vector2I(207  , 116 ), Home_Sink, WHITE, {192, 192, 192, 64}, 24));
                return buffer;
            case Map::Hallway:
                buffer.push_back(ClickableObject(Vector2I(0 , 190), Vector2I(51 , 518), Hallway_Door_bedroom, WHITE, {192, 192, 192, 64}, 24)); //initial size - initial position
                buffer.push_back(ClickableObject(Vector2I(527 , 181 ), Vector2I(368  , 166 ), Hallway_Exit, WHITE, {192, 192, 192, 64}, 24));
                buffer.push_back(ClickableObject(Vector2I(1241  , 213 ), Vector2I(1034  , 97 ), Hallway_Door_Broken, WHITE, {192, 192, 192, 64}, 24));
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
            case Home_Door:
                return "Click To Interact With The Door";
            case Home_Sink:
                return "Click to interact with the Sink";
            case Home_Bed:
                return "Click To interact with the Bed";
            case Hallway_Exit:
                return "Click To Exit The House";
            case Hallway_Door_bedroom:
                return "Click To Enter The Bedroom";
        }
        return "";
    }

    void ObjectIDClicked(ObjectIDs id)
    {
        switch (id)
        {
            case ObjectIDs::Home_Bed:
                SetMessage("its just a bed");
                return;
            case ObjectIDs::Home_Sink:
                SetMessage("Its broken and leaking.");
                return;
            case ObjectIDs::Home_Door:
                DATA::Vars::currentlocation = Map::Hallway;
            case ObjectIDs::Hallway_Exit:
                return;
            case ObjectIDs::Hallway_Door_bedroom:
                DATA::Vars::currentlocation = Map::Home;
                return;
            case ObjectIDs::Hallway_Door_Broken:
                SetMessage("its stuck");
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
}