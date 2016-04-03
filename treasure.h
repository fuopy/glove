#ifndef _TREASURE_H
#define _TREASURE_H

struct Treasure {
	char x;
	char y;
	char type;
	bool active;
};
void add_treasure(char x, char y, char type);
void draw_treasure(Treasure& obj);
void activate_treasure(Treasure& obj);

#endif
