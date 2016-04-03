#ifndef _EXIT_H
#define _EXIT_H

struct Exit{
	char x;
	char y;
	char dest;
	bool active;
};

void add_exit(char x, char y, char dest);
void draw_exit(Exit &obj);
void activate_exit(Exit& obj);

#endif
