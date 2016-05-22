#ifndef _SAVE_H
#define _SAVE_H

#include "world.h"
#include "globals.h"

extern bool validSave;

void saveSetup();
void saveCreate();
bool checkFileValidity(byte file);
void breakSave(byte file);
void initializeSave(byte file);
int getRoomClearPercentage();
short getCurrentLevelProgress();
bool saveHighScore();
void markRoomAsCleared(unsigned char room);
void deleteContinueSave();
void displayLoadGame(unsigned char file);
void clearAllRooms();
byte readAdvance(int &address);

#endif
