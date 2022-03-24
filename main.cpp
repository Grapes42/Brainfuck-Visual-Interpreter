#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

void callLoop(char *chars, int *memArr, int *memArrSizeP, int *charPosP, int *pointerPosP);
void backendPrint(int memArr, int memArrSize, int pointerPos);

int main() {

	//User selection of *.bf file
	string brainFuckFile;
	cout << "Input file: ";
	cin >> brainFuckFile;
	cout << endl;

	//Get *.bf file into string
	ifstream in(brainFuckFile);
	string contents((istreambuf_iterator<char>(in)), 
    istreambuf_iterator<char>());

	//Gets number of characters for character array
	int charCount = contents.length();
	char chars[charCount];

	//Convert string into character array
	for(int i=0; i<charCount; i++) {
		chars[i] = contents.c_str()[i];
	}

	//Creates array of memory cells
	int memArrSize = 10;
	int memArr[memArrSize];

	//Sets the pointer position to 0
	int pointerPos = 0;
	
	//Zeros the memory cell array
	for(int i=0; i<memArrSize; i++) {
		memArr[i] = 0;
	}

	//Runs once for every character in the Brainfuck file
	for(int charPos=0; charPos<charCount; ++charPos) {

		//Runs command based on the current character
		switch(chars[charPos]) {
			case '<':
				pointerPos--;
				break;
			case '>':
				pointerPos++;
				break;
			case '-':
				memArr[pointerPos]--;
				break;
			case '+':
				memArr[pointerPos]++;
				break;
			case '[':
				callLoop(chars, memArr, &memArrSize, &charPos, &pointerPos);
				break;
			case ']':
				cout << "Invalid operation, not in loop" << endl;
				break;
			default:
				break;
		}

		//Prints the whole memory array
		for(int i=0; i<memArrSize; i++) {
			cout << memArr[i] << " ";
		}

		cout << endl;

		//Prints pointer position
		for(int i=0; i<pointerPos; i++) {
			cout << "  ";
		}

		cout << "^" << endl;

		usleep(100000);
	}
}

//Function for calling a new loop
void callLoop(char *chars, int *memArr, int *memArrSizeP, int *charPosP, int *pointerPosP) {
	
	bool inLoop = true;
	int loopLen = 0;

	//Declaring variables from pointers
	int &memArrSize = *memArrSizeP,
		&charPos = *charPosP,
		&pointerPos = *pointerPosP;

	while(inLoop) {

		charPos++;

		//Runs command based on the current character
		switch(chars[charPos]) {
			case '<':
				pointerPos--;
				loopLen++;
				break;
			case '>':
				pointerPos++;
				loopLen++;
				break;
			case '-':
				memArr[pointerPos]--;
				loopLen++;
				break;
			case '+':
				memArr[pointerPos]++;
				loopLen++;
				break;
			case '[':
				callLoop(chars, memArr, &memArrSize, &charPos, &pointerPos);
				break;
			case ']':
				if(memArr[pointerPos] > 0) {
					charPos -= ++loopLen;
					loopLen = 0;
				}
				else {
					inLoop = false;
					//cout << "not in loop" << endl;
				}
				break;
			default:
				break;
		}

		//Prints the whole memory array
		for(int i=0; i<memArrSize; i++) {
			cout << memArr[i] << " ";
		}

		cout << endl;

		//Prints pointer position
		for(int i=0; i<pointerPos; i++) {
			cout << "  ";
		}

		cout << "^" << endl;

		usleep(100000);
	}
}