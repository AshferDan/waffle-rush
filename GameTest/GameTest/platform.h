#pragma once
#include "utils.h"

// platform struct
struct platform {
	float x1, x2, y1, y2; // positions
	float width, height; // size
};

#define max_coords 15

struct coords {
	float x, y;
};

struct platblocks {
	float x1, x2, y1, y2, w, h;
};

// test platform struct
struct platform2 {
	int numcoords;
	struct coords platcoords[max_coords];
	struct platblocks blocks[max_coords];
};

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
int collision(struct platform plt, struct Player p);

// fix collide
//float fixcollidex(float pltx, float plty, float pltw, float plth, float px, float py, float pw, float ph);
float fixcollidex(struct platform plt, struct Player p);

float fixcollidey(struct platform plt, struct Player p);

int collisionwhere(struct platform plt, struct Player p);


int collisiontest(struct platblocks plt, struct Player p);

float fixcollidextest(struct platblocks plt, struct Player p);
float fixcollideytest(struct platblocks plt, struct Player p);

int collisionwheretest(struct platblocks plt, struct Player p);
