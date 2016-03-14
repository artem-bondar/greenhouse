#ifndef GTEXT_H
#define GTEXT_H

#include <string>

using namespace std;

struct coordinates {
	short X, Y;
};

struct asciiKeys {
	const char
		closingWindow[3] = { 50,55,56 },
		openingWindow[3] = { 49,53,54 },
		turningOffDevice[3] = { 52,54,56 },
		turningOnDevice[3] = { 51,53,55 },
		valid[12] = { 13,49,50,51,52,53,54,55,56,113,115,104 };
	enum asciiValid { ENTER = 13, ONE = 49, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, Q = 113, S = 115, H = 104 };
};

struct Text
{
	const string
		autoQuit = "Greenhouse is not working!\n",
		badArgument = "It is only allowed to use 'manual' - as controlled greenhouse start or 'auto' - just to observe greenhouse working.\n",
		close = "closed",
		commandKeys[12] = {
		"[1]","[2]","[3]","[4]","[5]","[6]","[7]","[8]","[S]","[Q]","[H]","[Enter]" },
		commandWords[11] = {
		"Open","Close","ON","OFF"," window ","Switch ",
		"and switch "," humidification device ","Skip hour ","Quit","Show/hide non-executable commands" },
		conditions[5] = {
		"Humidification device"," is already ","working","stopped" },
		device = "\nHumidification device",
		dot = ".",
		finish = "Modeling is finished.\n",
		high = "too high for work!\n",
		hours = " hours\n",
		humidity = "C\nHumidity: ",
		humidityError = "Critical humidity: ",
		is = " is ",
		last = "Final conditions:\n",
		low = "too low for work!\n",
		menuWords[12] = {
		" Open"," Close","ON","OFF",
		" window"," Switch "," and switch ",
		" humidification device"," Skip hour\n",
		" Quit\n\n"," Show/hide non-executable commands\n\n"," Confirm command\n" },
		n = "\n",
		notWorking = "not working\n",
		off = "off\n",
		on = "on\n",
		open = "opened",
		pn = "%\n",
		quit = "\nYou quit greenhouse. Thank you for using!\n\n",
		startLine = "\r>>> ",
		status = "Status: ",
		temperature = "Temperature: ",
		temperatureError = "Critical temperature: ",
		time = "Time lasted: ",
		welcome = "\nWelcome to greenhouse!\n\n",
		window = "Window",
		working = "working\n";

	const int
		closeWindow[3] = { 1,6,7 },
		openWindow[3] = { 0,4,5 };

	const int size = 3;
};

enum colors {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GREY, DARK_GREY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE
};
enum conditionsErrorName { WINDOW_OPENED, WINDOW_CLOSED, DEVICE_ON, DEVICE_OFF };
enum executeCommands {
	OPEN_WINDOW = 1, CLOSE_WINDOW,
	TURN_ON_DEVICE, TURN_OFF_DEVICE,
	OPEN_WINDOW_TURN_ON_DEVICE,
	OPEN_WINDOW_TURN_OFF_DEVICE,
	CLOSE_WINDOW_TURN_ON_DEVICE,
	CLOSE_WINDOW_TURN_OFF_DEVICE,
	QUIT, SKIP_HOUR
};

extern Text text;
extern coordinates startCleanCoords, endCleanCoords;
extern asciiKeys keys;

#endif