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
        if (DG2D::INI::getvalue("minwidth",tmpbuffer) == false)
        {
            DG2D::INI::setvalue("minwidth", "1280");
        }
        else
        {
            try
            {
                Vars::Consts::win[0] = std::stoi(tmpbuffer);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        if (DG2D::INI::getvalue("minheight",tmpbuffer) == false)
        {
            DG2D::INI::setvalue("minheight", "720");            
        }
        else
        {
            try
            {           
                Vars::Consts::win[1] = std::stoi(tmpbuffer);   
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        return 0;
    }

    int Save()
    {
        DG2D::INI::setvalue("isfullscreen", Vars::isfullscreen ? "true" : "false");
        return 0;
    }
}