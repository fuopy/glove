#include "save.h"
#include "world.h"

void add_exit(char x, char y, char dest)
{
	for(int i=0; i<numSpawners; ++i) {
		if(!exits[i].active) {
			exits[i].active = true;
			exits[i].x = x;
			exits[i].y = y;
			exits[i].dest = dest;
			return;
		}
	}
}

void draw_exit(Exit& obj)
{
    const unsigned char* drawSpr = (unsigned char*) sprites+SPRITE_EXIT;
	if(obj.active)
		arduboy.drawBitmap(obj.x*8+scrollx, obj.y*8+scrolly, drawSpr, 8, 8, 1);	
}

void activate_exit(Exit& obj)
{
	levelsCompleted++;
	if(!quitGame)
	{
		// If playing RANDOM mode
		if(GameMode == GAME_MODE_RANDOM){
			gameGotoLevel(random(0,numLevels-1));
		// In any other mode
		} else {			
			// Mark this room as cleared in save file
			markRoomAsCleared(currentLevel);
			gameGotoLevel(obj.dest);
		}
	}
}
