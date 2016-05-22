#include "globals.h"
#include "prompt.h"
#include "save.h"

#define TONE_BACK 400

void displayRecords()
{
	int address = GAME_SAVE_FILE * 10 * 5;
	
	arduboy.clear();
	arduboy.setCursor(0, 0);
	arduboy.print(F("     - Records -     "));
	arduboy.setCursor(0, 8*2);
	arduboy.print(F("Name Score Time  #Rms"));
	
	byte hi;
	byte lo;
	short val;
	// Loop through scores
	int scoreAddress;
	
	for(char i=0; i<3; ++i) {
		scoreAddress = 20 + (i*10) + address;
		
		hi = EEPROM.read(scoreAddress+FILE_NAME);
		arduboy.setCursor(0, 8*(3+i));
		arduboy.print(char(hi));
		hi = EEPROM.read(scoreAddress+FILE_NAME+1);
		arduboy.setCursor(6*1, 8*(3+i));
		arduboy.print(char(hi));
		hi = EEPROM.read(scoreAddress+FILE_NAME+2);
		arduboy.setCursor(6*2, 8*(3+i));
		arduboy.print(char(hi));
		hi = EEPROM.read(scoreAddress+FILE_NAME+3);
		arduboy.setCursor(6*3, 8*(3+i));
		arduboy.print(char(hi));
		
		hi = EEPROM.read(scoreAddress+FILE_SCORE);
		lo = EEPROM.read(scoreAddress+FILE_SCORE+1);
		val = (hi << 8) | lo;
		arduboy.setCursor(6*5, 8*(3+i));
		arduboy.print(val);
		if(val>0) arduboy.print("00");
		
		hi = EEPROM.read(scoreAddress+FILE_TIME);
		lo = EEPROM.read(scoreAddress+FILE_TIME+1);
		val = (hi << 8) | lo;
		arduboy.setCursor(6*11, 8*(3+i));
		//arduboy.print(val);
		printTime(val);
		
		hi = EEPROM.read(scoreAddress+FILE_LEVEL);
		arduboy.setCursor(6*17, 8*(3+i));
		arduboy.print(hi);
	}
	arduboy.setCursor(0, 8*7);
	
	arduboy.print(F("ROOMS CLEARED: "));
	arduboy.print(getRoomClearPercentage());
	arduboy.print("%");
	
	arduboy.display();
	
	tautInput();
	while(true) {
		delay(10);
		updateInput();
		if(B_PRESSED || A_PRESSED) {
			arduboy.tunes.tone(TONE_BACK, 20);
			break;
		}
	}
}
