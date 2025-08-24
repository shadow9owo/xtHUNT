# PROJECT XTHUNT - CODE DOCS

developed by shadowdev @ doomgames.cc <br>
contact : <a href="mailto:shadowdevreal@protonmail.com">main</a> || <a href="https://x.com/DoomGamescc">alternative</a>


compiling : 
- g++ , cmake

locations in source code:

UI structs : 
- Types.hpp

UI helpers :
- Renderer.hpp (namespace UI_elements)

SaveSystem :
- globalvars.cpp (namespace DATA)
- (SaveInventoryJson,LoadInventoryJson)
- Save , Load

Debugging : 
- %exefile% --debug <br>
- (runs in debug mode src in main.cpp)

Rendering :
- Render.cpp

notes when the games started yes a camera <br>
is defined but there is no real purpose for it

except scaling up to screenres 

(DO NOT USE ANY CAMERA FUNCTIONS IF YOU DONT HAVE TO)

notes :

USE :
- int GetInternalRenderWidth() { return GAME::target.texture.width; } <br>
- int GetInternalRenderHeight() { return GAME::target.texture.height; }	TO GET SCREENSIZES!!! 

(DO NOT FORGET) (UTILS.hpp) 


USE Vector2I GetMousePositionPro() <br>
to get scaled screensize <br>
(base hardcoded screensize is 1280x720) <br>
(UTILS.hpp)










