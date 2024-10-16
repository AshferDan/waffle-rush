#pragma once
#include "platform.h"


int collision(struct platform plt, struct Player p) {
	float pyh = p.y + p.height;
	float pxw = p.x + p.width;
	float pltx2 = plt.x1 + plt.width;
	float plty2 = plt.y1 + plt.height;
	return (pxw >= plt.x1 && p.x <= pltx2 && pyh >= plt.y1 && p.y <= plty2);
}


float fixcollidex(struct platform plt, struct Player p) {
	if (p.x < plt.x1 + plt.width / 2) {
		return plt.x1 - p.width;
	}
	return plt.x1 + plt.width;
}


float fixcollidey(struct platform plt, struct Player p) {

	if (p.y < plt.y1) {
		return plt.y1 - p.height;
	}
	return plt.y2;
}


int collisionwhere(struct platform plt, struct Player p) {

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

int collisiontest(struct platblocks plt, struct Player p) {
	float pyh = p.y + p.height;
	float pxw = p.x + p.width;
	float pltx2 = plt.x1 + plt.w;
	float plty2 = plt.y1 + plt.h;
	return (pxw >= plt.x1 && p.x <= pltx2 && pyh >= plt.y1 && p.y <= plty2);
}

float fixcollidextest(struct platblocks plt, struct Player p) {
	if (p.x < plt.x1 + plt.w / 2) {
		return plt.x1 - p.width;
	}
	return plt.x1 + plt.w;
}


float fixcollideytest(struct platblocks plt, struct Player p) {

	if (p.y < plt.y1) {
		return plt.y1 - p.height;
	}
	return plt.y2;
}
int collisionwheretest(struct platblocks plt, struct Player p) {

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

