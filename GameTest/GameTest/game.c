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
<<<<<<< Updated upstream
=======
CP_Image player_sprite;
float totalMinutes, totalSeconds; // timer
int isPaused; // check if game paused
float frameRate;
>>>>>>> Stashed changes

int numplats = 2;

void Game_Init(void)
{
	// set frame rate
	frameRate = CP_System_GetFrameRate();

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

	//initialize test goal
	goalx = 1000;
	goaly = 350;

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

	// game pause
	isPaused = 0;

	// check if level complete
	isCleared = 0;

	// score
	levelScore = 0;

	// PLATFORMS INITIALIZATION
	/*---------------------------------------------------------------------------------------------------*/
#pragma region Initialize Platform

	FILE* file = fopen("Assets/Base.txt", "r");
	int pindex = 0; int pcindex = 0;
	int test = 0;
	while (pindex < numplats) {
		int x, y;
		fscanf_s(file, "%d", &Platform[pindex].numcoords);

		while (pcindex < Platform[pindex].numcoords) {
			fscanf_s(file, "%d %d", &x, &y);
			platform_coordinates(pindex, pcindex, x, y);
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

<<<<<<< Updated upstream
=======
	// track pointer
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	// pause/resume game with Esc
	if (CP_Input_KeyTriggered(KEY_ESCAPE) && isPaused == 0) {
		isPaused = 1;

	}
	else if (CP_Input_KeyTriggered(KEY_ESCAPE) && isPaused == 1) {
		isPaused = 0;
	}

>>>>>>> Stashed changes
	// Timer UI
	if (isPaused == 0 && isCleared == 0) {
		totalMinutes = totalMinutes;
		totalSeconds += dt;
	}
	else if (isPaused == 1) {
		totalMinutes = totalMinutes;
		totalSeconds = totalSeconds;
	}
	
	totalMinutes = 0.0;
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(60);
	char time[16] = { 0 };
	if (totalSeconds >= 60) {
		totalSeconds -= 60;
		totalMinutes += 1;
	}
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_RIGHT;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_BASELINE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Font_DrawText("Time: ", 1400, 100);
	sprintf_s(time, 16, "%02d:%02d", (int) totalMinutes, (int) totalSeconds);
	CP_Font_DrawText(time, 1550, 100);

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

<<<<<<< Updated upstream
	// conditional switch
	if (CP_Input_KeyTriggered(KEY_F)) {
		if (movestate == 0 && p.onplatform == 1 && p.withinx == 1) {
			p.y += 80;
			movestate = 1;
		}
<<<<<<< Updated upstream
		else if (movestate == 1 && p.y > 200 && p.leaveplatform == 1) {
			p.y -= 80;
			movestate = 0;
=======
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
			player.stamina += 40.0f * dt;
			for (int plat_index = 0; plat_index < numplats; plat_index++) {
				CollOnPlatforms(plat_index, Platform[plat_index], &player, player);
			}
		}

		else if (movestate == InPlat) {
			player.stamina -= 20.0f * dt;
			for (int plat_index = 0; plat_index < numplats; plat_index++) {
				CollPlatforms(plat_index, Platform[plat_index], &player, player);
			}
		}
		player.stamina = CP_Math_ClampFloat(player.stamina, 0, 100);

		// window clamps
		player.x = CP_Math_ClampFloat(player.x, 0, width - player.width);
		if (player.y + player.height > height || player.y < 0) {
			player.movey = 0;
		}
		player.y = CP_Math_ClampFloat(player.y, 0, height - player.height);

		// reset with R or touch ground while movestate OnPlat
		if (CP_Input_KeyTriggered(KEY_R) || ((player.y >= height - player.height) && movestate == OnPlat) || (player.stamina == 0)) {
			player.x = spawnx;
			player.y = spawny;
			movestate = OnPlat;
			player.movey = 0;
			deaths++;
			AddScore(&levelScore, -100, &isCleared);
>>>>>>> Stashed changes
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
=======
	// movement logics
	if (isPaused == 0) {
		movement(&player, movestate, speed, dt);
	}
>>>>>>> Stashed changes

	// reset checks for jumping and entering
	p.onplatform = 0;
	p.withinx = 0;
	p.leaveplatform = 0;
	// collision against platforms
	for (int plat_index = 0; plat_index < numplats; plat_index++) {
		CollPlatforms(plat_index, Platform[plat_index].numcoords, Platform[plat_index], &p, p);
	}
	// window clamps
	p.x = CP_Math_ClampFloat(p.x, 0, width - p.width);
	/*if (p.x < 0) {
		p.x = 0;
	}
	if (p.x + p.width > width) {
		p.x = width - p.width;
	}*/
	if (p.y + p.height > height || p.y<0) {
		p.movey = 0;
	}
	p.y = CP_Math_ClampFloat(p.y, 0, height - p.height);

<<<<<<< Updated upstream
#pragma endregion

	// HP
	/*---------------------------------------------------------------------------------------------------*/
#pragma region HP

	// hp clamp
	if (p.hp < 0) { p.hp = 0; };
	if (p.hp > 100) { p.hp = 100; };
=======
	// reset with R or touch ground while movestate OnPlat
	if (CP_Input_KeyDown(KEY_R) || ((player.y >= height - player.height) && movestate == OnPlat)) {
		player.x = 150;
		player.y = 200;
		movestate = OnPlat;
		player.movey = 0;
	}

	// pause/resume game with Esc
	if (isPaused == 1) {
		CP_Font_DrawText("PAUSED", width / 2, 100);
	}
	if (CP_Input_KeyTriggered(KEY_ESCAPE) && isPaused == 0) {
		isPaused = 1;
		
	}
	else if (CP_Input_KeyTriggered(KEY_ESCAPE) && isPaused == 1) {
		isPaused = 0;
	}
>>>>>>> Stashed changes
#pragma endregion

	// RENDER
	/*---------------------------------------------------------------------------------------------------*/
#pragma region RENDER

	// Platforms
	for (int i = 0; i < numplats; i++) {
		DrawPlatform(i);
	}

<<<<<<< Updated upstream
=======
	// Goal
	CP_Settings_Fill(green);
	CP_Graphics_DrawRect(goalx, goaly, 50, 50);

	if (AreSquaresIntersecting(player.x - 15, player.y - 15, player.height + 30, player.width + 30, goalx, goaly, 50, 50)) {
		CP_Settings_Fill(green);
		CP_Settings_TextSize(100);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Font_DrawText("You touched grass", width / 2, 50);
		AddScore(&levelScore, 1000, &isCleared);
		isCleared = 1;
	}

	// HAZARD DRAWING
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawTriangle(traps[0].x[0], traps[0].y[0], traps[0].x[1], traps[0].y[1], traps[0].x[2], traps[0].y[2]);

>>>>>>> Stashed changes
	// Player
	CP_Settings_Fill(p.color);
	CP_Graphics_DrawRect(p.x - 10, p.y - 10, p.width + 20, p.height + 20);

	// Health Bars
	// Graphics settings
	CP_Settings_Fill(hpcol); 
	CP_Settings_RectMode(CP_POSITION_CORNER);

<<<<<<< Updated upstream
=======
	// SCORE DRAWING
	char score[20] = { 0 };
	sprintf_s(score, 20, "SCORE: %d", levelScore);
	CP_Font_DrawText(score, 1250, 50);
	// TIMER DRAWING
	sprintf_s(time, 16, "TIME: %02d:%02d:%02d", (int)totalMinutes, (int)totalSeconds, (int)totalMillis);
	CP_Font_DrawText(time, 1250, 100);

	// PAUSE PAGE
	if (isPaused == 1) {
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Settings_Fill(pausebg);
		CP_Graphics_DrawRect(width/2, height/2, width, height);
		CP_Settings_Fill(plat);
		CP_Graphics_DrawRect(width/2, height/2, 1200, 600);
		CP_Settings_Fill(black);
		CP_Settings_TextSize(150);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Font_DrawText("PAUSED", width/2, 300);

		CP_Settings_TextSize(100);
		// draw resume button
		TextBoxCreate(500, 2 * height / 3, 350, 200, "RESUME", red);
		int ResumeClick = IsAreaClicked(500, 2 * height / 3, 350, 200, mouseX, mouseY); //if mouse is over button
		if (ResumeClick) {
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); // highlight button
			CP_Graphics_DrawRect(500, 2 * height / 3, 350, 200);
			if (CP_Input_MouseClicked()) { //if LMB1 pressed
				isPaused = 0;
			}
		}

		// draw quit button
		TextBoxCreate(1100, 2 * height / 3, 350, 200, "QUIT", red);
		int QuitClick = IsAreaClicked(1100, 2 * height / 3, 350, 200, mouseX, mouseY); //if mouse is over button
		if (QuitClick) {
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50)); // highlight button
			CP_Graphics_DrawRect(1100, 2 * height / 3, 350, 200);
			if (CP_Input_MouseClicked()) { //if LMB1 pressed
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			}
		}
		CP_Settings_RectMode(CP_POSITION_CORNER);
	}
>>>>>>> Stashed changes
#pragma endregion

	// Back to main menu
	if (CP_Input_KeyDown(KEY_Q)) { CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); };
}

void Game_Exit(void)
{

}