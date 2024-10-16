//---------------------------------------------------------
// file:	utils.h
// author:	TAN JUN QUAN
// email:	t.junquan@digipen.edu
//
// brief:	Declarations of utility functions
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "cprocessing.h"
#include <stdio.h>



// check if position is within a rectangle
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

// check if position is within a circle
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

// check if two circles intersect
int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2);

// create a red box with text within
void TextBoxCreate(float pos_x, float pos_y, float size_x, float size_y, const char* text);

// draw full hp bar
void DrawHPBar(float pos_x1, float pos_y1, float pos_x2, float pos_y2, float hp, float maxhp);

// draw segmented hp bar
void DrawHPBar2(float pos_x1, float pos_y1, float pos_x2, float pos_y2, float hp, float maxhp);
