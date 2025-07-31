#include <vector>
#include "raylib.h"
#include "Types.hpp"

namespace Textures
{
    std::vector<TextureStruct> textures;

    void Load()
    {
        textures.push_back(TextureStruct(TextureEnum_None, LoadTexture("./graphics/missing.jpg")));
        textures.push_back(TextureStruct(CursorHover, LoadTexture("./graphics/hover.png")));
        textures.push_back(TextureStruct(CursorGrab, LoadTexture("./graphics/grab.png")));
        textures.push_back(TextureStruct(texture_Home, LoadTexture("./graphics/home.bmp")));
        textures.push_back(TextureStruct(texture_hallway, LoadTexture("./graphics/hallway.png")));
        textures.push_back(TextureStruct(Texture_outside_home, LoadTexture("./graphics/outside.png")));
        textures.push_back(TextureStruct(Eye, LoadTexture("./graphics/eye.bmp")));
        textures.push_back(TextureStruct(Eye2, LoadTexture("./graphics/eye2.bmp")));
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