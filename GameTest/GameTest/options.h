//---------------------------------------------------------
// file:	options.h
// author:	AVID WAFFLE ENJOYERS
// email:	-
//
// brief:	Declarations of option page
//			
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include "mainmenu.h"
#include "utils.h"
#include "platform.h"

// BGM volume bar
float current_bgm_vol, max_bgm_vol, prev_bgm_vol;

// Sound effects volume bar
float current_se_vol, max_se_vol, prev_se_vol;

// icons for volume bars
float icon1_width, icon1_height, icon2_width, icon2_height;
float icon_bgm_x, icon_bgm_y, icon_se_x, icon_se_y;

void Options_Init(void);
void Options_Update(void);
void Options_Exit(void);

// menus when game is paused (pause, options, quit)
void PauseMenu();
void OptionsMenu();
void QuitMenu();

void SaveOptions(float current_bgm_vol, float current_se_vol);
void SaveOptionsInGame(float current_bgm_vol, float current_se_vol, float* prev_bgm_vol, float* prev_se_vol);