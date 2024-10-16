#pragma once
#include "platform.h"




// am i colliding
int collision(struct platblocks plt, struct Player p) {
	float pyh = p.y + p.height;
	float pxw = p.x + p.width;
	float pltx2 = plt.x1 + plt.w;
	float plty2 = plt.y1 + plt.h;
	return (pxw >= plt.x1 && p.x <= pltx2 && pyh >= plt.y1 && p.y <= plty2);
}

// fix x position
float fix_collide_x(struct platblocks plt, struct Player p) {
	if (p.x + p.width/2 < plt.x1 + plt.w / 2) { // is player left of platform
		return plt.x1 - p.width; // throw left of platform
	}
	return plt.x1 + plt.w; // throw right of platform
}

// fix y position
float fix_collide_y(struct platblocks plt, struct Player p) {

	if (p.y + p.height/2 < plt.y1) { // is player above platform
		return plt.y1 - p.height; // throw up of platform
	}
	return plt.y2; // throw bottom of platform
}
int collision_direction(struct platblocks plt, struct Player p) {

	//left right up down
	float px2 = (p.x + p.width);
	float py2 = (p.y + p.height);
	float leftcoll = px2 - plt.x1;
	float rightcoll = plt.x2 - p.x;
	float topcoll = py2 - plt.y1;
	float botcoll = plt.y2 - p.y;

	float horizontal = (leftcoll < rightcoll) ? leftcoll : rightcoll;
	float vertical = (topcoll < botcoll) ? topcoll : botcoll;

	// horizontal = 1, vertical = 2
	return (horizontal < vertical) ? 1 : 2;

}


void platcoord(int plat_index, int coord_index, float x, float y) {
	Platform[plat_index].platcoords[coord_index] = (struct coords){ x,y };
}

void horizontalhitbox(int coord_index, struct platform* plt) {
	if (plt->platcoords[coord_index + 1].x > plt->platcoords[coord_index].x) {		// if next coordx > current coordx
		plt->blocks[coord_index] = (struct platblocks){
			plt->platcoords[coord_index].x + 10,
			plt->platcoords[coord_index + 1].x - 10,
			plt->platcoords[coord_index].y - 10,
			plt->platcoords[coord_index].y + 10,
			(plt->platcoords[coord_index + 1].x - 10) - (plt->platcoords[coord_index].x + 10),
			20
		};
	}
	else {																			// if next coordx < current coordx
		plt->blocks[coord_index] = (struct platblocks){		
			plt->platcoords[coord_index + 1].x + 10,
			plt->platcoords[coord_index].x - 10,
			plt->platcoords[coord_index].y - 10,
			plt->platcoords[coord_index].y + 10,
			(plt->platcoords[coord_index].x - 10) - (plt->platcoords[coord_index + 1].x + 10),
			20
		};
	}

	printf("hitbox hori: index %d, x1 %f, x2 %f, y1 %f, y2 %f\n", plt->blocks[coord_index].x1, plt->blocks[coord_index].x2, plt->blocks[coord_index].y1, plt->blocks[coord_index].y2);
}

void verticalhitbox(int coord_index, struct platform* plt) {
	if (coord_index != plt->numcoords - 1) {										// if not last coord
		if (plt->platcoords[coord_index+1].y > plt->platcoords[coord_index].y) {	// if next coordy > current coordy
			plt->blocks[coord_index] = (struct platblocks){
				plt->platcoords[coord_index].x - 10,
				plt->platcoords[coord_index].x + 10,
				plt->platcoords[coord_index].y - 10,
				plt->platcoords[coord_index + 1].y + 10,
				20,
				(plt->platcoords[coord_index + 1].y + 10) - (plt->platcoords[coord_index].y - 10)
			};
		}
		else {																		// if next coordy < current coordy
			plt->blocks[coord_index] = (struct platblocks){
				plt->platcoords[coord_index].x - 10,
				plt->platcoords[coord_index].x + 10,
				plt->platcoords[coord_index].y + 10,
				plt->platcoords[coord_index + 1].y - 10,
				20,
				(plt->platcoords[coord_index + 1].y - 10) - (plt->platcoords[coord_index].y + 10)
			};

		}
	}
	else {																			// if last coord
			plt->blocks[coord_index] = (struct platblocks){
			plt->platcoords[0].x - 10,
			plt->platcoords[coord_index].x + 10,
			plt->platcoords[0].y - 10,
			plt->platcoords[coord_index].y + 10,
			20,
			(plt->platcoords[coord_index].y + 10) - (plt->platcoords[0].y - 10)
		};
	}
	printf("hitbox vert: index %d, x1 %f, x2 %f, y1 %f, y2 %f\n", plt->blocks[coord_index].x1, plt->blocks[coord_index].x2, plt->blocks[coord_index].y1, plt->blocks[coord_index].y2);
}

void hitbox(int plat_index, int numplatcoords, struct platform* plt) {
	int i = 0;
	printf("hitbox init: i = %d, platform %d coords %d\n", i, plat_index, plt[plat_index].numcoords);
	while (i <numplatcoords) {
		printf("hitbox loop: i %d, plat_index %d, numcoords %d\n", i, plat_index, numplatcoords);
		if (i % 2 == 0 && i < numplatcoords - 1) { //horizontal & not last coord
			horizontalhitbox(i, &plt[plat_index]);
		}
		else { //vertical
			verticalhitbox(i, &plt[plat_index]);
		}
		i++;
	}

}