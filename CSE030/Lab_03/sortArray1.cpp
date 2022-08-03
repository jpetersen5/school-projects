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
	int max;
	for (int i = 0; i < sz; i++) {
		cin >> arr[i];
	}

	// loop to sort
	for (int i = 0; i < sz - 1; i++) {
		// initialize max value index
		int imax = i;
		// loop to check for maximum value (using indices beyond already found maximums)
		for (int j = i + 1; j < sz; j++) {
			if (arr[j] > arr[imax]) {
				imax = j;
			}
		}
		// swap with a temporary variable
		int temp;
		temp = arr[i];
		arr[i] = arr[imax];
		arr[imax] = temp;
	}

	// output sorted array
	cout << "This is the sorted array in descending order: ";
	for (int i = 0; i < sz; i++) {
		cout << arr[i] << " ";
	}
	cout << endl << "The algorithm selected the maximum for the traverse of the array." << endl;

	return 0;
}
