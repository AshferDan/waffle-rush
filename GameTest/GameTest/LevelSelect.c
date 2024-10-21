//---------------------------------------------------------
// file:	mainmenu.c
// author:	TAN JUN QUAN
// email:	t.junquan@digipen.edu
//
// brief:	Main menu stage with a play button and an exit
//          button
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "LevelSelect.h"

CP_Font exo;

void LSelect_Init(void)
{
	//load font
	exo = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(exo);

	// level struct (to implement later)

	//levels[0].level_no = 1;
	//levels[1].level_no = 2;
	//levels[2].level_no = 3;
	//levels[3].level_no = 4;
	//levels[4].level_no = 5;

	//levels[0].isUnlocked = 1;
	//levels[1].isUnlocked = 1;
	//levels[2].isUnlocked = 1;
	//levels[3].isUnlocked = 0;
	//levels[4].isUnlocked = 0;

	//levels[0].isCleared = 1;
	//levels[1].isCleared = 1;
	//levels[2].isCleared = 0;
	//levels[3].isCleared = 0;
	//levels[4].isCleared = 0;
}

void LSelect_Update(void)
{
	//assign window width and height
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();

	//track pointer
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	//background
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	//header text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("LEVEL SELECT", CP_System_GetWindowWidth() / 2, 100);

	//level 1 button
	TextBoxCreate(width / 4, height / 3, 150, 150, "1");
	int L1Click = IsAreaClicked(width / 4, height / 3, 150, 150, mouseX, mouseY); //if mouse is over button
	if (L1Click) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(width / 4, height / 3, 150, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_SetNextGameState(L1_Init, L1_Update, L1_Exit); //go to game
		}
	}

	//level 2 button
	TextBoxCreate(width / 4 + 200, height / 3, 150, 150, "2");
	int L2Click = IsAreaClicked(width / 4 + 200, height / 3, 150, 150, mouseX, mouseY); //if mouse is over button
	if (L2Click) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(width / 4 + 200, height / 3, 150, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_SetNextGameState(L1_Init, L1_Update, L1_Exit); //go to game
		}
	}

	//level 3 button
	TextBoxCreate(width / 2, height / 3, 150, 150, "3");
	int L3Click = IsAreaClicked(width / 2, height / 3, 150, 150, mouseX, mouseY); //if mouse is over button
	if (L3Click) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(width / 2, height / 3, 150, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_SetNextGameState(L1_Init, L1_Update, L1_Exit); //go to game
		}
	}

	//level 4 button
	TextBoxCreate(width / 2 + 200, height / 3, 150, 150, "4");
	int L4Click = IsAreaClicked(width / 2 + 200, height / 3, 150, 150, mouseX, mouseY); //if mouse is over button
	if (L4Click) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(width / 2 + 200, height / 3, 150, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_SetNextGameState(L1_Init, L1_Update, L1_Exit); //go to game
		}
	}

	//level 5 button
	TextBoxCreate(3 * width / 4, height / 3, 150, 150, "5");
	int L5Click = IsAreaClicked(3 * width / 4, height / 3, 150, 150, mouseX, mouseY); //if mouse is over button
	if (L5Click) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(3 * width / 4, height / 3, 150, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_SetNextGameState(L1_Init, L1_Update, L1_Exit); //go to game
		}
	}

	//back to main menu button
	TextBoxCreate(width / 2, 2 * height / 3, 500, 150, "BACK");
	int ExitClick = IsAreaClicked(width / 2, 2 * height / 3, 500, 150, mouseX, mouseY); //if mouse is over button
	if (ExitClick) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(width / 2, 2 * height / 3, 500, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); //return to main menu
		}
	}
}

void LSelect_Exit(void)
{

}