#pragma once
#include "platform.h"


// Coordinates (NOTE: to be changed to read from text file)
void platcoord(int plat_index, int coord_index, float x, float y) {
	Platform[plat_index].platcoords[coord_index] = (struct coords){ x,y };
}

	// HITBOX LOGIC
	/*---------------------------------------------------------------------------------------------------*/
#pragma region Hitboxes

// determines platform horizontal hitboxes, used in hitbox function below
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
}

// determines platform vertical hitboxes, used in hitbox function below
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
				plt->platcoords[coord_index + 1].y - 10,
				plt->platcoords[coord_index].y + 10,
				20,
				(plt->platcoords[coord_index].y + 10) - (plt->platcoords[coord_index+1].y - 10)
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
}

// determines all hitboxes of platforms, use in a loop with number of total platforms per level
// e.g :
//		for (int plat_index = 0; plat_index < numplats; plat_index++) {
//			hitbox(plat_index, Platform[plat_index].numcoords, &Platform[plat_index]);
//		}
//
void hitbox(int plat_index, int numplatcoords, struct platform* plt) {

	for (int coord_index = 0; coord_index < Platform[plat_index].numcoords; coord_index++) {
		if (coord_index % 2 == 0 && coord_index < Platform[plat_index].numcoords - 1) { //horizontal & not last coord
			horizontalhitbox(coord_index, &Platform[plat_index]);
		}
		else { //vertical
			verticalhitbox(coord_index, &Platform[plat_index]);
		}
	}
}

#pragma endregion


	// COLLISION LOGIC
	/*---------------------------------------------------------------------------------------------------*/
#pragma region Collision and repositions

// am i colliding
int collision(struct platblocks plt, struct Player p) {
	float pyh = p.y + p.height;
	float pxw = p.x + p.width;
	float pltx2 = plt.x1 + plt.w;
	float plty2 = plt.y1 + plt.h;
	return (pxw >= plt.x1 && p.x <= pltx2 && pyh >= plt.y1 && p.y <= plty2);
}

// checks if collision is vertical or horizontal
int collision_direction(struct platblocks plt, struct Player p) {

	// assign player x2 and y2 coordinates
	float px2 = (p.x + p.width);
	float py2 = (p.y + p.height);
	// how much the player goes into the platform
	float leftcoll = px2 - plt.x1;
	float rightcoll = plt.x2 - p.x;
	float topcoll = py2 - plt.y1;
	float botcoll = plt.y2 - p.y;

	// return lower value for horizontal/vertical
	float horizontal = (leftcoll < rightcoll) ? leftcoll : rightcoll;
	float vertical = (topcoll < botcoll) ? topcoll : botcoll;

	// horizontal = 1, vertical = 2
	return (horizontal < vertical) ? 1 : 2;

}

// fix x position
float fix_collide_x(struct platblocks plt, struct Player p) {
	if (p.x + p.width / 2 < plt.x1 + plt.w / 2) { // is player left of platform
		return plt.x1 - p.width; // throw left of platform
	}
	return plt.x1 + plt.w; // throw right of platform
}

// fix y position
float fix_collide_y(struct platblocks plt, struct Player p) {
	if (p.y + p.height / 2 < plt.y1) { // is player above platform
		return plt.y1 - p.height; // throw up of platform
	}
	return plt.y2; // throw bottom of platform
}

// fixes player position in relation to platform hitboxes
// e.g:
//		for (int plat_index = 0; plat_index < numplats; plat_index++) {
//			CollPlatforms(plat_index, Platform[plat_index].numcoords, Platform[plat_index], &p, p);
//		}
// 
void CollPlatforms(int plat_index, int numplatcoords, struct platform plt, struct Player* p, struct Player ply) {
	// iterate through number of coordinates
	for (int coord_index = 0; coord_index < Platform[plat_index].numcoords; coord_index++) {
		// check for collision
		if (collision(Platform[plat_index].blocks[coord_index], ply)) {
			// check if collision is from vertical and not horizontal
			if (collision_direction(Platform[plat_index].blocks[coord_index], ply) == 2) { // if colliding vertically
				if (ply.x < Platform[plat_index].blocks[coord_index].x2 && ply.x + ply.width > Platform[plat_index].blocks[coord_index].x1) {  // if player within x coords of platform 

					p->y = fix_collide_y(Platform[plat_index].blocks[coord_index], ply);

					// if player on platform
					if ((p->y + ply.height) == Platform[plat_index].blocks[coord_index].y1) {
						p->onplatform = 1; // on platform!
						if (ply.x >= Platform[plat_index].blocks[coord_index].x1 && ply.x + ply.width <= Platform[plat_index].blocks[coord_index].x2) {
							p->withinx = 1;
						}
					}
					// two conditions to set player vertical velocity 0:
					// 1) if player is on top of platform and travelling downwards
					// 2) if player bumps bottom of platform and travelling upwards
					if (ply.y < Platform[plat_index].blocks[coord_index].y1 && ply.movey > 0 || ply.y > Platform[plat_index].blocks[coord_index].y1 && ply.movey < 0) { p->movey = 0; }

					// end if player within x coords of platform
				}
				// end if colliding vertically
			}
			// if player is outside x coords of platform
			// aka player is colliding from the sides
			else p->x = fix_collide_x(Platform[plat_index].blocks[coord_index], ply);
		}// end if collision check
	}
}
#pragma endregion

void DrawPlatform(int plat_index) {
	CP_Graphics_BeginShape();
	for (int i = 0; i <= Platform[plat_index].numcoords - 1; i++) {
		CP_Graphics_AddVertex(Platform[plat_index].platcoords[i].x, Platform[plat_index].platcoords[i].y);
	}
	CP_Graphics_EndShape();
}