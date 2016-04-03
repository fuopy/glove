#ifndef _PHYSICS_H
#define _PHYSICS_H


bool intersectSpriteSprite(short x1, short y1, short x2, short y2);
bool collideSpriteSprite(short &x1, short &y1, bool horiz, char &vel, short x2, short y2);
bool collideSpriteWall(short &x1, short &y1, bool horiz, char &vel, short x2, short y2, short w2, short h2);

#endif