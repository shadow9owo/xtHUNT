find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
# POSIX
find_library(DL_LIB dl)
find_library(RT_LIB rt)
find_library(M_LIB m)

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        master   # or a specific version
)

FetchContent_MakeAvailable(raylib)

# game libs

add_library(globalvars globalvars.cpp)
add_library(ini ini.cpp)
add_library(Input Input.cpp)
add_library(IO IO.cpp)
add_library(logger logger.cpp)
add_library(Npc Npc.cpp)
add_library(spreitesheet spritesheet.cpp)
add_library(Textures Textures.cpp)
add_library(tinyxml2 tinyxml2.cpp)
add_library(Utils Utils.cpp)

target_link_libraries(globalvars PRIVATE raylib)
target_link_libraries(ini PRIVATE raylib)
target_link_libraries(Input PRIVATE raylib)
target_link_libraries(IO PRIVATE raylib)
target_link_libraries(logger PRIVATE raylib)
target_link_libraries(Npc PRIVATE raylib)
target_link_libraries(spreitesheet PRIVATE raylib)
target_link_libraries(Textures PRIVATE raylib)
target_link_libraries(tinyxml2 PRIVATE raylib)
target_link_libraries(Utils PRIVATE raylib)

add_library(Render Render.cpp)
target_link_libraries(Render PRIVATE raylib globalvars ini Input IO logger Npc spreitesheet Textures tinyxml1 Utils)

add_executable(game main.cpp)

target_link_libraries(game PRIVATE
    raylib
    OpenGL::GL
    Threads::Threads
    globalvars ini Input IO logger Npc Render spreitesheet Textures tinyxml2 Utils
)

# Windows only

if(WIN32)
  target_link_libraries(game PRIVATE gdi32 winmm)
endif()

# Linux only

if(UNIX)
    find_library(WAYLAND_CLIENT_LIB wayland-client)
    find_library(WAYLAND_CURSOR_LIB wayland-cursor)
    find_library(WAYLAND_EGL_LIB wayland-egl)
    find_library(XKBCOMMON_LIB xkbcommon)

    if(WAYLAND_CLIENT_LIB AND WAYLAND_CURSOR_LIB AND WAYLAND_EGL_LIB AND XKBCOMMON_LIB)
        target_link_libraries(game PRIVATE
            ${WAYLAND_CLIENT_LIB}
            ${WAYLAND_CURSOR_LIB}
            ${WAYLAND_EGL_LIB}
            ${XKBCOMMON_LIB}
        )
    endif()
endif()

if(DL_LIB)
  target_link_libraries(game PRIVATE ${DL_LIB})
endif()
if(RT_LIB)
  target_link_libraries(game PRIVATE ${RT_LIB})
endif()
if(M_LIB)
  target_link_libraries(game PRIVATE ${M_LIB})
endif()

install(TARGETS game DESTINATION bin)
