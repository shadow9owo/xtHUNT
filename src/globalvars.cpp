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
        Scenes currentScene = Scene_MainMenu;
        Map currentlocation = Map::Map_None;
        std::vector<Items> Inventory;

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
        if (!file.is_open()) {
            return;
        }

        json root;
        try
        {
            file >> root;
        }
        catch (const json::parse_error& e)
        {
            std::cerr << "JSON parse error: " << e.what() << "\n";
            return;
        }
        file.close();

        Vars::Inventory.clear();

        if (root.contains("Items") && root["Items"].is_array())
        {
            for (const auto& item : root["Items"])
            {
                if (item.is_number_integer())
                {
                    Items e = static_cast<Items>(item.get<int>());
                    Vars::Inventory.push_back(e);
                }
            }
        }
    }

    void SaveInventoryJson()
    {
        json root;
        root["Items"] = json::array();

        for (const auto& item : Vars::Inventory)
        {
            root["Items"].push_back(static_cast<int>(item));
        }

        std::ofstream file("inventory.json");
        if (!file.is_open()) {
            return;
        }

        file << root.dump(2);
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
