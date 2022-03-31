#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

// Declaring functions [

int callLoop();
void charConditional(bool *inLoop, int *loopLen);
void backendPrint();

// ] Declaring functions


// Declaring global variables [

// Creates character array [
char chars[100];
int charPos, charCount;
// ] Creates character array

// Creates memory cell array [
int const memArrSize = 10;
int memArr[memArrSize];
// ] Creates memory cell array

// Other setup [
int pointerPos = 0;
int const timeDel = 100000;
// ] Other setup

// ] Declaring global variables

int main() {

    // User selection of *.bf file [
	string brainFuckFile;
	cout << "Input file: ";
	cin >> brainFuckFile;
	cout << endl;
    // ] User selection of *.bf file

    // Get *.bf file into string [
	ifstream in(brainFuckFile);
	string contents((istreambuf_iterator<char>(in)), 
    istreambuf_iterator<char>());
    // ] Get *.bf file into string

    // Gets number of characters for character array [
	charCount = contents.length();
    // ] Gets number of characters for character array

    // Convert string into character array [
	for(int i=0; i<charCount; i++) {
		chars[i] = contents.c_str()[i];
	}
    // ] Convert string into character array

    // Zeros the memory cell array [
	for(int i=0; i<memArrSize; i++) {
		memArr[i] = 0;
	}
    // Zeros the memory cell array

    // Place holder values [
    bool inLoop = false;
    int loopLen = 0;
    // ] Place holder values

    // Runs once for every character in the brainfuck file [
    for(charPos=0; charPos<charCount; ++charPos) {

        charConditional(&inLoop, &loopLen);

        backendPrint();

    }
    // ] Runs once for every character in the brainfuck file

}

// Defining functions [

// Creates a sub-loop [
int callLoop() {

    bool inLoop = true;
    int loopLen = 0;
    
    while(inLoop) {

        charPos++;

        charConditional(&inLoop, &loopLen);

        backendPrint();

        
    }

    return loopLen;
}
// ] Creates a sub-loop

// Runs command based on the current character [
void charConditional(bool *inLoopP, int *loopLenP) {

    bool &inLoop = *inLoopP;
    int &loopLen = *loopLenP, subLoopLen;

    switch(chars[charPos]) {
        case '<':
            pointerPos--;
            if(inLoop) {loopLen++;}
            break;
        case '>':
            pointerPos++;
            if(inLoop) {loopLen++;}
            break;
        case '-':
            memArr[pointerPos]--;
            if(inLoop) {loopLen++;}
            break;
        case '+':
            memArr[pointerPos]++;
            if(inLoop) {loopLen++;}
            break;
        case '[':
            subLoopLen = callLoop();
            loopLen += subLoopLen+2;
            break;
        case ']':
            if(memArr[pointerPos] > 0) {
                charPos -= ++loopLen;
                loopLen = 0;
            }
            else {
                inLoop = false;
            }
            break;
        //default:
        //    break;
    }
}
// ] Runs command based on the current character

// Prints the backend of the brainfuck program [
void backendPrint() {

    // Prints the whole memory array [
	for(int i=0; i<memArrSize; i++) {
		cout << memArr[i] << " ";
	}

    cout << endl;
    // ] Prints the whole memory array

    // Prints pointer position [
	for(int i=0; i<pointerPos; i++) {		

		// Correction for multiple digit numbers [
		for(int j=10; j<memArr[i]; j*= 10) {
			cout << " ";
		}
        // ]

		cout << "  ";
	}
	cout << "^" << endl;
    // ] Prints pointer position
}
// ] Prints the backend of the brainfuck program

// ] Defining functions

