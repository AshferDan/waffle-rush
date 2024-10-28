//---------------------------------------------------------
// file:	game.c
// author:	AVID WAFFLE ENJOYERS
// email:	-
//
// brief:   Tutorial stage
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "game.h"

CP_Color bg, red, green, hpcol; //colors
float speed; //speed
float width, height; //window width/height
float hpx1, hpx2, hpy1, hpy2; //positions of hp bar
CP_Font text;
CP_Image player_sprite;

hazard traps[100];

void Game_Init(void)
{
	// load font
	text = CP_Font_Load("Assets/Exo2-Regular.ttf");

	// load player sprite
	player_sprite = CP_Image_Load("Assets/Waffle_Player.png");

	// get window size
	width = CP_System_GetWindowWidth();
	height = CP_System_GetWindowHeight();

	// initialize colors
	bg = CP_Color_Create(100, 100, 100, 255); //background
	red = CP_Color_Create(200, 50, 50, 255); //red
	green = CP_Color_Create(50, 200, 50, 255); //green
	hpcol = CP_Color_Create(255, 150, 150, 255); //hp colour

	// initialize base speed
	speed = 600;

	// initialize movestate
	movestate = OnPlat;

	// initialize player
	// size
	player.width = 20;
	player.height = 20;
	// position
	player.x = 700;
	player.y = 200;
	// movement
	player.movex = 0;
	player.movey = 0;
	// transit variables
	player.transition_time = 1.0f;
	// health
	player.stamina = 100.0f;
	// color
	player.color = CP_Color_Create(150, 150, 200, 255);

	// PLATFORMS INITIALIZATION
	/*---------------------------------------------------------------------------------------------------*/
#pragma region Initialize Platform

	FILE* file = fopen("Assets/Base.txt", "r");

	if (file == NULL) {
		printf("Failed to open platform file! Check if file exists\n");
		CP_Engine_Terminate;
	}
	// read how many platforms in level
	fscanf_s(file, "%d", &numplats);

	// pindex - platform index
	// pcindex - platform coordinate index
	int pindex = 0; int pcindex = 0;
	while (pindex < numplats) {
		// coordinate ints to read
		// scan how many coordinates
		fscanf_s(file, "%d", &Platform[pindex].numcoords);
		// for how many coordinates in platform
		while (pcindex < Platform[pindex].numcoords) {
			int x, y;
			// scan coordinates
			fscanf_s(file, "%d %d", &x, &y);
			// assign coordinates to array
			platform_coordinates(pindex, pcindex, x, y);
			pcindex++;
		}
		pcindex = 0;
		fscanf_s(file, "%d", &Platform[pindex].numblocks);
		while (pcindex < Platform[pindex].numblocks) {
			int x1, y1, x2, y2;
			fscanf_s(file, "%d %d %d %d", &x1, &y1, &x2, &y2);
			platform_onblocks(pindex, pcindex, x1, y1, x2, y2);
			pcindex++;
		}
		pcindex = 0;
		pindex++;
	}
	fclose(file);

	// initialize all platform hitboxes
	for (int plat_index = 0; plat_index < numplats; plat_index++) {
		hitbox(plat_index, Platform[plat_index].numcoords, &Platform[plat_index]);
	}

#pragma endregion

	//HAZARDS
	/*-----------------------------------------------------------------------------------------------------------*/
#pragma region Hazard
	FILE* file1 = fopen("Assets/testhazard.txt", "r");
	int numberoftraps;
	fscanf_s(file1, "%d", &numberoftraps);

	for (int i = 0; i < numberoftraps; ++i) {
		for (int j = 0; j < 3; ++j) {
			fscanf_s(file1, "%d %d", &traps[i].x[j], &traps[i].y[j]);
		}
		fscanf_s(file1, "%d", &traps[i].type);
	}

	fclose(file1);
#pragma endregion
	// Corner drawing
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_ImageMode(CP_POSITION_CORNER);
}

void Game_Update(void)
{
	// background
	CP_Graphics_ClearBackground(bg);
	// getdt
	float dt = CP_System_GetDt();

	// MOVEMENT 
	/*---------------------------------------------------------------------------------------------------*/
#pragma region Movement
	// change movestate
	// OnPlat - on platform
	// InPlat - inside platform
	// EnterPlat - from OnPlat to InPlat
	// ExitPlat - from InPlat to OnPlat
	if (CP_Input_KeyTriggered(KEY_E) && (movestate == OnPlat || movestate == InPlat)) {
		movestate = start_transition(&player, movestate);
	}
	// Transiting movestate
	movestate = transition(&player, movestate, dt);

	// movement logics
	movement(&player, movestate, speed, dt);

	// reset checks for jumping and entering
	player.onplatform = 0;
	player.withinx = 0;
	player.leaveplatform = 0;
	// collision against platforms
	if (movestate == OnPlat) {
		player.stamina += 20.0f * dt;
		for (int plat_index = 0; plat_index < numplats; plat_index++) {
			CollOnPlatforms(plat_index,Platform[plat_index], &player, player);
		}
	}

	else if (movestate == InPlat) {
		player.stamina -= 20.0f * dt;
		for (int plat_index = 0; plat_index < numplats; plat_index++) {
			CollPlatforms(plat_index, Platform[plat_index], &player, player);
		}
	}
	player.stamina = CP_Math_ClampFloat(player.stamina, 0, 100);
	printf("%f\n", player.stamina);
	// window clamps
	player.x = CP_Math_ClampFloat(player.x, 0, width - player.width);
	if (player.y + player.height > height || player.y<0) {
		player.movey = 0;
	}
	player.y = CP_Math_ClampFloat(player.y, 0, height - player.height);

	// reset with R or touch ground while movestate OnPlat
	if (CP_Input_KeyDown(KEY_R) || ((player.y >= height - player.height) && movestate == OnPlat)) {
		player.x = 150;
		player.y = 200;
		movestate = OnPlat;
		player.movey = 0;
	}
#pragma endregion

	// RENDER
	/*---------------------------------------------------------------------------------------------------*/
#pragma region RENDER

	// Platforms
	CP_Settings_Fill(hpcol);
	for (int i = 0; i < numplats; i++) {
		DrawPlatform(i);
	}

	/*for (int i = 0; i < numplats; i++) {
		for (int j = 0; j < Platform[i].numblocks; j++) {
			CP_Graphics_DrawRect(Platform[i].onblocks[j].x1, Platform[i].onblocks[j].y1, Platform[i].onblocks[j].w, Platform[i].onblocks[j].h);
		}
	}*/


	// HAZARD DRAWING
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawTriangle(traps[0].x[0], traps[0].y[0], traps[0].x[1], traps[0].y[1], traps[0].x[2], traps[0].y[2]);

	// Player
	// CP_Settings_Fill(player.color);
	// CP_Graphics_DrawRect(player.x - 10, player.y - 10, player.width + 20, player.height + 20);
	CP_Image_Draw(player_sprite, player.x -15, player.y -15, player.width + 30, player.height + 30, 255);

#pragma endregion

	// Back to main menu
	if (CP_Input_KeyDown(KEY_Q)) { CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); };

}

void Game_Exit(void)
{
	CP_Image_Free(player_sprite);

}