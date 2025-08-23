#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#ifdef _WIN32
#include <direct.h>
#endif

#include "IO.hpp"

namespace IO
{
    bool FolderExists(const std::string& path)
    {
        struct stat info;
        if (stat(path.c_str(), &info) != 0)
            return false;
        return (info.st_mode & S_IFDIR) != 0;
    }

    bool FileExists(const std::string& path)
    {
        struct stat info;
        if (stat(path.c_str(), &info) != 0)
            return false;
        return (info.st_mode & S_IFREG) != 0; 
    }

    bool CreateFolder(const std::string& path)
    {
        if (FolderExists(path))
            return true;

    #ifdef _WIN32
        return _mkdir(path.c_str()) == 0;
    #else
        return mkdir(path.c_str(), 0755) == 0;
    #endif
    }
}
