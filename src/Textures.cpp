#include <vector>
#include "raylib.h"
#include "Types.hpp"

namespace Textures
{
    std::vector<TextureStruct> textures;

    void Load()
    {
        textures.push_back(TextureStruct(CursorHover, LoadTexture("hover.png")));
        textures.push_back(TextureStruct(CursorGrab, LoadTexture("grab.png")));
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