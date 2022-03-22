#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
	for(int i=0; i<charCount; ++i) {
		
		//Runs command based on the current character
		switch (chars[i]) {
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
			default:
				continue;
		}

		//Prints the whole memory array
		for(int i=0; i<memArrSize; i++) {
			cout << memArr[i] << " ";
		}
		
		cout << endl;
		
	}

}

