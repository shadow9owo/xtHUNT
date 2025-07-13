#include "Types.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include "globalvars.hpp"
#include "main.hpp"
#include "logger.hpp"

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
                buffer.push_back(ClickableObject(Vector2I(105 , 436), Vector2I(467 , 191), Bed, WHITE, {192, 192, 192, 64}, 24)); //initial size - initial position
                buffer.push_back(ClickableObject(Vector2I(663 , 256 ), Vector2I(159  , 347 ), Door, WHITE, {192, 192, 192, 64}, 24));
                buffer.push_back(ClickableObject(Vector2I(1034  , 414 ), Vector2I(207  , 116 ), Sink, WHITE, {192, 192, 192, 64}, 24));
                return buffer;
            case Map::None:
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
            case Door:
                return "Click To Interact With The Door";
            case Sink:
                return "Click to interact with the Sink";
            case Bed:
                return "Click To interact with the Bed";
        }
        return "";
    }
}