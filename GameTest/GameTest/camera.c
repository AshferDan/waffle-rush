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

#pragma once
#include "camera.h"

void playerCamColl(Player *player, Camera* camera) {
	float playerR = player->x + player->width;
	float playerB = player->y + player->height;

	if (playerR > camera->limitrightx) {
		camera->limitleftx += playerR - camera->limitrightx;
		camera->limitrightx += playerR -camera->limitrightx;

	}
	else if (player->x < camera->limitleftx) {
		camera->limitrightx -= camera->limitleftx - player->x;
		camera->limitleftx -= camera->limitleftx - player->x;
	}
	camera->worldshiftx = camera->limitleftx - camera->spawnX;
	if (player->y < camera->limittop) {
		camera->limitbase -= camera->limittop - player->y;
		camera->limittop -= camera->limittop - player->y;
	}
	else if (playerB > camera->limitbase) {
		camera->limittop += playerB - camera->limitbase;
		camera->limitbase += playerB - camera->limitbase;
	}
	camera->worldshifty = camera->limittop - camera->spawnY;
}


