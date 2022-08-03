#include <iostream>
using namespace std;


int main() {
	// initialize size of array and ask for input
	int sz;
	cout << "Enter the size of the array: ";
	cin >> sz;

	// check for valid size
	if (sz < 1) {
		cout << "ERROR: you entered an incorrect value for the array size!" << endl;
		return 0;
	}

	// initialize array to size and ask for value with a loop
	int arr [sz];
	cout << "Enter the numbers in the array, separated by a space, and press enter: ";
	for (int i = 0; i < sz; i++) {
		cin >> arr[i];
	}

	// initialize value to check for and ask for input
	int v;
	cout << "Enter a number to search for in the array: ";
	cin >> v;

	// initialize # of checks, loop for linear search and output when appropriate
	int x = -1;
	for (int i = 0; i < sz; i++) {
		if (arr[i] == v) {
			// # of checks is equal to index + 1
			x = i + 1;
			cout << "Found value " << v << " at index " << i << ", which took " << x << " checks." << endl;

			// check for best / worst case; no else if in case best and worst overlap
			if (i == 0) {
				cout << "We ran into the best case scenario!" << endl;
			} if (i == sz - 1) {
				cout << "We ran into the worst case scenario!" << endl;
			}

			// end loop when answer found
			break;
		}
	}

	// if the loop ends x will still be initialized to -1, must be failed
	if (x == -1) {
		cout << "The value " << v << " was not found in the array!" << endl;
	}

	return 0;
}
