#include "globalvars.hpp"
#include "ini.hpp"
#include "Types.hpp"
#include "tinyxml2.h"

namespace DATA
{
    namespace Vars
    {
        bool debug = false;
        bool running = true;
        bool isfullscreen = true;
        Scenes currentScene = MainMenu;
        Map currentlocation = Map::Map_None;
        std::vector<Items> Inventory;

        std::vector<Vector2I> placementbuffer;

        std::string Message;

        namespace Consts
        {
            int win[2] = {1280, 720}; // width, height
        }
    }

    void LoadInventoryFromXML()
    {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile("inventory.xml") != tinyxml2::XML_SUCCESS)
        {
            std::cerr << "Failed to load inventory.xml\n";
            return;
        }

        Vars::Inventory.clear();

        tinyxml2::XMLElement* root = doc.FirstChildElement("Inventory");
        if (!root) return;

        for (tinyxml2::XMLElement* itemElement = root->FirstChildElement("Item");
             itemElement != nullptr;
             itemElement = itemElement->NextSiblingElement("Item"))
        {
            const char* text = itemElement->GetText();
            if (text)
            {
                try
                {
                    int val = std::stoi(text);
                    Vars::Inventory.push_back(static_cast<Items>(val));
                }
                catch(const std::exception& e)
                {

                }
            }
        }
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

        LoadInventoryFromXML();

        return 0;
    }

    int Save()
    {
        tinyxml2::XMLDocument doc;

        tinyxml2::XMLElement* root = doc.NewElement("Inventory");
        doc.InsertFirstChild(root);

        for (Items item : Vars::Inventory)
        {
            tinyxml2::XMLElement* itemElement = doc.NewElement("Item");
            itemElement->SetText(std::to_string(static_cast<int>(item)).c_str());
            root->InsertEndChild(itemElement);
        }

        doc.SaveFile("inventory.xml");

        DG2D::INI::setvalue("isfullscreen", Vars::isfullscreen ? "true" : "false");

        return 0;
    }
}
