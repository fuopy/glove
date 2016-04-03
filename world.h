#ifndef _WORLD_H
#define _WORLD_H

#include "globals.h"
#include "data.h"
#include "game.h"

#include "bullet.h"
#include "badguy.h"
#include "wall.h"
#include "key.h"
#include "treasure.h"
#include "spawner.h"
#include "exit.h"
#include "explorer.h"

const int numBullets = 3;
const int numBadguys = 20;
const int numWalls = 16;
const int numKeys = 4;
const int numTreasures = 9;
const int numSpawners = 4;
const int numExits = 4;


const short gamew = 256;
const short gameh = 128;

extern Bullet bullets[3];
extern BadGuy badguys[20];
extern Explorer p1;
extern Wall walls[16];
extern Key keys[4];
extern Treasure treasures[9];
extern Spawner spawners[4];
extern Exit exits[4];

extern short spawnx;
extern short spawny;
extern char autoFireTime;
extern char whiteScreenTime;
extern unsigned short score;
extern short rollingScore;
extern unsigned short rollingHealth;
extern unsigned char currentLevel;
extern unsigned char levelsCompleted;
extern unsigned short gameTime;
extern short gameTimeTick;
extern bool quitGame;
extern short scrollx;
extern short scrolly;
extern char BadGuy_UpdateDelay;

void worldLoadLevel();
void worldClearLevel();

#endif
