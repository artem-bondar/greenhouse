#ifndef GINTERFACE_H
#define GINTERFACE_H

#include "text.h"

void
changeTextColor(colors textColor),
clearConsoleAfterCoords(coordinates cleanAfter, coordinates cleanUntill),
clearConsoleRow(short rowNumber, short moveCursor = 0),
increaseConsoleBufferSize(),
pause(int ms),
print(string text, colors textColor, colors backgroundColor = BLACK),
showArgumentError(),
showAutoLastConditions(),
showConditionsError(conditionsErrorName code),
showConditionsStatus(),
showDevicesStatus(),
showError(),
showLastConditions(),
showMenu(bool changeNonExecutableShowMode = true),
showQuitMessage(),
showSelectedCommand(char keyValue),
showTime(),
showWelcomeMessage(),
showWorkingStatus();

coordinates
getCoords();

bool
checkMenuCommand(int commandCode);

extern bool
doNotShowNonExecutable;

#endif