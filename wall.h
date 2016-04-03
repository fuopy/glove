#ifndef _WALL_H
#define _WALL_H

struct Wall {
	char x;
	char y;
	char w;
	char h;
	bool active;
	char style;
};

void add_wall(char x, char y, char w, char h, char style);
void draw_wall(Wall &obj);

#endif
