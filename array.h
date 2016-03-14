#ifndef ARRAY_H
#define ARRAY_H

bool
checkElementInArray(char element, const char* array, int arrayLength),
checkElementInArray(int element, const int* array, int arrayLength);

int
getElementIndexFromArray(char element, const char* array, int arrayLength);

extern int
newNumberOfRaisedErrors,
lastNumberOfRaisedErrors;

#endif