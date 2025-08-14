whats wrong why is the formatting fucked

# PROJECT XTHUNT - CODE DOCS
developed by shadowdev @ doomgames.cc
contact : <a href="mailto:shadowdevreal@protonmail.com">main</a> || <a href="https://x.com/DoomGamescc">alternative</a>

compiling : 
- g++ , cmake

locations in source code:

UI structs : 
	Types.hpp
UI helpers :
	Renderer.hpp (namespace UI_elements)

SaveSystem :
	globalvars.cpp (namespace DATA)
	(SaveInventoryJson,LoadInventoryJson)
 <br>
 	Save , Load

Debugging : 
	%exefile% --debug
	(runs in debug mode src in main.cpp)

Rendering :
	Render.cpp
<br>
	notes when the games started yes a camera
	is defined but there is no real purpose for it
	except scaling up to screenres 
	<br>
	(DO NOT USE ANY CAMERA FUNCTIONS IF YOU DONT HAVE TO)
<br>
	notes : 
 		USE : 
		int GetInternalRenderWidth() { return GAME::target.texture.width; }
    	int GetInternalRenderHeight() { return GAME::target.texture.height; }	
		TO GET SCREENSIZES!!! 

(DO NOT FORGET) (UTILS.hpp)

USE Vector2I GetMousePositionPro()
to get scaled screensize 
(base hardcoded screensize is 1280x720)
(UTILS.hpp)
