#include <iostream>

#include "greenhouse.h"
#include "interface.h"
#include "input.h"
#include "text.h"

Greenhouse::Greenhouse() // Default factory settings
{
	time_ = 0;
	temperature_ = 20;
	humidity_ = 65;
	isWindowOpen_ = false;
	isHumidificationOn_ = false;
	isForceQuited_ = false;
	isWorking_ = true;
}

// Getters

bool Greenhouse::getQuitStatus()
{
	return isForceQuited_;
}
bool Greenhouse::getWorkStatus()
{
	return isWorking_;
}
bool Greenhouse::getWindowStatus()
{
	return isWindowOpen_;
}
bool Greenhouse::getHumidificationDeviceStatus()
{
	return isHumidificationOn_;
}
int Greenhouse::getTime()
{
	return time_;
}
double Greenhouse::getHumidity() {
	return humidity_;
}
double Greenhouse::getTemperature() {
	return temperature_;
}

// Setters

void Greenhouse::increaseTime()
{
	time_++;
}
void Greenhouse::openWindow() {
	isWindowOpen_ = true;
}
void Greenhouse::closeWindow() {
	isWindowOpen_ = false;
}
void Greenhouse::startHumidificationDevice() {
	isHumidificationOn_ = true;
}
void Greenhouse::stopHumidificationDevice() {
	isHumidificationOn_ = false;
}

// Executors

void Greenhouse::executeCommand(int commandCode)
{
	if (isWorking_ && commandCode != QUIT) {

		increaseTime();

		if (commandCode != SKIP_HOUR) {
			switch (commandCode) {
			case OPEN_WINDOW:
			{
				openWindow();
				break;
			}
			case CLOSE_WINDOW:
			{
				closeWindow();
				break;
			}
			case TURN_ON_DEVICE:
			{
				startHumidificationDevice();
				break;
			}
			case TURN_OFF_DEVICE:
			{
				stopHumidificationDevice();
				break;
			}
			case OPEN_WINDOW_TURN_ON_DEVICE:
			{
				openWindow();
				startHumidificationDevice();
				break;
			}
			case OPEN_WINDOW_TURN_OFF_DEVICE:
			{
				openWindow();
				stopHumidificationDevice();
				break;
			}
			case CLOSE_WINDOW_TURN_ON_DEVICE:
			{
				closeWindow();
				startHumidificationDevice();
				break;
			}
			case CLOSE_WINDOW_TURN_OFF_DEVICE:
			{
				closeWindow();
				stopHumidificationDevice();
				break;
			}
			}
		}
	}
	else {
		// Won't increase time when greenhouse is broken
		if (commandCode == QUIT)
			isForceQuited_ = true;
	}
}

void Greenhouse::modWorkStatus() // The method for checking the possibility of failure due to critical greenhouse conditions
{
	if (temperature_ >= MAX_TEMPERATURE || temperature_ <= MIN_TEMPERATURE || humidity_ <= MIN_HUMIDITY || humidity_ >= MAX_HUMIDITY) {
		isWorking_ = false;
	}
}

void Greenhouse::runHeaterTact() {
	// Model changes in temperature
	if (isWorking_ && !isForceQuited_ && isHeaterWorking_) // Heater is working on default due to rules
		if (isWindowOpen_) {
			// Formulas based on:
			// - Proportions of substraction between critical and current conditions
			// - Overall working time
			// - Random deviation
			temperature_ -= int((temperature_ - MIN_TEMPERATURE)*(rand() % 10 + 10 + time_ / 2)) / 100 + rand() % 1 + 1 + time_ / 8;
		}
		else {
			temperature_ += int((MAX_TEMPERATURE - temperature_)*(rand() % 10 + 5 + time_ / 3)) / 100 + 1 + time_ / 10;
		}
}

void Greenhouse::runHumidificationDeviceTact() {
	// Model changes in humidity
	if (isWorking_ && !isForceQuited_)
		if (isHumidificationOn_) {
			humidity_ += int((MAX_HUMIDITY - humidity_)*(rand() % 10 + 10 + time_ / 3)) / 100 + rand() % 2 + 1 + time_ / 10;
		}
		else {
			humidity_ -= int((humidity_ - MIN_HUMIDITY)*(rand() % 10 + 5 + time_ / 2)) / 100 + rand() % 1 + 1 + time_ / 8;
		}
}

// Modeling

void Greenhouse::startModeling(const char* argv)
{
	changeTextColor(DARK_GREY);
	showWelcomeMessage();
	// Select working mode
	if (!strcmp(argv, "manual")) {
		newGreenhouse.runInteractiveMode();
	}
	else {
		newGreenhouse.runAutoMode();
	}
	changeTextColor(LIGHT_GREY);
}

bool isLastIteration = false;

void Greenhouse::runInteractiveMode()
{
	increaseConsoleBufferSize();
	while (!isForceQuited_)
	{
		if (!isLastIteration) {
			showTime();
			showWorkingStatus();
			showConditionsStatus();
			showDevicesStatus();
			// If-case is used not to duplicate conditions info after greenhouse is broken
			startCleanCoords = getCoords();
			// Getting console text coordinates to clear menu after choosing command
			if (!isWorking_) {
				isLastIteration = true;
			}
		}
		showMenu();
		executeCommand(getExecuteCommandCode()); // Executing already valid command
		endCleanCoords = getCoords();
		runHeaterTact();
		runHumidificationDeviceTact();
		modWorkStatus();
		clearConsoleAfterCoords(startCleanCoords, endCleanCoords);
	}
	showLastConditions();
	showQuitMessage();
}

void Greenhouse::runAutoMode()
{
	while (isWorking_)
	{
		showTime();
		showWorkingStatus();
		showConditionsStatus();
		executeCommand(SKIP_HOUR);
		runHeaterTact();
		runHumidificationDeviceTact();
		modWorkStatus();
		pause(750);
	}
	showAutoLastConditions();
}