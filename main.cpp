#include <iostream>
using namespace std;

int main() {
	
	int memArrSize = 10;
	char chars[] = {'>', '>','<', '+'};
	int memArr[memArrSize];
	int pointerPos = 0;
	
	//Zeros the memory array
	for(int i=0; i<memArrSize; i++) {
		memArr[i] = 0;
	}

	for(int i=0; i<sizeof(chars)/sizeof(chars[0]); i++) {

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
				break;
		}

		//Prints the whole memory array
		for(int i=0; i<memArrSize; i++) {
			cout << memArr[i] << " ";
		}

		cout << endl;
		
	}

}

