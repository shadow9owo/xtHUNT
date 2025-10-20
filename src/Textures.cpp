#include <vector>
#include "raylib.h"
#include "Types.hpp"

namespace Textures
{
    std::vector<TextureStruct> textures;

    void Load()
    {
        textures.push_back(TextureStruct(TextureEnum_None, LoadTexture("./graphics/missing.tga")));
        textures.push_back(TextureStruct(CursorHover, LoadTexture("./graphics/hover.tga")));
        textures.push_back(TextureStruct(CursorGrab, LoadTexture("./graphics/grab.tga")));
        textures.push_back(TextureStruct(texture_Home, LoadTexture("./graphics/home.tga")));
        textures.push_back(TextureStruct(texture_hallway, LoadTexture("./graphics/hallway.tga")));
        textures.push_back(TextureStruct(Texture_outside_home, LoadTexture("./graphics/outside.tga")));
        textures.push_back(TextureStruct(Eye, LoadTexture("./graphics/eye.tga")));
        textures.push_back(TextureStruct(Eye2, LoadTexture("./graphics/eye2.tga")));
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