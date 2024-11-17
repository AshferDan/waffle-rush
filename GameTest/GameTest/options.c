//---------------------------------------------------------
// file:	options.c
// author:	AVID WAFFLE ENJOYERS
// email:	-
//
// brief:	Options menu
//			
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "options.h"

CP_Font exo;

// BGM volume bar
float current_bgm_vol, max_bgm_vol;

// Sound effects volume bar
float current_se_vol, max_se_vol;

// icons for volume bars
float icon1_width, icon1_height, icon2_width, icon2_height;
float icon_bgm_x, icon_bgm_y, icon_se_x, icon_se_y;

void Options_Init(void) {

	//load font
	exo = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(exo);

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	// load options file

	FILE* file = fopen("Assets/Options.txt", "r");
	fscanf_s(file, "%f %f", &current_bgm_vol, &current_se_vol);
	printf("BGM Volume: %lf\nSE Volume: %lf\n", current_bgm_vol, current_se_vol);
	printf("---------------------------------------------------------------\n");
	fclose(file);

	// set max volumes for BGM and sound effects
	max_bgm_vol = 100.0f;
	max_se_vol = 100.0f;

	// set size for icons
	icon1_width = 10.0f;
	icon1_height = 10.0f;
	icon2_width = 20.0f;
	icon2_height = 70.0f;

	// set position for icons
	icon_bgm_x = CP_System_GetWindowWidth() / 2;
	icon_bgm_y = CP_System_GetWindowHeight() / 3;
	icon_se_x = CP_System_GetWindowWidth() / 2;
	icon_se_y = CP_System_GetWindowHeight() / 2;
}

void Options_Update(void) {
	//assign window width and height
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();

	//track pointer
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	// back button color
	CP_Color button_color = CP_Color_Create(200, 60, 60, 255);

	//background
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	//header text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(100);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("OPTIONS", width / 2, 100);

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(70);
	CP_Font_DrawText("BGM Volume", width / 16, height / 3);
	CP_Font_DrawText("Sound Volume", width / 16, height / 2);

	// update BGM volume
	if (current_bgm_vol > max_bgm_vol) {
		current_bgm_vol = max_bgm_vol;
	}
	else if (current_bgm_vol < 0) {
		current_bgm_vol = 0.0f;
	}
	
	// lower BGM volume button
	TextBoxCreate(icon_bgm_x - 100, icon_bgm_y, 50, 50, "-", button_color);
	int LowerBGMClick = IsAreaClicked(icon_bgm_x - 100, icon_bgm_y, 50, 50, mouseX, mouseY); //if mouse is over button
	if (LowerBGMClick) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(icon_bgm_x - 100, icon_bgm_y, 50, 50);
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) { //if LMB1 pressed
			current_bgm_vol -= 1;
		}
	}

	// raise BGM volume button
	TextBoxCreate(width - 150, icon_bgm_y, 50, 50, "+", button_color);
	int RaiseBGMClick = IsAreaClicked(width - 150, icon_bgm_y, 50, 50, mouseX, mouseY); //if mouse is over button
	if (RaiseBGMClick) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(width - 150, icon_bgm_y, 50, 50);
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) { //if LMB1 pressed
			current_bgm_vol += 1;
		}
	}

	// update BGM volume bar
	if (current_bgm_vol > 0) {
		for (float i = 0.0f; i < max_bgm_vol; i += 5.0f) {
			CP_Settings_Fill(button_color);
			if (i < current_bgm_vol) {
				CP_Graphics_DrawRect(icon_bgm_x + 30.0f * (i / 5.0f), icon_bgm_y, icon2_width, icon2_height);
			}
			else {
				CP_Graphics_DrawRect(icon_bgm_x + 30.0f * (i / 5.0f), icon_bgm_y, icon1_width, icon1_height);
			}
		}
	}
	else {
		for (float i = 0.0f; i < max_bgm_vol; i += 5.0f) {
			CP_Settings_Fill(button_color);
			CP_Graphics_DrawRect(icon_bgm_x + 30.0f * (i / 5.0f), icon_bgm_y, icon1_width, icon1_height);
		}
	}

	// update SE volume
	if (current_se_vol > max_se_vol) {
		current_se_vol = max_se_vol;
	}
	else if (current_se_vol < 0) {
		current_se_vol = 0.0f;
	}

	// lower SE volume button
	TextBoxCreate(icon_se_x - 100, icon_se_y, 50, 50, "-", button_color);
	int LowerSEClick = IsAreaClicked(icon_se_x - 100, icon_se_y, 50, 50, mouseX, mouseY); //if mouse is over button
	if (LowerSEClick) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(icon_se_x - 100, icon_se_y, 50, 50);
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) { //if LMB1 pressed
			current_se_vol -= 1;
		}
	}

	// raise SE volume button
	TextBoxCreate(width - 150, icon_se_y, 50, 50, "+", button_color);
	int RaiseSEClick = IsAreaClicked(width - 150, icon_se_y, 50, 50, mouseX, mouseY); //if mouse is over button
	if (RaiseSEClick) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(width - 150, icon_se_y, 50, 50);
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) { //if LMB1 pressed
			current_se_vol += 1;
		}
	}

	// update SE volume bar
	if (current_se_vol > 0) {
		for (float i = 0.0f; i < max_se_vol; i += 5.0f) {
			CP_Settings_Fill(button_color);
			if (i < current_se_vol) {
				CP_Graphics_DrawRect(icon_se_x + 30.0f * (i / 5.0f), icon_se_y, icon2_width, icon2_height);
			}
			else {
				CP_Graphics_DrawRect(icon_se_x + 30.0f * (i / 5.0f), icon_se_y, icon1_width, icon1_height);
			}
		}
	}
	else {
		for (float i = 0.0f; i < max_se_vol; i += 5.0f) {
			CP_Settings_Fill(button_color);
			CP_Graphics_DrawRect(icon_se_x + 30.0f * (i / 5.0f), icon_se_y, icon1_width, icon1_height);
		}
	}

	//save changes button
	TextBoxCreate(3 * width / 8, height - 100, 300, 150, "SAVE", button_color);
	int SaveClick = IsAreaClicked(3 * width / 8, height - 100, 300, 150, mouseX, mouseY); //if mouse is over button
	if (SaveClick) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(3 * width / 8, height - 100, 300, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			FILE* OptionsFile = fopen("Assets/Options.txt", "w");
			fprintf_s(OptionsFile, "%lf %lf", current_bgm_vol, current_se_vol);
			printf("Changes saved successfully!\nBGM Volume: %lf\nSE Volume: %lf\n", current_bgm_vol, current_se_vol);
			fclose(OptionsFile);
		}
	}

	//discard changes and return to main menu button
	TextBoxCreate(5 * width / 8, height - 100, 300, 150, "BACK", button_color);
	int ExitClick = IsAreaClicked(5 * width / 8, height - 100, 300, 150, mouseX, mouseY); //if mouse is over button
	if (ExitClick) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); //highlight button
		CP_Graphics_DrawRect(5 * width / 8, height - 100, 300, 150);
		if (CP_Input_MouseClicked()) { //if LMB1 pressed
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); //return to main menu
		}
	}

	// Back to main menu
	if (CP_Input_KeyDown(KEY_Q)) { CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); };
}

void Options_Exit(void) {

}