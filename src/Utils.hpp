#include "Types.hpp"
#include <vector>

namespace Utils
{
    extern Vector2I GetMousePositionPro();
    extern std::vector<ClickableObject> GetButtons(Map map);
    extern std::string ObjectIDToSTR(ObjectIDs id);
}