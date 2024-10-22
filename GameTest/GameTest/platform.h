#pragma once
#include "utils.h"


#define max_coords 16
#define max_platforms 20

// Platformer globals
int movestate; //0 = platformer, 1 = platform
float switchtime;


// STRUCTS --------------------------------------------
#pragma region Structs
// Platform Struct
#pragma region Platform structs

// coordinate struct
typedef struct coords {
	float x, y;
} coords;
// platform hitbox struct
typedef struct platblocks {
	float x1, x2, y1, y2, w, h;
} platblocks;

// platform struct
typedef struct platform {
	int numcoords;
	coords platcoords[max_coords];
	platblocks blocks[max_coords];
} platform;

platform Platform[max_platforms];

#pragma endregion

// Player Struct
#pragma region Player Struct
typedef struct Player {
	float x; //posx
	float y; //posy
	float movex; //movex
	float movey; //movey
	float hp; //health (NOTE: change to lives)
	float width;
	float height;
	float speed;
	int onplatform;
	int withinx;
	int leaveplatform;
	CP_Color color; //color
} Player;

struct Player player; //player p
#pragma endregion

#pragma endregion



// FUNCTIONS --------------------------------------------
#pragma region Functions
// assign platform coordinates (NOTE: to change to read from text file)
void platform_coordinates(int plat_index, int coord_index, float x, float y);

// MOVEMENT AND MOVESTATE LOGIC
#pragma region Movement and movestate
// set movestate
int movestate_set(Player* p, int movestate);
int start_transition(Player* ply, int movestate);

//end_transition(Player* ply, float dt, int movestate);
// platformer and in platform movements
void movement(Player* p, int movestate, float speed);
#pragma endregion

// HITBOX LOGIC (see platform.c)
#pragma region Hitboxes
void horizontalhitbox(int coord_index, platform* plt);
void verticalhitbox(int coord_index, platform* plt);
void hitbox(int plat_index, int numplatcoords, platform* plt);
#pragma endregion

// COLLISION LOGIC (see platform.c)
#pragma region Collision

int collision(platblocks plt, Player p);

int collision_direction(platblocks plt, Player p);

float fix_collide_x(platblocks plt, Player p);
float fix_collide_y(platblocks plt, Player p);

void CollPlatforms(int plat_index, int numplatcoords, platform plt, Player* p, Player ply);
#pragma endregion 

// draw platforms
void DrawPlatform(int plat_index);
#pragma endregion