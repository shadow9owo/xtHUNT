#include "Types.hpp"

namespace DATA
{
    namespace Vars
    {
        extern bool debug;
        extern bool running;
        extern bool isfullscreen;
        extern Scenes currentScene;

        namespace Consts
        {
            extern int win[2];
        }
    }

    extern int Load();
    extern int Save();
}