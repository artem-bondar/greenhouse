#include "greenhouse.h"
#include "interface.h"

Greenhouse newGreenhouse;
Text text;

coordinates startCleanCoords, endCleanCoords;
asciiKeys keys;

// In header files there are mentioned as extern

void main(int argc, char* argv[]){
	if (argc == 2 && (!strcmp(argv[1], "auto") || !strcmp(argv[1], "manual"))) {
		// Checking arguments for validity
		// "Auto" - for automatic modeling, - "manual" for interactive
		// Greenhouse class object "newGreenhouse" is already initialized in "Greenhouse.cpp"
		newGreenhouse.startModeling(argv[1]); // Sending mode specifier to mode switcher, that launches model process
	}
	else
		showArgumentError(); // If check not completed - show error
	newGreenhouse.startModeling("manual");
}