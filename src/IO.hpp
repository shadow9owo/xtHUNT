#include <string>
#include <sys/stat.h>

namespace IO
{
    extern bool FolderExists(const std::string& path);
    extern bool FileExists(const std::string& path);
    extern bool CreateFolder(const std::string& path);
}