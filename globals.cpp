#include "globals.h"

Arduboy arduboy;

bool old_a = false;
bool old_b = false;
bool old_up = false;
bool old_down = false;
bool old_left = false;
bool old_right = false;

bool new_a = false;
bool new_b = false;
bool new_up = false;
bool new_down = false;
bool new_left = false;
bool new_right = false;

char progmemString[] = "";

unsigned char GameMode = GAME_MODE_GLOVE;
int GameSaveOffset = GAME_GLOVE_OFFSET;

void tautInput()
{
	new_a = true;
	new_b = true;
	new_up = true;
	new_down = true;
	new_left = true;
	new_right = true;
}

void updateInput()
{
	old_a = new_a;
	old_b = new_b;
	old_up = new_up;
	old_down = new_down;
	old_left = new_left;
	old_right = new_right;
	
	new_a = arduboy.pressed(B_BUTTON);
	new_b = arduboy.pressed(A_BUTTON);
	new_up = arduboy.pressed(UP_BUTTON);
	new_down = arduboy.pressed(DOWN_BUTTON);
	new_left = arduboy.pressed(LEFT_BUTTON);
	new_right = arduboy.pressed(RIGHT_BUTTON);
}

char* rps(const char* const* str)
{
	strcpy_P(progmemString, (char*)pgm_read_word(str));
	return progmemString;
}

char* dps(const char* str)
{
	strcpy_P(progmemString, (char*)pgm_read_word(str));
	return progmemString;
}

char* eps(char* str)
{
	strcpy_P(progmemString, str);
    return progmemString;
}

char* spsn(int addr, unsigned char len)
{
	int offset;
	
	progmemString[0] = '\0';
	
	for(offset = 0; offset < len; offset++)
	{
		progmemString[offset] = EEPROM.read(addr+offset);	
	}
	progmemString[offset] = '\0';
	
    return progmemString;
}


void printTime(unsigned short time)
{
	short mins = time/60;
	short secs = time%60;
	
	if(mins < 10) arduboy.print('0');
	arduboy.print(mins);
	arduboy.print(':');
	if(secs < 10) arduboy.print('0');
	arduboy.print(secs);
		
}

short EEPROMReadShort(int addr)
{
	byte hi = EEPROM.read(addr+FILE_SCORE);
	byte lo = EEPROM.read(addr+FILE_SCORE+1);
	return (hi << 8) | lo;
}