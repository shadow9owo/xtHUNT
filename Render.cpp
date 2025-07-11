#include "raylib.h"

namespace Renderer
{
    Camera2D cam;

    void RenderWorld()
    {
        BeginMode2D(cam);
        
        EndMode2D();
        return;
    }

    void RenderUI()
    {
        return;
    }
}