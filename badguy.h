#ifndef _BADGUY_H
#define _BADGUY_H

struct BadGuy {
	short x;
	short y;
	bool active;
};

void add_badguy(short x, short y);
void update_badguy(BadGuy &b);
void draw_badguy(BadGuy &b);
void destroy_badguy(BadGuy &obj);

#endif
