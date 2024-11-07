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

//

void Camera_Init(Camera* cam) { 

	float screenX = CP_System_GetWindowWidth();
	float screenY = CP_System_GetWindowHeight();
	//cam->showtotalx = screenX * camera.zoom;
	//cam->showtotaly = screenY * camera.zoom;
	//cam->limitleftx = camera.showtotalx * 1.0 / 10.0f;
	//cam->limitlefty = camera.showtotaly;
	//cam->limitrightx = camera.showtotalx * 4.0 / 10.0f;
	//cam->limitrighty = camera.showtotaly * 4.0 / 10.0f; //keep note that i might need 4 points per line.
	//cam->zoom = 1.0;
}

void Camera_Update(Camera* cam) {
	//assign window width and height
	int winWidth = CP_System_GetWindowWidth();
	int winHeight = CP_System_GetWindowHeight();

	//track pointer
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 128));
	CP_Settings_NoFill(); //s allows me to draw rect without fill
	

	CP_Settings_RectMode(CP_POSITION_CORNER);//allows program to know where is
	

	//header text



}


void Camera_Exit(void) 
{



}