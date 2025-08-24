#include "Types.hpp"
#include <vector>

namespace DATA
{
    namespace Vars
    {
        extern bool debug;
        extern bool running;
        extern bool paused;
        extern bool isfullscreen;
        extern Scenes currentScene;
        extern Map currentlocation;
        extern Inventory plr_Inventory;

        extern Game_Difficulty difficulty;

        extern bool savefilecorruptionprevention;

        extern Population population;
        extern Game_State gamestate;

        extern std::vector<Vector2I> placementbuffer;

        extern std::string Message;

        extern float UIfloattimer;

        extern bool halt;

        namespace Consts
        {
            extern int win[2];
        }
    }

    extern void LoadGameData();
    extern int Load();
    extern int Save();
}