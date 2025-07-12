#include <string>
#include "globalvars.hpp"
#include <iostream>
#include "logger.hpp"

namespace LOGGER
{
    void Log(const std::string &message)
    {
        if (DATA::Vars::debug)
        {
            std::cout << "[DEBUG] " << message << std::endl;
        }else {
            return; // --debug not set 
        }
    }
}