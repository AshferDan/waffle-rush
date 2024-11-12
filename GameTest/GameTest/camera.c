//---------------------------------------------------------
// file:	credits.c
// author:	AVID WAFFLE ENJOYERS
// email:	-
//
// brief:	Credits page
//			
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "camera.h"

	////assign window width and height
	//int winWidth = CP_System_GetWindowWidth();
	//int winHeight = CP_System_GetWindowHeight();

	//draw ur fucking camera
	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 128));
	//CP_Settings_NoFill(); //s allows me to draw rect without fill
	//CP_Settings_RectMode(CP_POSITION_CORNER);//allows program to know where is


int playerCamColl(Player *player, Camera * camera) {
	float playerR = player->x + player->width;

	if (playerR > camera->limitrightx) {
		printf("too far right");
		//camera->worldshiftx += 5; //this is the distance between player and border
		camera->worldshiftx += playerR - camera->limitrightx; //this is the distance between player and border
		camera->limitleftx += playerR - camera->limitrightx;
		camera->limitrightx += playerR -camera->limitrightx;

	}
	else if (player->x < camera->limitleftx) {
		printf("too far left");
		//camera->worldshiftx -= 5; //this is the distance between player and border
		camera->worldshiftx -= camera->limitleftx - player->x ; //this is the distance between player and border
		camera->limitrightx -= camera->limitleftx - player->x;
		camera->limitleftx -= camera->limitleftx - player->x;
	}

}


