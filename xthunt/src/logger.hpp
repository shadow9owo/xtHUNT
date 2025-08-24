#include <string>
#include "globalvars.hpp"
#include <iostream>
#include <vector>

namespace LOGGER
{
    extern void logClamp();
    extern void LogDEBUG(const std::string &message);
    extern void LogINFO(const std::string &message);
    extern void LogERROR(const std::string &message);
    extern void RenderLogs();
}