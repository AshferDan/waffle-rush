#pragma once
#include "utils.h"
#include "hazard.h"


#define max_coords 16
#define max_platforms 20

// Platformer globals
typedef enum MoveState {
	OnPlat,
	InPlat,
	EnterPlat,
	ExitPlat,
} MoveState;

MoveState movestate;

float switchtime;

int numplats;


// STRUCTS --------------------------------------------
#pragma region Structs

	// Platform Struct
	#pragma region Platform Structs
		// InPlat
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
			int numblocks;
			coords platcoords[max_coords];
			platblocks inblocks[max_coords];
			platblocks onblocks[max_coords];
		} platform;

		// platform array
		platform Platform[max_platforms];

		// coordinate struct
	#pragma endregion Platform Structs



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

		struct Player player; //player 
	#pragma endregion Player Struct

#pragma endregion



// FUNCTIONS --------------------------------------------
#pragma region Functions

	// MOVEMENT AND MOVESTATE LOGIC
	#pragma region Movement and movestate
		// set movestate
		int start_transition(Player* ply, MoveState movestate);

		// platformer and in platform movements
		void movement(Player* p, MoveState movestate, float speed);
		#pragma endregion

	// HITBOX LOGIC (see platform.c)
	#pragma region Hitboxes
		// assign platform coordinates
		void platform_coordinates(int plat_index, int coord_index, float x, float y);
		// assign onblock coordinates
		void platform_onblocks(int plat_index, int block_index, float x1, float y1, float x2, float y2);
		// initialize horizontal hitbox
		void horizontalhitbox(int coord_index, platform* plt);
		// initialize vertical hitbox
		void verticalhitbox(int coord_index, platform* plt);
		// initialize all hitboxes for a platform
		void hitbox(int plat_index, int numplatcoords, platform* plt);
	#pragma endregion

	// COLLISION LOGIC (see platform.c)
	#pragma region Collision
		// if player and platform hitbox collides
		int collision(platblocks plt, Player p);

		int collision_direction(platblocks plt, Player p);

		float fix_collide_x(platblocks plt, Player p);
		float fix_collide_y(platblocks plt, Player p);

		void CollPlatforms(int plat_index, platform plt, Player* p, Player ply);

		void CollOnPlatforms(int plat_index, platform plt, Player* p, Player ply);
	#pragma endregion 

	// draw platforms
	void DrawPlatform(int plat_index);
#pragma endregion