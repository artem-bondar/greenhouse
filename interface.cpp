#include <iostream>
#include <Windows.h> // WinAPI

#include "greenhouse.h"
#include "text.h"
#include "array.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Getting console output descriptor and saving it in "hStdOut" identifier
CONSOLE_SCREEN_BUFFER_INFO csbi; // (On initialization is empty)
// CSBI-typedef variable for saving different info about console in it's fields like:
// - dwCursorPosition, that stores coordinates of cursor in COORD-typedef
	// Isn't a dynamic variable
// - dwSize - sizes of console
// - etc.

void clearConsoleRow(short rowNumber, short moveCursor = 0) {
	// Clear exact (rowNumber) console line
	// Type "short" is used because API functions requires COORD-typedef for coordinates, which used short X, Y fields
	GetConsoleScreenBufferInfo(hStdOut, &csbi); // Save current info about console in global "csbi" variable
	DWORD binBuffer; // DWORD-typedef (double word - 64-bits) to save number of printed chars in FillConsoleOutputCharacter-function
	FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', csbi.dwSize.X, { 0, csbi.dwCursorPosition.Y - rowNumber }, &binBuffer);
	// WinAPI function for printing character that receives next arguments:
	// - HANDLE %identifiername% - identifier of console screen, where the character will be printed
	// - TCHAR-typedef %char% - printed character
	// - DWORD %number% - how many times in a row character will be printed
	// - COORD-typedef %variablename% - coordinates, starting from what the character will be printed
		// Instead of COORD can be used it's equivalent - {short X, short Y}
	// - LPDWORD-typedef (pointer to DWORD) %variablename% - pointer to the variable, that will 
	// receive the number of real printed symbols 
	SetConsoleCursorPosition(hStdOut, { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y - moveCursor});
	// Restoring cursor position with "moveCursor" incrementing
	// WinAPI function for setting cursor to new position, receives next argumnets:
	// - HANDLE %identifiername%
	// - COORD %variablename%
}

coordinates getCoords() {
	// Get current cursor coordinates and saves it to global variable
	// Uses pre-made COORD analogue - coordinates-structure - for not including "Windows.h" in another files
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	coordinates saveTo = { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
	return saveTo;
}

void clearConsoleAfterCoords(coordinates cleanAfter, coordinates cleanUntill) {
	// Clearing all symbols in console after "cleanAfter" coordinates untill "cleanUntill" coordinates
	COORD cleanAfterCoords = { cleanAfter.X, cleanAfter.Y };
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	DWORD binBuffer;
	DWORD cleanSize = csbi.dwSize.X * (cleanUntill.Y + 1 - cleanAfter.Y); 
	// Counting size of cleaning area, + 1 for off-by-one length fix in substraction in line numeration
	FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cleanSize, cleanAfterCoords, &binBuffer);
	SetConsoleCursorPosition(hStdOut, { cleanAfterCoords.X, cleanAfterCoords.Y });
	// Restoring cursor position with "moveCursor" incrementing
}

void print(string text, colors textColor, colors backgroundColor = BLACK) {
	// cout analogue with colors
	SetConsoleTextAttribute(hStdOut, (WORD)((backgroundColor << 4) | textColor));
	// WinAPI function for changing console color attribute, receives next arguments:
	// - HANDLE %identifiername%
	// - WORD-typedef %number% - 4 byte number, but only last 8-bits are used and are standing for
	// Ib Rb Gb Bb If Rf Gf Bf
	// b,f for background, foreground
	// I for intensity, R,G,B for RGB colors availability
	cout << text;
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | DARK_GREY));
	// Returning default color settings
}

void changeTextColor(colors textColor) {
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | textColor));
}

void increaseConsoleBufferSize() {
	// Makes console buffer size 80x750, compared to default 80x300
	COORD newSize = { 80,750 };
	SetConsoleScreenBufferSize(hStdOut, newSize);
}

void showWelcomeMessage() {
	print(text.welcome, LIGHT_MAGENTA);
}

void showError() {
	// Showing the cause of breaking error
	changeTextColor(LIGHT_RED);
	if (newGreenhouse.getTemperature() >= newGreenhouse.MAX_TEMPERATURE || newGreenhouse.getTemperature() <= newGreenhouse.MIN_TEMPERATURE)
	{
		cout << text.temperatureError;
		if (newGreenhouse.getTemperature() >= newGreenhouse.MAX_TEMPERATURE)
			cout << text.high;
		else
			cout << text.low;
	}
	if (newGreenhouse.getHumidity() >= newGreenhouse.MAX_HUMIDITY || newGreenhouse.getHumidity() <= newGreenhouse.MIN_HUMIDITY)
	{
		cout << text.humidityError;
		if (newGreenhouse.getHumidity() >= newGreenhouse.MAX_HUMIDITY)
			cout << text.high;
		else
			cout << text.low;
	}
	changeTextColor(DARK_GREY);
}

void showTime() {
	changeTextColor(LIGHT_GREY);
	cout << text.time << newGreenhouse.getTime() << text.hours;
	changeTextColor(DARK_GREY);
}

void showConditionsStatus() {
	cout << text.temperature << newGreenhouse.getTemperature() 
		 << text.humidity << newGreenhouse.getHumidity() << text.pn;
}

void showLastConditions() {
	cout << text.finish;
	showTime();
	print(text.last, LIGHT_GREY);
	showConditionsStatus();
}

void showAutoLastConditions() {
	// For auto-mode
	showError();
	cout << text.n << text.finish;
	showTime();
	print(text.last, LIGHT_GREY);
	showConditionsStatus();
}

void showQuitMessage() {
	print(text.quit, LIGHT_MAGENTA);
}

void showWorkingStatus() {
	cout << text.status;
	if (newGreenhouse.getWorkStatus()) {
		print(text.working, GREEN);
	}

	else {
		print(text.notWorking, RED);
		showError();
	}
}

void showDevicesStatus() {
	print(text.window, CYAN);
	cout << text.is;
	if (newGreenhouse.getWindowStatus()) {
		print(text.open, GREEN);
	}
	else {
		print(text.close, RED);
	}
	print(text.device, BROWN);
	cout << text.is;
	if (newGreenhouse.getHumidificationDeviceStatus()) {
		print(text.on, GREEN);
	}
	else {
		print(text.off, RED);;
	}
	cout << text.n;
}

bool checkMenuCommand(int commandCode) {
	// Checks if menu command can be executed due to basis of formal logic
	if ((newGreenhouse.getWindowStatus() && checkElementInArray(commandCode, keys.openingWindow, sizeof(keys.openingWindow))) ||
		(!newGreenhouse.getWindowStatus() && checkElementInArray(commandCode, keys.closingWindow, sizeof(keys.closingWindow))) ||
		(newGreenhouse.getHumidificationDeviceStatus() && checkElementInArray(commandCode, keys.turningOnDevice, sizeof(keys.turningOnDevice))) ||
		(!newGreenhouse.getHumidificationDeviceStatus() && checkElementInArray(commandCode, keys.turningOffDevice, sizeof(keys.turningOffDevice))) ||
		(!newGreenhouse.getWorkStatus() && commandCode <= 57)) 
	{
		return false;
	}
	return true;
}

bool doNotShowNonExecutable = true;

void showMenu(bool changeNonExecutableShowMode = true) {
	// Uses many if-cases for appropriate coloring the text
	if (!changeNonExecutableShowMode) {
		if (doNotShowNonExecutable) {
			doNotShowNonExecutable = false;
		}
		else {
			doNotShowNonExecutable = true;
		}
	}
	for (int i = 1; i <= 12; i++) {
		// For backlighting executable commands
		if (doNotShowNonExecutable || (!doNotShowNonExecutable && (checkMenuCommand(i - 1 + keys.ONE)))) {
			if ((checkMenuCommand(i - 1 + keys.ONE) && newGreenhouse.getWorkStatus()) || i >= 10) {
				print(text.commandKeys[i - 1], WHITE);
			}
			else {
				print(text.commandKeys[i - 1], DARK_GREY);
			}
			if (i <= CLOSE_WINDOW_TURN_OFF_DEVICE) {
				if (checkElementInArray(i - 1, text.openWindow, text.size)) print(text.menuWords[0], GREEN);
				if (checkElementInArray(i - 1, text.closeWindow, text.size)) print(text.menuWords[1], RED);
				if (i == TURN_ON_DEVICE || i == TURN_OFF_DEVICE) cout << text.menuWords[5];
				else print(text.menuWords[4], CYAN);
				if (i >= OPEN_WINDOW_TURN_ON_DEVICE) cout << text.menuWords[6];
				if (i >= TURN_ON_DEVICE) {
					if ((i - 1) % 2 == 1) print(text.menuWords[3], RED);
					else print(text.menuWords[2], GREEN);
					print(text.menuWords[7], BROWN);
				}
				cout << text.n;
			}
			if (i == CLOSE_WINDOW_TURN_OFF_DEVICE) cout << text.n;
			if (i > CLOSE_WINDOW_TURN_OFF_DEVICE && i != 10) cout << text.menuWords[i - 1];
			if (i == 10) print(text.menuWords[9], MAGENTA);
		}
		else {
			if (i == CLOSE_WINDOW_TURN_OFF_DEVICE) cout << text.n;
		}
	}
	cout << text.n << text.startLine;
}

void showArgumentError() {
	cout << text.badArgument;
}

void showConditionsError(conditionsErrorName code) {
	newNumberOfRaisedErrors++;
	switch (lastNumberOfRaisedErrors) {
	case 0:
	{
		clearConsoleRow(0);
		break;
	}
	case 1:
	{
		lastNumberOfRaisedErrors = 0;
		clearConsoleRow(0);
		clearConsoleRow(1, 1);
		break;
	}
	case 2:
	{
		lastNumberOfRaisedErrors = 0;
		clearConsoleRow(0);
		clearConsoleRow(1);
		clearConsoleRow(2, 2);
		break;
	}
	}
	print(text.startLine, WHITE);
	switch (code) {
	case WINDOW_OPENED: {
		print(text.window, CYAN);
		cout << text.conditions[1];
		print(text.open, GREEN);
		break;
	}
	case WINDOW_CLOSED: {
		print(text.window, CYAN);
		cout << text.conditions[1];
		print(text.close, RED);
		break;
	}
	case DEVICE_ON: {
		print(text.conditions[0], BROWN);
		cout << text.conditions[1];
		print(text.conditions[2], GREEN);
		break;
	}
	case DEVICE_OFF: {
		print(text.conditions[0], BROWN);
		cout << text.conditions[1];
		print(text.conditions[3], RED);
		break;
	}
	}
	cout << text.n << text.startLine;
}

void showSelectedCommand(char keyValue) {
	// Uses many if-cases for appropriate coloring the text
	clearConsoleRow(0);
	print(text.startLine, WHITE);
	if (keyValue <= keys.EIGHT && keyValue >= keys.ONE) {
		int shiftedIndex = keyValue - keys.ONE + 1;
		if (checkElementInArray(shiftedIndex - 1, text.openWindow, text.size)) print(text.commandWords[0], GREEN);
		if (checkElementInArray(shiftedIndex - 1, text.closeWindow, text.size)) print(text.commandWords[1], RED);
		if (shiftedIndex == TURN_ON_DEVICE || shiftedIndex == TURN_OFF_DEVICE) cout << text.commandWords[5];
		else print(text.commandWords[4], CYAN);
		if (shiftedIndex >= OPEN_WINDOW_TURN_ON_DEVICE) cout << text.commandWords[6];
		if (shiftedIndex >= TURN_ON_DEVICE)
		{
			if ((shiftedIndex - 1) % 2 == 1) print(text.commandWords[3], RED);
			else print(text.commandWords[2], GREEN);
			print(text.commandWords[7], BROWN);
		}
	}
	else
		switch (keyValue) {
		case keys.S:
		{
			cout << text.commandWords[8];
			break;
		}
		case keys.Q:
		{
			print(text.commandWords[9], MAGENTA);
			break;
		}
		case keys.H:
		{
			cout << text.commandWords[10];
			break;
		}
		}
	endCleanCoords = getCoords();
}

void pause(int ms) {
	Sleep(ms);
	cout << text.n;
}