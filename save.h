#ifndef _SAVE_H
#define _SAVE_H

#include "world.h"
#include "globals.h"

#define GAME_SAVE_FILE 6 // Save file for use with the game

extern bool validSave;

void saveSetup();
bool checkFileValidity(byte file);
void breakSave(byte file);
void initializeSave(byte file);
int getRoomClearPercentage();
bool saveHighScore();
void markRoomAsCleared(unsigned char room);
void deleteContinueSave();
void displayLoadGame(unsigned char file);

#endif
