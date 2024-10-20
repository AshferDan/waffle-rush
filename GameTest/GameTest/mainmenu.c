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
#include "mainmenu.h"

CP_Font exo;

void Main_Menu_Init(void)
{
	//load font
	exo = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(exo);
}

void Main_Menu_Update(void)
{
	//assign window width and height
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();

	//track pointer
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();


	//background
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));


	//draw play button
	TextBoxCreate(width / 2, height / 3, 500, 150, "PLAY");
	int PlayClick = IsAreaClicked(width / 2, height / 3, 500, 150, mouseX, mouseY); //if mouse is over button
	if (PlayClick) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(width / 2, height / 3, 500, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit); //go to game
		}
	}

	//level 1 button
	TextBoxCreate(3*width / 4, height / 3, 150, 150, "1");
	int L1Click = IsAreaClicked(3 * width / 4, height / 3, 150, 150, mouseX, mouseY); //if mouse is over button
	if (L1Click) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(3 * width / 4, height / 3, 150, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_SetNextGameState(L1_Init, L1_Update, L1_Exit); //go to game
		}
	}

	//draw exit button
	TextBoxCreate(width / 2, 2 * height / 3, 500, 150, "EXIT");
	int ExitClick = IsAreaClicked(width / 2, 2 * height / 3, 500, 150, mouseX, mouseY); //if mouse is over button
	if (ExitClick) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(width / 2, 2 * height / 3, 500, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_Terminate(); //end game
		}
	}
}

void Main_Menu_Exit(void)
{

}
