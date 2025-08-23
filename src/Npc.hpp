#include "raylib.h"
#include "globalvars.hpp"
#include "logger.hpp"
#include "Types.hpp"
#include "Utils.hpp"
#include "Render.hpp"
#include <iostream>

namespace Npc
{
    extern DialogueTree currentDialogue;

    extern int DialogueCallBack(DialogueID dialogueId,int playerChoice);

    extern void HandleDialogue(DialogueID Dialogue,int choice);

    extern void InitPopulation();

    extern int InitDialogue(const DialogueTree& tree);

    extern int RenderDialogue();
}