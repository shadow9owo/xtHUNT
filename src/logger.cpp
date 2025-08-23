#include <string>
#include "globalvars.hpp"
#include <iostream>
#include "logger.hpp"
#include <vector>

namespace LOGGER
{
    std::vector<std::string> logs;

    void logClamp()
    {
        if (logs.size() + 1 > 10)
        {
            logs.erase(logs.begin());
        }
    }

    void LogDEBUG(const std::string &message)
    {
        if (DATA::Vars::debug)
        {
            logClamp();
            logs.push_back("[DEBUG] " + message);
        }else {
            return; 
        }
    }

    void LogINFO(const std::string &message)
    {
        logClamp();
        logs.push_back("[INFO] " + message);
    }

    void LogERROR(const std::string &message)
    {
        logClamp();
        logs.push_back("[ERROR] " + message);
    }

    void RenderLogs()
    {
        for (size_t i = 0; i < logs.size(); i++)
        {
            int a = i;
            if (a == 0)
            {
                a = 1;
            }
            DrawText(logs.at(i).c_str(), 0, 0 + (20 * i), 12, {255,255,255,(unsigned char)(255/a)});
        }
        return;
    }
}