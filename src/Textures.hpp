#include <vector>
#include "raylib.h"
#include "Types.hpp"

namespace Textures
{
    extern std::vector<TextureStruct> textures;
    extern void Load();
    extern void Unload();
}