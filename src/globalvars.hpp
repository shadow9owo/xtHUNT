#include "Types.hpp"
#include <vector>
namespace DATA
{
    namespace Vars
    {
        extern bool debug;
        extern bool running;
        extern bool isfullscreen;
        extern Scenes currentScene;
        extern Map currentlocation;
        extern std::vector<Items> Inventory;

        extern std::vector<Vector2I> placementbuffer;

        extern std::string Message;

        extern float UIfloattimer;

        namespace Consts
        {
            extern int win[2];
        }
    }

    extern int Load();
    extern int Save();
}