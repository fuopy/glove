#ifndef _BULLET_H
#define _BULLET_H
	
struct Bullet {
	short x;
	short y;
	char vx;
	char vy;
	char lifetime;
	bool active;
};

void add_bullet(short x, short y, short vx, short vy);
void update_bullet(Bullet &obj);
void draw_bullet(Bullet& obj);

#endif
