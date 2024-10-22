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

#include "Level1.h"

CP_Color bg, red, green, hpcol; //colors
float speed; //speed
float width, height; //window width/height
float hpx1, hpx2, hpy1, hpy2; //positions of hp bar
CP_Font text;
CP_Image player_sprite;

int numplats1 = 4;

void L1_Init(void)
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
	speed = 400;

	// initialize movestate
	movestate = 0;

	// initialize switchtime
	switchtime = 1;

	// initialize player
	// size
	player.width = 30;
	player.height = 30;
	// position
	player.x = 150;
	player.y = 200;
	// movement
	player.movex = 0;
	player.movey = 0;
	// health
	player.hp = 100;
	// color
	player.color = CP_Color_Create(150, 150, 200, 255);

	// PLATFORMS INITIALIZATION
	/*---------------------------------------------------------------------------------------------------*/
#pragma region Initialize Platform

	FILE* file = fopen("Assets/Level1.txt", "r");
	// pindex - platform index
	// pcindex - platform coordinate index
	int pindex = 0; int pcindex = 0;
	while (pindex < numplats1) {
		// coordinate ints to read
		int x, y;
		// scan how many coordinates
		fscanf_s(file, "%d", &Platform[pindex].numcoords);
		// for how many coordinates in platform
		while (pcindex < Platform[pindex].numcoords) {
			// scan coordinates
			fscanf_s(file, "%d %d", &x, &y);
			// assign coordinates to array
			platform_coordinates(pindex, pcindex, x, y);
			pcindex++;
		}
		pcindex = 0;
		pindex++;
	}
	fclose(file);

	// initialize all platform hitboxes
	for (int plat_index = 0; plat_index < numplats1; plat_index++) {
		hitbox(plat_index, Platform[plat_index].numcoords, &Platform[plat_index]);
	}

#pragma endregion

	//healthbar position
	hpx1 = width / 10; hpx2 = 9 * width / 10;
	hpy1 = 50; hpy2 = 100;

	// Corner drawing
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_ImageMode(CP_POSITION_CORNER);
}


void L1_Update(void)
{
	// background
	CP_Graphics_ClearBackground(bg);
	// getdt
	float dt = CP_System_GetDt();

	// MOVEMENT 
	/*---------------------------------------------------------------------------------------------------*/
#pragma region Movement
		// change movestate, teleport up/down
	// 0 is platformer, 1 is inplatform, 2 is 0>1, 3 is 1>0

	if (CP_Input_KeyTriggered(KEY_E)&&(movestate==1 || movestate==0)) {
		/*if (movestate == 0 && player.onplatform == 1 && player.withinx == 1) {
			movestate=2;
			switchtime = 0;
		}
		else if (movestate == 1 && player.y > 200 && player.leaveplatform == 1) {
			movestate = 3;
			switchtime = 0;
		}*/
		movestate = start_transition(&player, movestate);
		if (movestate == 2 || movestate == 3) {
			switchtime = 0;
		}
	}


	//movestate = end_transition(&player, dt, switchtime, movestate);
	if (switchtime < 1) {
		if ((movestate == 2 && switchtime < 0.5) || (movestate == 3 && switchtime >= 0.5)) {
			player.movey += 800 * dt;
		}
		if ((movestate == 3 && switchtime < 0.5) || (movestate == 2 && switchtime >= 0.5)) {
			player.movey -= 800 * dt;
		}
		switchtime += 2 * dt;
	}
	if (switchtime >= 1) {
		if (movestate == 2) {
			movestate = 1;
		}
		if (movestate == 3) {
			movestate = 0;
		}
	}

	// Movement logic
	movement(&player, movestate, speed);

	// position update
	player.x += player.movex * dt;
	player.y += player.movey * dt;

	// reset checks for jumping and entering
	player.onplatform = 0;
	player.withinx = 0;
	player.leaveplatform = 0;
	// collision against platforms
	if (movestate == 1 || movestate == 0) {
		for (int plat_index = 0; plat_index < numplats1; plat_index++) {
			CollPlatforms(plat_index, Platform[plat_index].numcoords, Platform[plat_index], &player, player);
		}
	}
	// window clamps
	if (player.x < 0) {
		player.x = 0;
	}
	if (player.x + player.width > width) {
		player.x = width - player.width;
	}
	if (player.y < 0) {
		player.y = 0;
		player.movey = 0;
	}
	if (player.y + player.height > height) {
		player.y = height - player.height;
		player.movey = 0;
	}
	// reset with R or touch ground in platform movestate
	if (CP_Input_KeyDown(KEY_R)|| ((player.y >= height - player.height) && movestate == 0)) {
		player.x = 150;
		player.y = 200;
		movestate = 0;
		player.movey = 0;
	}
	

#pragma endregion

	// HP
	/*---------------------------------------------------------------------------------------------------*/
#pragma region HP

	// hp clamp
	if (player.hp < 0) { player.hp = 0; };
	if (player.hp > 100) { player.hp = 100; };
#pragma endregion

	// RENDER
	/*---------------------------------------------------------------------------------------------------*/
#pragma region RENDER

	// Platforms
	CP_Settings_Fill(hpcol);
	for (int i = 0; i < numplats1; i++) {
		DrawPlatform(i);
	}

	// Goal
	CP_Settings_Fill(green);
	CP_Graphics_DrawRect(1520, 250, 50, 50);

	if (AreSquaresIntersecting(player.x,player.y,player.height,player.width,1520,250,50,50)) {
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText("Yippie!", 1300, 50);
	}

	// Player
	// CP_Settings_Fill(player.color);
	// CP_Graphics_DrawRect(player.x - 10, player.y - 10, player.width + 20, player.height + 20);
	CP_Image_Draw(player_sprite, player.x - 10, player.y - 10, player.width + 20, player.height + 20, 255);

#pragma endregion

	// Back to main menu
	if (CP_Input_KeyDown(KEY_Q)) { CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); };
}

void L1_Exit(void)
{

	CP_Image_Free(player_sprite);

}