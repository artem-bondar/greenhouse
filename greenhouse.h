#ifndef GREENHOUSE_H
#define GREENHOUSE_H

class Greenhouse
{
public:

	Greenhouse();

	void
		startModeling(const char* argv);

	bool
		getHumidificationDeviceStatus(),
		getQuitStatus(),
		getWindowStatus(),
		getWorkStatus();

	int
		getTime();

	double
		getHumidity(),
		getTemperature();

	const double
		MAX_HUMIDITY = 90,
		MIN_HUMIDITY = 30,
		MAX_TEMPERATURE = 40,
		MIN_TEMPERATURE = 0;
		
private:

	void
		closeWindow(),
		executeCommand(int commandCode),
		increaseTime(),
		modWorkStatus(),
		openWindow(),
		runAutoMode(),
		runHeaterTact(),
		runHumidificationDeviceTact(),
		runInteractiveMode(),
		startHumidificationDevice(),
		stopHumidificationDevice();

	bool
		isForceQuited_,
		isHumidificationOn_,
		isWindowOpen_,
		isWorking_;

	int
		humidity_,
		temperature_,
		time_;

	const bool
		isHeaterWorking_ = true;
};

extern Greenhouse newGreenhouse;

extern bool isLastIteration;

#endif