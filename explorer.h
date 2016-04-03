#ifndef _EXPLORER_H
#define _EXPLORER_H

struct Explorer {
	short x;
	short y;
	char direction;
	bool frame;
	char frameTime;
	bool active;
	short health;
	char nextHealthDecrease;
};
void initialize_explorer(Explorer& obj);
void update_explorer(Explorer& obj);
void draw_explorer(Explorer& obj);
void damage_explorer(Explorer& obj, short dmg);

#endif
