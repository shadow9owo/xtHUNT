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

        bool savefilecorruptionprevention = true;

        Game_Difficulty difficulty = D_Undefined;

        bool halt = false;
        
        Population population;
        Inventory plr_Inventory;
        Game_State gamestate;
        
        std::vector<Vector2I> placementbuffer;

        std::string Message;

        float UIfloattimer = 1;

        namespace Consts
        {
            int win[2] = {1280, 720};
        }
    }

    void SaveGameState(const Game_State& state) {
        std::ofstream file("./saves/gamestate.json");
        if (!file.is_open()) return;

        json j = state.toJson();
        file << j.dump();
        file.close();
    }

    void LoadGameState(Game_State& state) {
        std::ifstream file("./saves/gamestate.json");
        if (!file.is_open()) return;

        json j;
        try { file >> j; } 
        catch (const json::parse_error& e) { std::cerr << e.what() << '\n'; return; }
        file.close();

        state.fromJson(j);
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

        if (DG2D::INI::getvalue("savefilecorruptionprevention",tmpbuffer) == false)
        {
            DG2D::INI::setvalue("savefilecorruptionprevention", "true");
        }else {
            DG2D::INI::getvalue("savefilecorruptionprevention",tmpbuffer);

            if (tmpbuffer == "false")
            {
                Vars::savefilecorruptionprevention = false;
            }
            else
            {
                Vars::savefilecorruptionprevention = true;
            }
        }

        return 0;
    }

    void LoadGameData()
    {
        LoadGameState(Vars::gamestate);
        Vars::plr_Inventory = Vars::gamestate.playerInventory;
        Vars::gamestate.population = Vars::population;
        Vars::difficulty = Vars::gamestate.difficulty;
        Vars::currentlocation = Vars::gamestate.currentLocation;
        Vars::currentScene = Scene_MainMenu; //always start in menu
        return;
    }

    int Save()
    {
        Vars::gamestate.population = Vars::population;
        Vars::currentScene = Scene_MainMenu; //starts in menu so force it
        Vars::gamestate.difficulty = Vars::difficulty;
        Vars::gamestate.currentLocation = Vars::currentlocation;
        Vars::gamestate.playerInventory = Vars::plr_Inventory;
        SaveGameState(Vars::gamestate);

        DG2D::INI::setvalue("isfullscreen", Vars::isfullscreen ? "true" : "false");

        return 0;
    }
}
