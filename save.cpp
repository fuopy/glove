#include "save.h"
#include "records.h"
#include "prompt.h"
#include "game.h"

bool validSave;

byte readAdvance(int &address)
{
	byte val = EEPROM.read(address);
	address++;
	return val;
}

void saveSetup()
{
    validSave = checkFileValidity(GAME_SAVE_FILE);
}

void saveCreate()
{
	if(!validSave)
		initializeSave(GAME_SAVE_FILE);
	
	validSave = true;
}

bool checkFileValidity(byte file)
{
	int address = GameSaveOffset + FILE_VALID;
	
	/*
	char* checkStr = "LoMeM";
	unsigned char checkIndex;
	
	for(checkIndex = 0; checkIndex <= 5; ++checkIndex)
	{
		if(readAdvance(address) != checkStr[checkIndex])
			return false;
	}
	
	return true;
	*/
	
	
	if((EEPROM.read(address+FILE_VALID) == 'L')
		&& (EEPROM.read(address+FILE_VALID+1) == 'o')
		&& (EEPROM.read(address+FILE_VALID+2) == 'M')
		&& (EEPROM.read(address+FILE_VALID+3) == 'e')
		&& (EEPROM.read(address+FILE_VALID+4) == 'M'))
	{
		return true;
	}
	return false;
	
}


void breakSave(byte file)
{
	int address = GameSaveOffset;
	
	// Write game identity
	EEPROM.write(address+FILE_VALID, 'L');
	EEPROM.write(address+FILE_VALID+1, 'o');
	EEPROM.write(address+FILE_VALID+2, 'M');
	EEPROM.write(address+FILE_VALID+3, 'e');
	EEPROM.write(address+FILE_VALID+4, 'q');
}

void initializeSave(byte file)
{
	int address = GameSaveOffset;
	int offset;
	
	// Write game identity
	EEPROM.write(address+FILE_VALID, 'L');
	EEPROM.write(address+FILE_VALID+1, 'o');
	EEPROM.write(address+FILE_VALID+2, 'M');
	EEPROM.write(address+FILE_VALID+3, 'e');
	EEPROM.write(address+FILE_VALID+4, 'M');
	
	// Blank out Room Visited Completion and continue file
	for(offset = 0; offset < 14; ++offset) {
		EEPROM.write(address+FILE_COMPLETION+offset, 0);
	}
	
	// Blank out High Score files
	for(char player = 0; player < 30; player += 1) {
		EEPROM.write(20+address+player, 0);
	}
}


int getRoomClearPercentage()
{
	char i;
	int address = GameSaveOffset;
	char block;
	char completed = 0;
	
	if(!validSave) return 0;
	
	for(char blockNum = 0; blockNum < 5; ++blockNum) {
		block = EEPROM.read(address+FILE_COMPLETION+blockNum);
		for(i=0; i<8; ++i) {
			if((block>>i) & 1) completed++;
		}
	}
	
	return (completed*100)/30;
}


bool saveHighScore()
{
	int address = GameSaveOffset;
	
	char myScoreIndex;
	short compareScore;
	
	int myScoreAddress;
	int srcScoreAddress;
	int destScoreAddress;
	
	byte hi;
	byte lo;
	
	for(myScoreIndex=0; myScoreIndex<3; ++myScoreIndex) {
		srcScoreAddress = 20 + (myScoreIndex*10) + address;
		hi = EEPROM.read(srcScoreAddress+FILE_SCORE);
		lo = EEPROM.read(srcScoreAddress+FILE_SCORE+1);
		compareScore = (hi << 8) | lo;
		if(score > compareScore) break;
	}
	
	if(myScoreIndex < 3) {
		// Input name
		char input;
		char nameLength = 0;
		char inputName[5];
		
		for(char i=0; i<4; ++i) {
			inputName[i] = ' ';
		}
		inputName[4] = '\0';
		
		char cursorPos = 0;
		
		while(true) {
			arduboy.clear();
			arduboy.setCursor(0,0);
			arduboy.print(F("You set a high score!"));
			arduboy.setCursor(0,8);
			arduboy.print(F(" Enter name: \""));
			arduboy.print(inputName);
			arduboy.setCursor(6*18, 8);
			arduboy.print("\"");
			input = prompt_keyboard(cursorPos);
			if(input == 0) {
				if(nameLength > 0) nameLength--;
				if(nameLength < 4) inputName[nameLength] = ' ';
			} else {
				if(nameLength >= 4) break;
				inputName[nameLength] = input;
				nameLength++;
			}
		}
		
		
		for(char i=2; i>myScoreIndex; --i) {
			srcScoreAddress = 20 + ((i-1)*10) + address;
			destScoreAddress = 20 + (i*10) + address;
			for(char data=0; data<10; ++data) {
				hi = EEPROM.read(srcScoreAddress+data);
				EEPROM.write(destScoreAddress+data, hi);
			}
		}
		
		myScoreAddress = 20 + (myScoreIndex*10) + address;
		EEPROM.write(myScoreAddress+FILE_SCORE, ((score >> 8) & 0xFF));
		EEPROM.write(myScoreAddress+FILE_SCORE+1, (score & 0xFF));
		EEPROM.write(myScoreAddress+FILE_TIME, ((gameTime >> 8) & 0xFF));
		EEPROM.write(myScoreAddress+FILE_TIME+1, (gameTime & 0xFF));
		EEPROM.write(myScoreAddress+FILE_LEVEL, levelsCompleted);
		EEPROM.write(myScoreAddress+FILE_NAME, inputName[0]);
		EEPROM.write(myScoreAddress+FILE_NAME+1, inputName[1]);
		EEPROM.write(myScoreAddress+FILE_NAME+2, inputName[2]);
		EEPROM.write(myScoreAddress+FILE_NAME+3, inputName[3]);
		
		displayRecords();
		
		return true;
	}
	return false;
}


void markRoomAsCleared(unsigned char room)
{
	if(room > numLevels) return;
	int address = GameSaveOffset;
	int pos = address+FILE_COMPLETION+(room/8);
	char data = EEPROM.read(pos);
	data |= 1 << (room%8);
	EEPROM.write(pos, data);
}

short getCurrentLevelProgress()
{
	int address = GameSaveOffset;
	return EEPROM.read(10+address+FILE_LEVEL);
}

void displayLoadGame(byte file)
{
	unsigned char level = currentLevel;
	rollingScore = -30;
	quitGame = false;
	int address = GameSaveOffset;

	if(EEPROM.read(10+address+FILE_CONTINUE) == 1) {
		gameSetup();
		
		byte hi = EEPROM.read(10+address+FILE_SCORE);
		byte lo = EEPROM.read(10+address+FILE_SCORE+1);
		score = (hi << 8) | lo;
		
		hi = EEPROM.read(10+address+FILE_HEALTH);
		lo = EEPROM.read(10+address+FILE_HEALTH+1);
		p1.health = (hi << 8) | lo;
		
		levelsCompleted = getCurrentLevelProgress();
		currentLevel = EEPROM.read(10+address+FILE_CURRENT_LEVEL);
		
		hi = EEPROM.read(10+address+FILE_TIME);
		lo = EEPROM.read(10+address+FILE_TIME+1);
		gameTime = (hi << 8) | lo;
		
		if(currentLevel == 0)
			currentLevel = 255;
				
		gameGotoLevel(currentLevel);
		gameLoop();
	}
		
	quitGame = true;
}

void saveGame(byte file)
{
	int address = GameSaveOffset + 10;
	EEPROM.write(address+FILE_SCORE, ((score >> 8) & 0xFF));
	EEPROM.write(address+FILE_SCORE+1, (score & 0xFF));
	EEPROM.write(address+FILE_HEALTH, ((p1.health >> 8) & 0xFF));
	EEPROM.write(address+FILE_HEALTH+1, (p1.health & 0xFF));
	EEPROM.write(address+FILE_TIME, ((gameTime >> 8) & 0xFF));
	EEPROM.write(address+FILE_TIME+1, (gameTime & 0xFF));
	EEPROM.write(address+FILE_LEVEL, levelsCompleted);
	EEPROM.write(address+FILE_CURRENT_LEVEL, currentLevel);
	EEPROM.write(address+FILE_CONTINUE, 1);
}

void deleteContinueSave()
{
	EEPROM.write(GameSaveOffset + 10 + FILE_CONTINUE, 0);
}

void clearAllRooms()
{
	short roomID;
	
	for(roomID = 0; roomID < numLevels; roomID++) {
		markRoomAsCleared(roomID);
	}
}
