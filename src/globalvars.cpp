#include "globalvars.hpp"
#include "ini.hpp"
#include "Types.hpp"
#include "json/json.h"
#include <fstream>

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

        Json::CharReaderBuilder reader;
        Json::Value root;
        std::string errors;

        bool parsing = Json::parseFromStream(reader, file, &root, &errors);
        file.close();

        if (!parsing) {
            return;
        }

        Vars::Inventory.clear();

        const Json::Value items = root["Items"];
        for (Json::Value::ArrayIndex i = 0; i < items.size(); ++i)
        {
            int ii = items[i].asInt();
            Items e = static_cast<Items>(ii);
            Vars::Inventory.push_back(e);
        }
    }

    void SaveInventoryJson()
    {
        std::ofstream file("inventory.json");
        if (!file.is_open()) {
            return;
        }

        Json::Value root;
        Json::Value items(Json::arrayValue);

        for (size_t i = 0; i < Vars::Inventory.size(); ++i)
        {
            int ii = static_cast<int>(Vars::Inventory[i]);
            items.append(ii);
        }

        root["Items"] = items;

        Json::StreamWriterBuilder builder;
        builder["indentation"] = "  ";

        Json::StreamWriter* writer = builder.newStreamWriter();
        writer->write(root, &file);

        delete writer;

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
