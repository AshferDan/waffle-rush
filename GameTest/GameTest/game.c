//---------------------------------------------------------
// file:	game.c
// author:	TAN JUN QUAN
// email:	t.junquan@digipen.edu
//
// brief:   When the player goes into red or green circles,
//			they will lose and gain health respectively
//			Render health bar on top, with segmented health
//			bar every 10%
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "game.h"

CP_Color bg, red, green, hpcol; //colors
float speed; //speed
float width, height; //window width/height
float hpx1, hpx2, hpy1, hpy2; //positions of hp bar
CP_Font text;

int numplats = 2;

void Game_Init(void)
{
	// load font
	text = CP_Font_Load("Assets/Exo2-Regular.ttf");

	// get window size
	width = CP_System_GetWindowWidth();
	height = CP_System_GetWindowHeight();

	// initialize colors
	bg = CP_Color_Create(100, 100, 100, 255); //background
	red = CP_Color_Create(200, 50, 50, 255); //red
	green = CP_Color_Create(50, 200, 50, 255); //green
	hpcol = CP_Color_Create(255, 150, 150, 255); //hp colour

	// initialize base speed
	speed = 400;

	// initialize movestate
	movestate = 0;

	// initialize player
	// size
	p.width = 30;
	p.height = 30;
	// position
	p.x = 700;
	p.y = 200;
	// movement
	p.movex = 0;
	p.movey = 0;
	// health
	p.hp = 100;
	// color
	p.color = CP_Color_Create(150, 150, 200, 255);

	// PLATFORMS INITIALIZATION
	/*---------------------------------------------------------------------------------------------------*/
#pragma region Initialize Platform

	FILE* file = fopen("Assets/coordinates.txt", "r");
	int pindex = 0; int pcindex = 0;
	int test = 0;
	while (pindex < numplats) {
		int x, y;
		fscanf_s(file, "%d", &Platform[pindex].numcoords);

		while (pcindex < Platform[pindex].numcoords) {
			fscanf_s(file, "%d %d", &x, &y);
			platcoord(pindex, pcindex, x, y);
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

	//healthbar position
	hpx1 = width / 10; hpx2 = 9 * width / 10;
	hpy1 = 50; hpy2 = 100;
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
	// change movestate, teleport up/down
	// 0 is platformer, 1 is inplatform
	// NOTE: TO ADD TRANSITION PHASE
	if (CP_Input_KeyTriggered(KEY_E)) {
		if (movestate == 0) { p.y += 100; }
		else p.y -= 100;
		movestate = (movestate == 0) ? 1 : 0;
	}

	// conditional switch
	if (CP_Input_KeyTriggered(KEY_F)) {
		if (movestate == 0 && p.onplatform == 1 && p.withinx == 1) { 
			p.y += 100;
			movestate = 1;
		}
		else if (movestate == 1) { //missing condition
			p.y -= 100;
			movestate = 0;
		}
	}

	// different movement logics
	if (movestate == 0) { // platformer
		p.movex = 0; p.movey += 10;
		if (CP_Input_KeyDown(KEY_W)) { p.movey = -speed; }; //temp fly
		if (CP_Input_KeyTriggered(KEY_SPACE) && p.onplatform == 1) { p.movey = -speed; } // jump!
		if (CP_Input_KeyDown(KEY_A)) { p.movex = -speed; };
		if (CP_Input_KeyDown(KEY_D)) { p.movex = speed; };
	}
	if (movestate == 1) { // top down/inside platform
		p.movex = 0; p.movey = 0;
		if (CP_Input_KeyDown(KEY_W)) { p.movey = -speed; };
		if (CP_Input_KeyDown(KEY_A)) { p.movex = -speed; };
		if (CP_Input_KeyDown(KEY_S)) { p.movey = speed; };
		if (CP_Input_KeyDown(KEY_D)) { p.movex = speed; };
	}


	// position update
	p.x += p.movex * dt;
	p.y += p.movey * dt;

	// reset checks for jumping and entering
	p.onplatform = 0;
	p.withinx = 0;
	// collision against platforms
	for (int plat_index = 0; plat_index < numplats; plat_index++) {
		CollPlatforms(plat_index, Platform[plat_index].numcoords, Platform[plat_index], &p, p);
	}

#pragma endregion

	// HP
	/*---------------------------------------------------------------------------------------------------*/
#pragma region HP

	// hp clamp
	if (p.hp < 0) { p.hp = 0; };
	if (p.hp > 100) { p.hp = 100; };
#pragma endregion

	// RENDER
	/*---------------------------------------------------------------------------------------------------*/
#pragma region RENDER

	// DRAW PLATFORMS
	for (int i = 0; i < numplats; i++) {
		DrawPlatform(i);
	}

	// Player
	CP_Settings_Fill(p.color);
	CP_Graphics_DrawRect(p.x - 10, p.y - 10, p.width + 20, p.height + 20);

	// Health Bars
	// Graphics settings
	CP_Settings_Fill(hpcol); 
	CP_Settings_RectMode(CP_POSITION_CORNER);

#pragma endregion

	// Back to main menu
	if (CP_Input_KeyDown(KEY_Q)) { CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); };
}

void Game_Exit(void)
{

}