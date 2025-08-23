#include "raylib.h"
#include "globalvars.hpp"
#include "logger.hpp"
#include "Types.hpp"
#include "Utils.hpp"
#include "Render.hpp"
#include <iostream>
#include "Npc.hpp"

namespace Npc
{

    DialogueTree currentDialogue = {};

    int RenderDialogue()
    {
        DrawRectangle(0,0, Utils::GetInternalRenderWidth(), Utils::GetInternalRenderHeight(), {0,0,0,192});

        if (currentDialogue.state == DialogueState_Finished || currentDialogue.texts.empty())
            return -1;

        if (currentDialogue.currentLine >= (int)currentDialogue.texts.size())
        {
            currentDialogue.state = DialogueState_Finished;
            return -1;
        }

        DialogueText& line = currentDialogue.texts[currentDialogue.currentLine];

        if (!line.options.empty())
            DATA::Vars::Message = line.options[0].text;
        else
            DATA::Vars::Message = "";

        Renderer::UI_Elements::RenderMessage();

        if (line.options.size() <= 1)
        {
            currentDialogue.currentLine++;
            return -1;
        }

        int clickedChoice = -1; //magic numbers fuck you too
        float startX = 50.0f;
        float startY = 400.0f;
        float buttonWidth = 400.0f;
        float buttonHeight = 40.0f;
        float padding = 10.0f;

        for (size_t i = 1; i < line.options.size(); i++)
        {
            Button btn = { 
                { (int)startX, (int)(startY + (i-1)*(buttonHeight+padding)) }, 
                { (int)buttonWidth, (int)buttonHeight }, 
                line.options[i].text, 
                BLACK, (Color){255,0,0,255}, 24
            };

            Renderer::UI_Elements::RenderButton(btn);

            if (Renderer::UI_Elements::IsButtonHovered(btn) && Renderer::UI_Elements::IsButtonClicked(btn))
                clickedChoice = (int)i;
        }

        if (clickedChoice > 0)
            DATA::Vars::Message = "";

        return clickedChoice;
    }


    int DialogueCallBack(DialogueID dialogueId, int playerChoice = -1)
    {
        if (playerChoice <= 0) return -1;

        DialogueText& line = currentDialogue.texts[currentDialogue.currentLine];
        DialogueOption& choice = line.options[playerChoice];

        LOGGER::LogINFO(choice.text);
        HandleDialogue(dialogueId, playerChoice);

        if (choice.nextIndex >= 0)
            currentDialogue.currentLine = choice.nextIndex;
        else
            currentDialogue.currentLine++;

        if (currentDialogue.currentLine >= (int)currentDialogue.texts.size())
            currentDialogue.state = DialogueState_Finished;

        return playerChoice;
    }


    
    void HandleDialogue(DialogueID dialogueId, int choice)
    {
        switch (dialogueId)
        {
            case DialogueID_Intro:
                if (choice == 1) 
                {
                    DATA::Vars::gamestate.difficulty = D_Normal;
                    DATA::Vars::difficulty = D_Normal;
                    currentDialogue.state = DialogueState_Finished;
                }
                else if (choice == 2) 
                {
                    DATA::Vars::gamestate.difficulty = D_Hard;
                    DATA::Vars::difficulty = D_Hard;
                    currentDialogue.state = DialogueState_Finished;
                }
                else if (choice == 3) 
                {
                    DATA::Vars::gamestate.difficulty = D_Impossible;
                    DATA::Vars::difficulty = D_Impossible;
                    currentDialogue.state = DialogueState_Finished;
                }
                break;
            default:
                LOGGER::LogERROR("Unknown dialogue in HandleDialogue()");
                break;
        }
    }

    void InitPopulation() // useless asf as the fucking savefile overwrites it if the user has a savefile :) i hate myself
    {   
        DATA::Vars::population.npcs = { // hardcoded makes me wanna die
            {Characters_None, true},
            {Characters_Undefined, true},
            {Characters_sekta_priest,true},
            {Characters_sekta_leader,true},
            {Characters_sekta_follower_0,true},
            {Characters_sekta_follower_1,true},
            {Characters_sekta_follower_2,true},
            {Characters_sekta_follower_3,true},
            {Characters_crack_dealer_0,true},
            {Characters_crack_dealer_1,true},
            {Characters_crackhead_0,true},
            {Characters_crackhead_1,true},
            {Characters_crackhead_2,true},
            {Characters_crackhead_3,true},
            {Characters_storeclerk_0,true},
            {Characters_storeclerk_1,true},
            {Characters_storeclerk_2,true},
            {Characters_storeclerk_3,true},
            {Characters_job_boss,true},
            {Characters_female_0,true},
            {Characters_female_1,true},
            {Characters_female_2,true},
            {Characters_female_3,true},
            {Characters_male_0,true},
            {Characters_male_1,true},
            {Characters_male_2,true},
            {Characters_male_3,true}
        };
        return;
    }

    int InitDialogue(const DialogueTree& tree)
    {
        if (currentDialogue.state != DialogueState_Finished)
            return -1;

        currentDialogue = tree;
        currentDialogue.state = DialogueState_Talking;
        currentDialogue.currentLine = 0;
        return 0;
    }
}