#include "physics.h"

#define WIDTH 8
#define HEIGHT 8

bool intersectSpriteSprite(short x1, short y1, short x2, short y2)
{
	return ((x1 < x2+WIDTH) &&
		(x1+WIDTH > x2) &&
		(y1 < y2+HEIGHT) &&
		(y1+HEIGHT > y2));
}

bool collideSpriteSprite(short &x1, short &y1, bool horiz, char &vel, short x2, short y2)
{
	if( (x1 < x2+WIDTH) &&
		(x1+WIDTH > x2) &&
		(y1 < y2+HEIGHT) &&
		(y1+HEIGHT > y2))
	{
		if(horiz)
		{
			if(vel < 0)
			{
				x1 = x2+WIDTH;
			}
			else
			{
				x1 = x2-WIDTH;
			}
		}
		else
		{
			if(vel < 0)
			{
				y1 = y2+HEIGHT;
			}
			else
			{
				y1 = y2-HEIGHT;
			}
		}
		vel = 0;
		return true;
	}
	return false;
}

bool collideSpriteWall(short &x1, short &y1, bool horiz, char &vel, short x2, short y2, short w2, short h2)
{
	if( (x1 < x2+w2) &&
	(x1+WIDTH > x2) &&
	(y1 < y2+h2) &&
	(y1+HEIGHT > y2))
	{
		if(horiz)
		{
			if(vel < 0)
			{
				x1 = x2+w2;
			}
			else
			{
				x1 = x2-WIDTH;
			}
		}
		else
		{
			if(vel < 0)
			{
				y1 = y2+h2;
			}
			else
			{
				y1 = y2-HEIGHT;
			}
		}
		vel = 0;
		return true;
	}
	return false;
}
