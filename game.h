#ifndef _GAME_H
#define _GAME_H

#include "data.h"

void displayGame();
void saveGame(unsigned char file);

void gameGotoLevel(unsigned char level);
void doGameComplete();
void doGameOver();
void flashScreen();
void addScore(short points);

void gameSetup();
void gameLoop();

#endif
