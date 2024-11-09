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
		camera->worldshiftx = playerR - camera->limitrightx; //this is the distance between player and border
		//camera->limitrightx += camera->worldshiftx;
		//camera->limitleftx += camera->worldshiftx;

	}
	else if (player->x < camera->limitleftx) {
		printf("too far left");
		camera->worldshiftx = camera->limitleftx - player->x; //this is the distance between player and border
		//camera->limitleftx -= camera->worldshiftx;
		//camera->limitrightx -= camera->worldshiftx;
	}

}


