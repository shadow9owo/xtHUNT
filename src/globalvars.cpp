#include "globalvars.hpp"
#include "ini.hpp"
#include "Types.hpp"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

namespace DATA
{
    namespace Vars
    {
        bool debug = false;
        bool running = true;
        bool isfullscreen = true;
        bool paused = false;
        Scenes currentScene = Scene_MainMenu;
        Map currentlocation = Map::Map_None;
        Inventory plr_Inventory;

        std::vector<Vector2I> placementbuffer;

        std::string Message;

        float UIfloattimer = 1;

        namespace Consts
        {
            int win[2] = {1280, 720};
        }
    }

    void LoadInventoryJson()
    {
        std::ifstream file("inventory.json");
        if (!file.is_open()) return;

        json j;
        try { file >> j; } 
        catch (const json::parse_error& e) { std::cerr << e.what(); return; }
        file.close();

        Vars::plr_Inventory.fromJson(j);
    }

    void SaveInventoryJson()
    {
        std::ofstream file("inventory.json");
        if (!file.is_open()) return;

        json j = Vars::plr_Inventory.toJson();
        file << j.dump();
        file.close();
    }


    int Load()
    {
        std::string tmpbuffer = "";

        if (DG2D::INI::getvalue("isfullscreen", tmpbuffer) == false)
        {
            DG2D::INI::setvalue("isfullscreen", "true");
        }
        else
        {
            Vars::isfullscreen = (tmpbuffer == "true");
        }

        if (DG2D::INI::getvalue("minwidth", tmpbuffer) == false)
        {
            DG2D::INI::setvalue("minwidth", "1280");
        }
        else
        {
            try
            {
                Vars::Consts::win[0] = std::stoi(tmpbuffer);
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        if (DG2D::INI::getvalue("minheight", tmpbuffer) == false)
        {
            DG2D::INI::setvalue("minheight", "720");
        }
        else
        {
            try
            {
                Vars::Consts::win[1] = std::stoi(tmpbuffer);
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        LoadInventoryJson();

        return 0;
    }

    int Save()
    {
        SaveInventoryJson();

        DG2D::INI::setvalue("isfullscreen", Vars::isfullscreen ? "true" : "false");

        return 0;
    }
}
