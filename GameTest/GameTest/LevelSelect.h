//---------------------------------------------------------
// file:	game.h
// author:	TAN JUN QUAN
// email:	t.junquan@digipen.edu
//
// brief:	Declarations of game stage
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "game.h"
#include "Level1.h"

// leevl struct
typedef struct Level {
	int level_no;
	int isUnlocked;
	int isCleared;
} Level;

// number of levels = 5
Level levels[5];

void LSelect_Init(void);
void LSelect_Update(void);
void LSelect_Exit(void);
