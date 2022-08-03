#include <iostream>
using namespace std;


// function to combine strings
string combineStr(string s, int n) {
	// initialize string to modify and return
	string combined = "";

	// loop n times, appending input string each time
	for (int i = 0; i < n; i++) {
		combined = combined + s;
	}

	// return result
	return combined;
}

// main function to request input and call combinedStr
int main() {
	// initialize variables
	string inp;
	int multi;

	// while loop to repeat until user stops with 0
	while (multi != 0) {
		// input arguments
		cout << "Enter a string: ";
		cin >> inp;
		cout << "Enter a number of times: ";
		cin >> multi;

		// check to end function or not
		if (multi == 0) {
			break;
		}

		// call function combineStr
		string combined = combineStr(inp, multi);

		cout << "The resulting string is: " << combined << endl;
	}

	return 0;
}
