#include <Arduino.h>
#include "globals.h"
#include "data.h"
#include "save.h"

void displayTitle()
{
    // Get the length of the strings
    size_t titleLen = strlen_P(gameTitle);
    size_t subTitleLen = strlen_P(gameSubTitle);
    
	arduboy.clear();
	
	// Print game title, large and centered
	arduboy.setTextSize(2);
	arduboy.setCursor(64 - titleLen*6, 12);
	arduboy.print(eps((char *)gameTitle));
	
	// Display game subtitle, small and centered
	arduboy.setTextSize(1);
	arduboy.setCursor(64 - subTitleLen*3, 30);
    arduboy.print(eps((char *)gameSubTitle));

	int roomsCleared = getRoomClearPercentage();
	
	// Display room clear count if the player beat at least level 1
	if(roomsCleared > 0)
	{
		arduboy.setCursor(6, 8*6 + 4);
		arduboy.print(F("ROOMS CLEARED: "));
		arduboy.print(roomsCleared);
		arduboy.print("%");
	}
	// Display copyright on an otherwise fresh file
	else
	{
		arduboy.setCursor(20, scrh-8);
		arduboy.print(F("(c) 2016 fuopy"));
	}
	
	arduboy.display();
	
	// Wait 1000 ticks
	delay(1000);
	
	// Start blanking out the screen
	while(true) {
		updateInput();
		arduboy.drawPixel(random(0,128), random(0,64), 0);
		arduboy.display();
		if(A_PRESSED) break;
	}
}