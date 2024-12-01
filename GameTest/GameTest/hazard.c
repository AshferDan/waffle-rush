#pragma once
#include "globals.h"

int crusher_direction(hazard crusher, Player p) {

		// assign player center xy coordinates
		float px = (p.x + p.width / 2);
		float py = (p.y + p.height / 2);
		// how much the player goes into the platform
		float leftcoll = (float)(fabs)((px + p.width/2) - crusher.x[0]);
		float rightcoll = (float)(fabs)(crusher.x[1] - (px - p.width / 2));
		float topcoll = (float)(fabs)((py + p.height/2) - crusher.y[0]);
		float botcoll = (float)(fabs)(crusher.y[2] - (py - p.height / 2));

		// return lower value for horizontal/vertical
		float horizontal = (leftcoll < rightcoll) ? leftcoll : rightcoll;
		float vertical = (topcoll < botcoll) ? topcoll : botcoll;

		// horizontal = 1, vertical = 2
		return (horizontal < vertical) ? 1 : 2;
	}

void reset_hazards() {
	for (int i = 0; i < MAX_BULLETS; i++) {
		bullets[i].x = 0;
		bullets[i].y = 0;
		bullets[i].active = false;
	}

    for (int i = 0; i < MAX_TRAPS; i++) {
        for (int j = 0; j < 3; j++) {
            traps[i].x[j] = 0;
            traps[i].y[j] = 0;
        }
        traps[i].type = 0;
    }
}

void init_hazards(FILE* HazardFile, int numberoftraps) {
    for (int hazard_index = 0; hazard_index < numberoftraps; ++hazard_index) {
        fscanf_s(HazardFile, "%d", &traps[hazard_index].type);
        switch (traps[hazard_index].type)
        {
        case spike:
        {
			for (int coordinate_index = 0; coordinate_index < 3; ++coordinate_index)
			{
				fscanf_s(HazardFile, "%f %f", &traps[hazard_index].x[coordinate_index], &traps[hazard_index].y[coordinate_index]);
			}
			fscanf_s(HazardFile, "%d", &traps[hazard_index].direction);
			break;
            
        }
        case crusher:
        {
            for (int coordinate_index = 0; coordinate_index < 3; ++coordinate_index)
            {
                fscanf_s(HazardFile, "%f %f", &traps[hazard_index].x[coordinate_index], &traps[hazard_index].y[coordinate_index]);
            }
            break;
        }
        case shooter:
        {
            for (int coordinate_index = 0; coordinate_index < 3; ++coordinate_index)
            {
                fscanf_s(HazardFile, "%f %f", &traps[hazard_index].x[coordinate_index], &traps[hazard_index].y[coordinate_index]);
            }
            break;
        }
        }
    }
}

void hazard_update() {

	for (int trap_index = 0; trap_index < numberoftraps; trap_index++) {
		switch (traps[trap_index].type) {
		case spike: {
			
			switch (traps[trap_index].direction) {
			case 0: {
				if (AreSquaresIntersecting(player.x, player.y, player.width, player.height, traps[trap_index].x[0], (traps[trap_index].y[0]+10.f), traps[trap_index].x[1] - traps[trap_index].x[0], traps[trap_index].y[2] - (traps[trap_index].y[0]+10.f)) && !(player.state == Dead || player.state == Spawning) && !((buffstate & 0b100) && Buff[invulBuff].buffduration > 0.00f)) {
					Kill_Player(&player, Burn, &deaths, &buffstate);
				}
				break;
			}
			case 1: {
				if (AreSquaresIntersecting(player.x, player.y, player.width, player.height, traps[trap_index].x[0], traps[trap_index].y[0], (traps[trap_index].x[1]-10.f) - traps[trap_index].x[0], traps[trap_index].y[2] - traps[trap_index].y[0]) && !(player.state == Dead || player.state == Spawning) && !((buffstate & 0b100) && Buff[invulBuff].buffduration > 0.00f)) {
					Kill_Player(&player, Burn, &deaths, &buffstate);
				}
				break;
			}
			case 2: {
				if (AreSquaresIntersecting(player.x, player.y, player.width, player.height, traps[trap_index].x[0], traps[trap_index].y[0], traps[trap_index].x[1] - traps[trap_index].x[0], (traps[trap_index].y[2]-10.f) - traps[trap_index].y[0]) && !(player.state == Dead || player.state == Spawning) && !((buffstate & 0b100) && Buff[invulBuff].buffduration > 0.00f)) {
					Kill_Player(&player, Burn, &deaths, &buffstate);
				}
				break;
			}
			case 3: {
				if (AreSquaresIntersecting(player.x, player.y, player.width, player.height, (traps[trap_index].x[0]+10.f), traps[trap_index].y[0], traps[trap_index].x[1] - (traps[trap_index].x[0]+10.f), traps[trap_index].y[2] - traps[trap_index].y[0]) && !(player.state == Dead || player.state == Spawning) && !((buffstate & 0b100) && Buff[invulBuff].buffduration > 0.00f)) {
					Kill_Player(&player, Burn, &deaths, &buffstate);
				}
				break;
			}
			}
			break;
			
		}
		case crusher: {
			float crushervely;
			//CRUSHER MOVEMENT
			// crusherstate = 0 if going down and crusherstate = 1 when going up
			if (crusherstate == 0) {
				crushervely = 1000.f * dt;
				traps[trap_index].y[2] += crushervely;
				if (traps[trap_index].y[2] > traps[trap_index].y[1]) {
					traps[trap_index].y[2] = traps[trap_index].y[1];
					crusherstate = 1;
				}
				// if the player hits the crusher at the bottom, add death and reset
				if (AreSquaresIntersecting(player.x, player.y, player.width, player.height, traps[trap_index].x[0], traps[trap_index].y[0], traps[trap_index].x[1] - traps[trap_index].x[0], traps[trap_index].y[2] - traps[trap_index].y[0]) && !(player.state == Dead || player.state == Spawning) && !((buffstate & 0b100) && Buff[invulBuff].buffduration > 0.00f)) {
					if (crusher_direction(traps[trap_index], player) == 1) {
						if (player.x >= ((traps[trap_index].x[1] + traps[trap_index].x[0]) / 2.f)) {
							player.x = traps[trap_index].x[1];
							player.movex = 0;
						}
						else if (player.x <= ((traps[trap_index].x[1] + traps[trap_index].x[0]) / 2.f)) {
							player.x = traps[trap_index].x[0] - player.width;
							player.movex = 0;
						}
					}
					else if (crusher_direction(traps[trap_index], player) == 2) {
						player.y = traps[trap_index].y[2];
						player.movey = 0;
						if ((player.y + player.height + 30) >= traps[trap_index].y[1]) {
							player.y = (traps[trap_index].y[1] - player.height - 15);
							Kill_Player(&player, Crush, &deaths, &buffstate);
						}
					}

				}
			}
			if (crusherstate == 1) {
				crushervely = -100.0f * dt;
				traps[trap_index].y[2] += crushervely;
				if (traps[trap_index].y[2] < traps[trap_index].y[0]) {
					traps[trap_index].y[2] = traps[trap_index].y[0];
					crusherstate = 0;
				}
				//if the player hits the crusher as it goes up, no death but cant go in
				if (AreSquaresIntersecting(player.x, player.y, player.width, player.height, traps[trap_index].x[0], traps[trap_index].y[0], traps[trap_index].x[1] - traps[trap_index].x[0], traps[trap_index].y[2] - traps[trap_index].y[0]) && !(player.state == Dead || player.state == Spawning) && !((buffstate & 0b100) && Buff[invulBuff].buffduration > 0.00f)) {
					if (crusher_direction(traps[trap_index], player) == 1) {
						if (player.x >= ((traps[trap_index].x[1] + traps[trap_index].x[0]) / 2.f)) {
							player.x = traps[trap_index].x[1];
							player.movex = 0;
						}
						else if (player.x <= ((traps[trap_index].x[1] + traps[trap_index].x[0]) / 2.f)) {
							player.x = traps[trap_index].x[0] - player.width;
							player.movex = 0;
						}
					}
					else if (crusher_direction(traps[trap_index], player) == 2) {
						player.y = traps[trap_index].y[2];
						player.movey = 0;
					}

				}
			}
			break;
		}
		default: {}
		}
	}
}

void Draw_Hazards() {
	// BULLET DRAWING
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255)); // Red color
	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (bullets[i].active) {
			//CP_Graphics_DrawRect(bullets[i].x - camera.worldshiftx, bullets[i].y - camera.worldshifty, BULLET_SIZE, BULLET_SIZE);
			float draw_posx = bullets[i].x - 5 - camera.worldshiftx;
			float draw_posy = bullets[i].y - 25 - camera.worldshifty;
			float displaysprite_x2 = ((int)player.anim % 3 == 0) ? 0.0f : 7.0f;
			float displaysprite_x3 = ((int)player.anim % 3 == 0) ? 7.0f : 14.0f;
			CP_Image_DrawSubImageAdvanced(effects, draw_posx, draw_posy + 20, player.width + 20, player.height + 5, displaysprite_x2, 11, displaysprite_x3, 16, 255, 0);
		}
	}

	// TRAP DRAWING
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	firetimer += 0.25;
	if (firetimer > 15) {
		firetimer = 0;
	}
	float sprite_x = (int)firetimer * 32.0f;

	for (int i = 0; i < numberoftraps; ++i)
	{
		switch (traps[i].type)
		{
		case spike:
		{
			CP_Image_DrawSubImageAdvanced(fire_sprite, traps[i].x[0] - camera.worldshiftx, traps[i].y[0] - camera.worldshifty, 50.0f, 50.0f, sprite_x, 0.0f, sprite_x + 32.0f, 32.0f, 255, 90.0f * traps[i].direction);
			break;
		}
		case crusher:
		{
			CP_Graphics_DrawRect(traps[i].x[0] - camera.worldshiftx, traps[i].y[0] - camera.worldshifty, traps[i].x[1] - traps[i].x[0], traps[i].y[2] - traps[i].y[0]);
			break;
		}
		case shooter:
		{
			CP_Graphics_DrawRect(traps[i].x[0] - camera.worldshiftx, traps[i].y[0] - camera.worldshifty, traps[i].x[1] - traps[i].x[0], traps[i].y[2] - traps[i].y[0]);
			break;
		}

		}
	}
}