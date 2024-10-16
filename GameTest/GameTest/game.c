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


struct Player p; //player p

int platcount = 8;
struct platform Platforms[8];

struct platform2 Platformtest[1];

int movestate; //0 = platformer, 1 = platform

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
	p.width = 50;
	p.height = 50;
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


	Platforms[0] = (struct platform){ 550, 550 + 300, 400, 400 + 25, 300, 25 };
	Platforms[1] = (struct platform){ 1000, 1000 + 150, 400, 400 + 200, 150, 200 };
	Platforms[2] = (struct platform){ 525, 525 + 25, 400, 400 + 400, 25, 400 };
	Platforms[3] = (struct platform){ 550, 550 + 150, 775, 775 + 25, 150, 25 };
	Platforms[4] = (struct platform){ 700, 700 + 25, 600, 600 + 200, 25, 200 };
	Platforms[5] = (struct platform){ 725, 725 + 125, 600, 600 + 25, 125, 25 };
	Platforms[6] = (struct platform){ 850, 850 + 25, 400, 400 + 225, 25, 225 };

	// first platform
	Platformtest[0].numcoords = 6;
	Platformtest[0].platcoords[0] = (struct coords){ 50, 300 };
	Platformtest[0].platcoords[1] = (struct coords){ 400, 300 };
	Platformtest[0].platcoords[2] = (struct coords){ 400, 450 };
	Platformtest[0].platcoords[3] = (struct coords){ 450, 450 };
	Platformtest[0].platcoords[4] = (struct coords){ 450, 600 };
	Platformtest[0].platcoords[5] = (struct coords){ 50, 600 };
	for (int i = 0; i < Platformtest[0].numcoords; i++) {
		
		if (i % 2 == 0 && i < Platformtest[0].numcoords-1) { //horizontal

			if (Platformtest[0].platcoords[i + 1].x > Platformtest[0].platcoords[i].x) {
				Platformtest[0].blocks[i] = (struct platblocks){
					Platformtest[0].platcoords[i].x + 10,
					Platformtest[0].platcoords[i + 1].x - 10,
					Platformtest[0].platcoords[i].y - 10,
					Platformtest[0].platcoords[i].y + 10,
					(Platformtest[0].platcoords[i + 1].x - 10) - (Platformtest[0].platcoords[i].x + 10),
					20
				};
			}
			else {
				Platformtest[0].blocks[i] = (struct platblocks){
					Platformtest[0].platcoords[i + 1].x + 10,
					Platformtest[0].platcoords[i].x - 10,
					Platformtest[0].platcoords[i].y - 10,
					Platformtest[0].platcoords[i].y + 10,
					(Platformtest[0].platcoords[i].x - 10) - (Platformtest[0].platcoords[i + 1].x + 10),
					20
				};
			}
			//printf("Platcoord [%d] x1 %f, x2 %f, y1 %f, y2 %f, w %f, h %f\n", i, Platformtest[0].blocks[i].x1, Platformtest[0].blocks[i].x2, Platformtest[0].blocks[i].y1, Platformtest[0].blocks[i].y2, Platformtest[0].blocks[i].w, Platformtest[0].blocks[i].h);
		}
		else if (i != Platformtest[0].numcoords-1) { //vertical
			Platformtest[0].blocks[i] = (struct platblocks){
				Platformtest[0].platcoords[i].x-10,
				Platformtest[0].platcoords[i].x+10,
				Platformtest[0].platcoords[i].y - 10,
				Platformtest[0].platcoords[i + 1].y+10,
				20,
				(Platformtest[0].platcoords[i + 1].y+10) - (Platformtest[0].platcoords[i].y-10)
			};
			//printf("Platcoord [%d] x1 %f, x2 %f, y1 %f, y2 %f, w %f, h %f\n", i, Platformtest[0].blocks[i].x1, Platformtest[0].blocks[i].x2, Platformtest[0].blocks[i].y1, Platformtest[0].blocks[i].y2, Platformtest[0].blocks[i].w, Platformtest[0].blocks[i].h);
		}
		else {
			Platformtest[0].blocks[i] = (struct platblocks){
			Platformtest[0].platcoords[0].x - 10,
			Platformtest[0].platcoords[i].x + 10,
			Platformtest[0].platcoords[0].y - 10,
			Platformtest[0].platcoords[i].y + 10,
			20,
			(Platformtest[0].platcoords[i].y + 10) - (Platformtest[0].platcoords[0].y-10)
			};
			//printf("FINAL Platcoord [%d] x1 %f, x2 %f, y1 %f, y2 %f, w %f, h %f\n", i, Platformtest[0].blocks[i].x1, Platformtest[0].blocks[i].x2, Platformtest[0].blocks[i].y1, Platformtest[0].blocks[i].y2, Platformtest[0].blocks[i].w, Platformtest[0].blocks[i].h);
		}
		
	}

	

	// second platform
	


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

	// MOVEMENT ----------------------------------------------/
#pragma region Movement

	if (CP_Input_KeyTriggered(KEY_E)) {
		if (movestate == 0) { p.y += 100; }
		else p.y -= 100;
		movestate = (movestate==0) ? 1 : 0;
	}

	// change when key pressed
	if (movestate == 0) {
		p.movex = 0; p.movey += 10;
		if (CP_Input_KeyDown(KEY_W)) { p.movey = -speed; }; //temp
		if (CP_Input_KeyDown(KEY_A)) { p.movex = -speed; };
		if (CP_Input_KeyDown(KEY_D)) { p.movex = speed; };
	}
	if (movestate == 1) {
		p.movex = 0; p.movey = 0;
		if (CP_Input_KeyDown(KEY_W)) { p.movey = -speed; };
		if (CP_Input_KeyDown(KEY_A)) { p.movex = -speed; };
		if (CP_Input_KeyDown(KEY_S)) { p.movey = speed; };
		if (CP_Input_KeyDown(KEY_D)) { p.movex = speed; };
	}


	// position update
	p.x += p.movex * dt;
	p.y += p.movey * dt;
	

	for (int i = 0; i < platcount; i++) {
		if (collision(Platforms[i], p)) {
		int hv = collisionwhere(Platforms[i], p);
		
		if (hv == 2) {
			if (p.x < Platforms[i].x2 && p.x + p.width > Platforms[i].x1) {
				
				p.y = fixcollidey(Platforms[i], p);
				if ((p.y + p.height) == Platforms[i].y1) {
					if (CP_Input_KeyTriggered(KEY_SPACE)) { p.movey = -speed; };
				}
				if (p.y < Platforms[i].y1 && p.movey > 0 || p.y > Platforms[i].y1 && p.movey < 0) { p.movey = 0; }

			}
		}else p.x = fixcollidex(Platforms[i], p);
		}

	}

	for (int i = 0; i < Platformtest[0].numcoords; i++) {
		if (collisiontest(Platformtest[0].blocks[i], p)) {
			int hv = collisionwheretest(Platformtest[0].blocks[i], p);

			if (hv == 2) {
				if (p.x < Platformtest[0].blocks[i].x2 && p.x + p.width > Platformtest[0].blocks[i].x1) {

					p.y = fixcollideytest(Platformtest[0].blocks[i], p);
					if ((p.y + p.height) == Platformtest[0].blocks[i].y1) {
						if (CP_Input_KeyTriggered(KEY_SPACE)) { p.movey = -speed; };
					}
					if (p.y < Platformtest[0].blocks[i].y1 && p.movey > 0 || p.y > Platformtest[0].blocks[i].y1 && p.movey < 0) { p.movey = 0; }

				}
			}
			else p.x = fixcollidextest(Platformtest[0].blocks[i], p);
		}

	}



#pragma endregion

	//HP		----------------------------------------------/
#pragma region HP

	// hp clamp
	if (p.hp < 0) { p.hp = 0; };
	if (p.hp > 100) { p.hp = 100; };
#pragma endregion

	// RENDER	----------------------------------------------/
#pragma region RENDER

	// Platforms
	for (int i = 0; i < platcount; i++) {
		CP_Graphics_DrawRect(Platforms[i].x1, Platforms[i].y1, Platforms[i].width, Platforms[i].height);
	}


	/*CP_Graphics_BeginShape();
	CP_Graphics_AddVertex(50, 400);
	CP_Graphics_AddVertex(400, 400);
	CP_Graphics_AddVertex(400, 450);
	CP_Graphics_AddVertex(450, 450);
	CP_Graphics_AddVertex(450, 500);
	CP_Graphics_AddVertex(50, 500);
	CP_Graphics_EndShape();*/

	

	//for (int i = 0; i <= Platformtest[0].numcoords - 1; i++) {
	//	CP_Graphics_DrawRect(Platformtest[0].blocks[i].x1, Platformtest[0].blocks[i].y1, Platformtest[0].blocks[i].w, Platformtest[0].blocks[i].h);
	//}

	CP_Graphics_BeginShape();
	for (int i = 0; i <= Platformtest[0].numcoords - 1; i++) {
		CP_Graphics_AddVertex(Platformtest[0].platcoords[i].x, Platformtest[0].platcoords[i].y);
	}
	CP_Graphics_EndShape();

	// Player
	CP_Settings_Fill(p.color);
	CP_Graphics_DrawRect(p.x - 10, p.y - 10, p.width + 20, p.height + 20);
//	CP_Graphics_DrawRect(p.x, p.y, p.width, p.height);

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