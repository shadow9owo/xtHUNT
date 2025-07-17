#include <vector>
#include "raylib.h"
#include "Types.hpp"

namespace Textures
{
    std::vector<TextureStruct> textures;

    void Load()
    {
        textures.push_back(TextureStruct(CursorHover, LoadTexture("./graphics/hover.png")));
        textures.push_back(TextureStruct(CursorGrab, LoadTexture("./graphics/grab.png")));
        textures.push_back(TextureStruct(texture_Home, LoadTexture("./graphics/home.bmp")));
        textures.push_back(TextureStruct(texture_Home, LoadTexture("./graphics/hallway.png")));
    }
    void Unload()
    {
        for (auto &texture : textures)
        {
            UnloadTexture(texture.TextureData);
        }
        textures.clear();
    }
}