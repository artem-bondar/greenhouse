int newNumberOfRaisedErrors, lastNumberOfRaisedErrors;

bool checkElementInArray(char element, const char* array, int arrayLength) {
	for (int i = 0; i < arrayLength; i++)
		if (element == array[i])
			return true;
	return false;
}

bool checkElementInArray(int element, const int* array, int arrayLength) {
	for (int i = 0; i < arrayLength; i++)
		if (element == array[i])
			return true;
	return false;
}

int getElementIndexFromArray(char element, const char* array, int arrayLength) {
	for (int i = 0; i < arrayLength; i++) {
		if (element == array[i]) {
			return i;
		}
	}
	return false;
}