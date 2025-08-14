# PROJECT XTHUNT - CODE DOCS

developed by shadowdev @ doomgames.cc
contact : <a href="mailto:shadowdevreal@protonmail.com">main</a> || <a href="https://x.com/DoomGamescc">alternative</a>
<br>
compiling : 
- g++ , cmake
<br>
locations in source code:
<br>
UI structs : 
- Types.hpp
<br>
UI helpers :
- Renderer.hpp (namespace UI_elements)
<br>
SaveSystem :
- globalvars.cpp (namespace DATA)
- (SaveInventoryJson,LoadInventoryJson)
<br>
- Save , Load
<br>
Debugging : 
<br>
- %exefile% --debug
<br>
- (runs in debug mode src in main.cpp)
<br>
Rendering :
- Render.cpp
<br>
notes when the games started yes a camera
<br>
is defined but there is no real purpose for it
<br>
except scaling up to screenres 
<br>
(DO NOT USE ANY CAMERA FUNCTIONS IF YOU DONT HAVE TO)
<br>
notes :
<br>
USE :
- int GetInternalRenderWidth() { return GAME::target.texture.width; }
<br>
- int GetInternalRenderHeight() { return GAME::target.texture.height; }	TO GET SCREENSIZES!!! 
<br>
(DO NOT FORGET) (UTILS.hpp)
<br>
USE Vector2I GetMousePositionPro()
<br>
to get scaled screensize 
<br>
(base hardcoded screensize is 1280x720)
<br>
(UTILS.hpp)






