#ifndef _KEY_H
#define _KEY_H

struct Key {
	char x;
	char y;
	unsigned char target;
	bool active;
};

void add_key(char x, char y, unsigned char target);
void draw_key(Key & obj);
void activate_key(Key& obj);

#endif
