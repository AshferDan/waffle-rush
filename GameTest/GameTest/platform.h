#pragma once
#include "utils.h"


#define max_coords 16
#define max_platforms 20


int movestate; //0 = platformer, 1 = platform


#pragma region Platform structs

// coordinate struct
struct coords {
	float x, y;
};
// platform hitbox struct
struct platblocks {
	float x1, x2, y1, y2, w, h;
};

// platform struct
struct platform {
	int numcoords;
	struct coords platcoords[max_coords];
	struct platblocks blocks[max_coords];
};

struct platform Platform[max_platforms];

#pragma endregion


// make player struct
struct Player {
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
};

struct Player p; //player p

// assign platform coordinates (NOTE: to change to read from text file)
void platcoord(int plat_index, int coord_index, float x, float y);


// HITBOX LOGIC (see platform.c)
#pragma region Hitboxes

void horizontalhitbox(int coord_index, struct platform* plt);
void verticalhitbox(int coord_index, struct platform* plt);
void hitbox(int plat_index, int numplatcoords, struct platform* plt);
#pragma endregion

// COLLISION LOGIC (see platform.c)
#pragma region Collision

int collision(struct platblocks plt, struct Player p);

int collision_direction(struct platblocks plt, struct Player p);

float fix_collide_x(struct platblocks plt, struct Player p);
float fix_collide_y(struct platblocks plt, struct Player p);

void CollPlatforms(int plat_index, int numplatcoords, struct platform plt, struct Player* p, struct Player ply);
#pragma endregion 

void DrawPlatform(int plat_index);