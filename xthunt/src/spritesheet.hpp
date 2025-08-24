#include <raylib.h>
#include "Types.hpp"

namespace spritesheet
{
    extern Vector4 GetSpritePosFromSpritesheet(Sprites sprite);
    extern bool DrawSpriteFromPos(Vector4 xywh,Vector2 dest,Color color = WHITE);
}