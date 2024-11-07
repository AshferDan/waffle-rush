//---------------------------------------------------------
// file:	Level1.c
// author:	AVID WAFFLE ENJOYERS
// email:	-
//
// brief:   Level 1 stage
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "Level1.h"
#include "camera.h"
Camera camera;
float screenX;
float screenY;
float offsetX;
float offsetY;
int CollDetect;


void L2_Init(void)
{
#pragma region im not using these
	// ASSET LOADS
	/*---------------------------------------------------------------------------------------------------------------------*/
#pragma region Assets
	// load font
	text = CP_Font_Load("Assets/Exo2-Regular.ttf");

	// load player sprite
	player_sprite = CP_Image_Load("Assets/Player_Sprites.png");
#pragma endregion
	// MAP INIT
	/*---------------------------------------------------------------------------------------------------------------------*/
#pragma region MAP
	// initialize spawn location
	spawnx = 150;
	spawny = 200;
	// initialize test goal
	goalx = 1520;
	goaly = 250;

	// PLATFORMS INITIALIZATION
	/*---------------------------------------------------------------------------------------------------------------------*/
#pragma region Initialize Platform
	FILE* file = fopen("Assets/Level2.txt", "r");

	if (file == NULL) {
		printf("Failed to open platform file! Check if file exists\n");
		CP_Engine_Terminate;
	}
	// read how many platforms in level
	fscanf_s(file, "%d", &numplats);

	// plat_index - platform index
	// plat_coord_index - platform coordinate index
	int plat_index = 0; int plat_coord_index = 0;
	while (plat_index < numplats) {
		// coordinate ints to read
		// scan how many coordinates
		fscanf_s(file, "%d", &Platform[plat_index].numcoords);
		// for how many coordinates in platform
		while (plat_coord_index < Platform[plat_index].numcoords) {
			int x, y;
			// scan coordinates
			fscanf_s(file, "%d %d", &x, &y);
			// assign coordinates to array
			platform_coordinates(plat_index, plat_coord_index, x, y);
			plat_coord_index++;
		}
		plat_coord_index = 0;
		fscanf_s(file, "%d", &Platform[plat_index].numblocks);
		while (plat_coord_index < Platform[plat_index].numblocks) {
			int x1, y1, x2, y2;
			fscanf_s(file, "%d %d %d %d", &x1, &y1, &x2, &y2);
			platform_onblocks(plat_index, plat_coord_index, x1, y1, x2, y2);
			plat_coord_index++;
		}
		plat_coord_index = 0;
		plat_index++;
	}
	fclose(file);

	// initialize all platform hitboxes
	for (int plat_index = 0; plat_index < numplats; plat_index++) {
		hitbox(plat_index, Platform[plat_index].numcoords, &Platform[plat_index]);
	}


#pragma endregion

	//HAZARDS
	/*---------------------------------------------------------------------------------------------------------------------*/
#pragma region Hazard
	FILE* file1 = fopen("Assets/Level1hazard.txt", "r");
	fscanf_s(file1, "%d", &numberoftraps);

	for (int i = 0; i < numberoftraps; ++i) {
		for (int j = 0; j < 3; ++j) {
			fscanf_s(file1, "%d %d", &traps[i].x[j], &traps[i].y[j]);
		}
		fscanf_s(file1, "%d", &traps[i].type);
	}

	fclose(file1);
#pragma endregion
#pragma endregion
	// PLAYER INITS
	/*---------------------------------------------------------------------------------------------------------------------*/
#pragma region Player related
	// initialize base speed
	speed = 600;

	// initialize player struct
	// size
	player.width = 20;
	player.height = 20;
	// position
	player.x = spawnx;
	player.y = spawny;
	// movement
	player.movex = 0;
	player.movey = 0;
	// transit variables
	player.transition_time = 1.0f;
	// health
	player.stamina = 100.0f;
	// color
	player.color = CP_Color_Create(150, 150, 200, 255);

	// initialize deaths
	deaths = 0;
#pragma endregion
	// Game states, counters
	/*---------------------------------------------------------------------------------------------------------------------*/
#pragma region States and counters
	// initialize movestate
	movestate = OnPlat;

	// timer
	timer = (Timer){ 0,0,0 };

	// game pause
	isPaused = 0;

	// check if level complete
	isCleared = 0;

	// score
	levelScore = 0;
#pragma endregion
	// Misc settings
	/*---------------------------------------------------------------------------------------------------------------------*/
#pragma region Misc inits and settings
	// Window size
	width = CP_System_GetWindowWidth();
	height = CP_System_GetWindowHeight();

	// Initialize colors
	pausebg = CP_Color_Create(0, 0, 0, 100);
	bg = CP_Color_Create(100, 100, 100, 255); //background
	black = CP_Color_Create(0, 0, 0, 255); //black
	red = CP_Color_Create(200, 50, 50, 255); //red
	green = CP_Color_Create(50, 200, 50, 255); //green
	plat = CP_Color_Create(255, 150, 150, 255); //platform colour
	stamina = CP_Color_Create(255, 255, 40, 255); //stamina colour

	// Corner drawing
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_ImageMode(CP_POSITION_CORNER);
#pragma endregion

#pragma endregion

	// CAMERA INIT
		/*---------------------------------------------------------------------------------------------------------------------*/
#pragma region Camera
	float screenX = CP_System_GetWindowWidth();
	float screenY = CP_System_GetWindowHeight();
	camera.limitleftx = screenX * 1.0f / 10.0f;
	camera.limitrightx = screenX * 4.0f / 10.0f;
	camera.limitheight1 = screenY * 0.3f;
	camera.limitheight2 = screenY * 0.8f;
	camera.width = camera.limitrightx - camera.limitleftx;
	camera.height = camera.limitheight2 - camera.limitheight1;
	camera.contactLeft = 0b01;
	camera.contactRight = 0b10;
	offsetX = 0;
	offsetY = 0;
	CollDetect = 0;
	
	
#pragma endregion
}

void L2_Update(void)
{
	// background
	CP_Graphics_ClearBackground(bg);

	// getdt
	float dt = CP_System_GetDt();

	// get mouse coords
	mouseX = CP_Input_GetMouseX();
	mouseY = CP_Input_GetMouseY();


	// pause/resume game with Esc
	if (CP_Input_KeyTriggered(KEY_ESCAPE) && isPaused == 0) {
		isPaused = 1;

	}
	else if (CP_Input_KeyTriggered(KEY_ESCAPE) && isPaused == 1) {
		isPaused = 0;
	}

	// Timer update
	if (isPaused == 0 && isCleared == 0) {
		timer.seconds += dt;
		if (timer.seconds >= 60) {
			timer.seconds = 0;
			timer.minutes++;
		}
		timer.millis = (int)(timer.seconds * 100) % 100;
	}

	// MOVEMENT 
	/*---------------------------------------------------------------------------------------------------------------------*/
#pragma region Movement
	// pause check
	if (isPaused == 0) {
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
		printf("movex %f, movey %f\n", player.movex, player.movey);
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
		}

		// animation timer update
		player.anim += 10 * dt;
		if (player.anim >= 20) {
			player.anim = 0;
		}
	}
#pragma endregion

	// CAMERA 
	/*---------------------------------------------------------------------------------------------------------------------*/

	// RENDER
	/*---------------------------------------------------------------------------------------------------*/
#pragma region RENDER
	// Platforms
	CP_Settings_Fill(plat);
	for (int i = 0; i < numplats; i++) {
		DrawPlatform(i);
	}

	// Goal
	CP_Settings_Fill(green);
	CP_Graphics_DrawRect(goalx, goaly, 50, 50);

	if (AreSquaresIntersecting(player.x - 15,player.y - 15,player.height + 30,player.width + 30,goalx,goaly,50,50)) {
		CP_Settings_Fill(green);
		CP_Settings_TextSize(150);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Font_DrawText("Yippie!", 1300, 50);
		AddScore(&levelScore, 1000, &isCleared);
		isCleared = 1;
	}

	// Player
	Draw_Player(player_sprite, player, &sprite_x, &sprite_y);

	// Stamina Bar
	CP_Settings_Fill(stamina);
	if (player.stamina <= 35.0f) {
		CP_Settings_Fill(red);
	}
	DrawStatBar(player.x - 15, player.y - 30, player.x + 35, player.y - 23, player.stamina, 100);


	// PAUSE PAGE
	if (isPaused == 1) {
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Settings_Fill(pausebg);
		CP_Graphics_DrawRect(width / 2, height / 2, width, height);
		CP_Settings_Fill(plat);
		CP_Graphics_DrawRect(width / 2, height / 2, 1200, 600);
		CP_Settings_Fill(black);
		CP_Settings_TextSize(150);
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Font_DrawText("PAUSED", width / 2, 300);

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
#pragma endregion
	
#pragma region Camera

	printf("limitleftx %f| limitrightx %f\n", camera.limitleftx, camera.limitheight1);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 128));
	CP_Settings_NoFill();
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(camera.limitleftx + offsetX, camera.limitheight1-offsetY, camera.width, camera.height);






#pragma endregion
	// Back to main menu
	if (CP_Input_KeyDown(KEY_Q)) { CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit); };

}

void L2_Exit(void)
{

	CP_Image_Free(player_sprite);

}