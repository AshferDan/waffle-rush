#pragma once
#include "utils.h"

//// platform struct
//struct platform {
//	float x1, x2, y1, y2; // positions
//	float width, height; // size
//};

#define max_coords 16
#define max_platforms 20

struct coords {
	float x, y;
};

struct platblocks {
	float x1, x2, y1, y2, w, h;
};



// test platform struct
struct platform {
	int numcoords;
	struct coords platcoords[max_coords];
	struct platblocks blocks[max_coords];
};


struct platform Platform[max_platforms];

// make player struct
struct Player {
	float x; //posx
	float y; //posy
	float movex; //movex
	float movey; //movey
	float hp; //health
	float width;
	float height;
	CP_Color color; //color
};



// check collide

// fix collide


int collision(struct platblocks plt, struct Player p);

float fix_collide_x(struct platblocks plt, struct Player p);
float fix_collide_y(struct platblocks plt, struct Player p);

int collision_direction(struct platblocks plt, struct Player p);

void platcoord(int plat_index, int coord_index, float x, float y);

void horizontalhitbox(int coord_index, struct platform* plt);
void verticalhitbox(int coord_index, struct platform* plt);
void hitbox(int plat_index, int numplatcoords, struct platform* plt);