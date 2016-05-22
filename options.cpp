#include "options.h"
#include "prompt.h"
#include "save.h"

// The Strings used for the Options Menu
const char optionsMenuItems_0[] PROGMEM = "[   Options Menu    ]";
const char optionsMenuItems_1[] PROGMEM = "Sound:";
const char optionsMenuItems_2[] PROGMEM = "Reset Game Data";

const char* const optionsMenuItems[] PROGMEM = {
    optionsMenuItems_0,
    optionsMenuItems_1,
    optionsMenuItems_2
};

const char clearSaveConfirmItems_0[] PROGMEM = "[REALLY CLEAR SAVE? ]";
const char clearSaveConfirmItems_1[] PROGMEM = "No, whoops!";
const char clearSaveConfirmItems_2[] PROGMEM = "Yes, I'm sure.";

const char optionsMenuItemsCount = 2;

const char* const clearSaveMenuItems[] PROGMEM = {
	clearSaveConfirmItems_0,
	clearSaveConfirmItems_1,
	clearSaveConfirmItems_2
};

const char clearSaveMenuItemsCount = 2;

unsigned char displayOptionsMenu()
{
    unsigned char choice;
    
    // Repeat while a choice has not been made
    while(choice != 255) {
        // Check if the audio is currently enabled
        bool audioEnabled = arduboy.audio.enabled();
        
        // Prompt the user for a choice
		arduboy.clear();
		
		// Draw whether sound is disabled
		arduboy.setCursor(6*7 + 2, 8);
		if (audioEnabled) {
			arduboy.print("On");
		} else {
			arduboy.print("Off");
		}
        choice = prompt_start(optionsMenuItems, optionsMenuItemsCount);
        
        // Choice: Toggle Sound
        if(choice == 0) {
			if(audioEnabled) {
				arduboy.audio.off();
				arduboy.audio.saveOnOff();
			}
			else
			{
				arduboy.audio.on();
				arduboy.audio.saveOnOff();
			}
            return SETTING_CHANGED;
        }
        
        // Choice: Clear Data
        else if(choice == 1) {
			
			// If it's time to reboot, reboot!
			if(displayClearMenu() == SETTING_REBOOT)
				return SETTING_REBOOT;
			
			// Otherwise return to settings
			continue;
        }
        
        // Back: Go to previous screen
        return SETTING_FINISHED;
    }   
}

unsigned char displayClearMenu()
{
	unsigned char choice;
	
	// Prompt the user for a choice
	arduboy.clear();
	choice = prompt_start(clearSaveMenuItems, clearSaveMenuItemsCount);
	
    // Repeat while a choice has not been made
    while(choice != 255) {
		
		// Choice One: Do nothing
		if(choice == 0)
			return SETTING_FINISHED;
		
		// Choice Two: Delete the save file
		if(choice == 1)
		{
			// Delete the save file
			breakSave(GAME_SAVE_FILE);
			
			// Reboot the game
			return SETTING_REBOOT;
		}
		
		// Back: Go to the previous screen
		return SETTING_FINISHED;
	}
}
