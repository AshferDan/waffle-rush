#pragma once
//---------------------------------------------------------
// file:	credits.h
// author:	AVID WAFFLE ENJOYERS
// email:	-
//
// brief:	Declarations of game stage
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "mainmenu.h"
#include "game.h"
#include "utils.h"
#include "platform.h"



typedef struct camera {
	float limitleftx; //invis border
	float limitrightx;
	float width;
	float height;
	float limitheight1;
	float limitheight2;
	float worldshiftx;
	float worldshifty;
	int contactLeft;
	int contactRight;
	int contactUp;
	int contactDown;



} Camera;

Camera camera;

void Camera_Init(Camera * camera);
void Camera_Update(Camera* camera);
void Camera_Exit(void);