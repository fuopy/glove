#include "world.h"

void add_wall(char x, char y, char w, char h, char style)
{
	for(int i=0; i<numWalls; ++i) {
		if(!walls[i].active) {
			walls[i].active = true;
			walls[i].x = x;
			walls[i].y = y;
			walls[i].w = w;
			walls[i].h = h;
			walls[i].style = style;
			return;
		}
	}
}

void draw_wall(Wall &obj)
{
    const unsigned char* drawSpr;
    int x, y;
    
	if(!obj.active) return;
    
    drawSpr = (unsigned char*) sprites+SPRITE_WALL + (8*obj.style);
    
    for(y = obj.y; y < obj.y+obj.h; ++y) {
        for(x = obj.x; x < obj.x+obj.w; ++x) {
            arduboy.drawBitmap(x*8+scrollx, y*8+scrolly, drawSpr, 8, 8, 1);
        }
    }
}
