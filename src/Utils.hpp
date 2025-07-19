#include "Types.hpp"
#include <vector>

namespace Utils
{
    extern Vector2I GetMousePositionPro();
    extern std::vector<ClickableObject> GetButtons(Map map);
    extern std::string ObjectIDToSTR(ObjectIDs id);
    extern void ObjectIDClicked(ObjectIDs id);
    
    extern void SetMessage(std::string message);
    extern void ClearMessage();

    extern Vector2I GetSizeFromPositions(const std::vector<Vector2I>& vec);

    extern void updatetimers();

    extern std::string getinfo();
}