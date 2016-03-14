#include <conio.h> // Used for _getch()

#include "text.h"
#include "greenhouse.h"
#include "interface.h"
#include "array.h"

char getPressedKey() {
	return _getch();
}

bool checkConditions(char keyValue) {
	// Checks if command can be executed due to basis of formal logic
	bool isKeyValid = true;
	newNumberOfRaisedErrors = 0;
	if (newGreenhouse.getWindowStatus() && checkElementInArray(keyValue, keys.openingWindow, sizeof(keys.openingWindow))) {
		showConditionsError(WINDOW_OPENED);
		isKeyValid = false;
	}
	if (!newGreenhouse.getWindowStatus() && checkElementInArray(keyValue, keys.closingWindow, sizeof(keys.closingWindow))) {
		showConditionsError(WINDOW_CLOSED);
		isKeyValid = false;
	}
	if (newGreenhouse.getHumidificationDeviceStatus() && checkElementInArray(keyValue, keys.turningOnDevice, sizeof(keys.turningOnDevice))) {
		showConditionsError(DEVICE_ON);
		isKeyValid = false;
	}
	if (!newGreenhouse.getHumidificationDeviceStatus() && checkElementInArray(keyValue, keys.turningOffDevice, sizeof(keys.turningOffDevice))) {
		showConditionsError(DEVICE_OFF);
		isKeyValid = false;
	}
	lastNumberOfRaisedErrors = newNumberOfRaisedErrors;
	return isKeyValid;
}

int getExecuteCommandCode() {
	char keyValue;
	char printedCommand; // Previous keyValue
	bool isKeyChecked = false;
	bool isCommandPrinted = false;
	while (!isKeyChecked)
	{
		keyValue = getPressedKey();
		if (checkElementInArray(keyValue, keys.valid, sizeof(keys.valid))) {
			if (keyValue == keys.ENTER) {
			// Assume "Enter" as a function depending on previous command value
				if (isCommandPrinted && checkConditions(printedCommand)) {
					// Not already entered => do nothing
					// Entered and valid => finish while-loop
					if (printedCommand != keys.H) {
						isKeyChecked = true;
					}
					else {
						clearConsoleAfterCoords(startCleanCoords, endCleanCoords);
						isCommandPrinted = false;
						showMenu(false);
					}
				}
			}
			else
			{
				showSelectedCommand(keyValue);
				printedCommand = keyValue;
				isCommandPrinted = true;
			}
		}
	}
	return getElementIndexFromArray(printedCommand, keys.valid, sizeof(keys.valid));
}