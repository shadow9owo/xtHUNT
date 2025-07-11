#include "globalvars.hpp"
#include "ini.hpp"

namespace DATA
{
    namespace Vars
    {
        bool running = true;
        bool isfullscreen = true;

        namespace Consts //could make a vector2i struct but i am lazy atm
        {
            int win[2] = {1280,720}; //width, height
        }
    }

    int Load()
    {
        std::string tmpbuffer = ""; //wipes it
        if (DG2D::INI::getvalue("isfullscreen",tmpbuffer) == false) // i know its ass but easy to mod :D
        {
            DG2D::INI::setvalue("isfullscreen", "true");
        }
        else
        {
            Vars::isfullscreen = (tmpbuffer == "true");
        }
        return 0;
    }

    int Save()
    {
        return 0;
    }
}