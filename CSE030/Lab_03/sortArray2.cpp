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

	// initialize value for swaps
	int x = 0;
	// loop to sort
	for (int i = 0; i < sz - 1; i++) {
		// initialize min value index
		int imin = i;
		// loop to check for minimum value (using indices beyond already found minimums)
		for (int j = i + 1; j < sz; j++) {
			if (arr[j] < arr[imin]) {
				imin = j;
			}
		}
		// swap with a temporary variable
		if (imin != i) {
			int temp;
			temp = arr[i];
			arr[i] = arr[imin];
			arr[imin] = temp;
			x++;
		}
	}

	// output sorted array
	cout << "This is the sorted array in ascending order: ";
	for (int i = 0; i < sz; i++) {
		cout << arr[i] << " ";
	}
	cout << endl << "The algorithm selected the minimum for the traverse of the array." << endl;
	cout << "It took " << x << " swaps to sort the array..." << endl;

	return 0;
}

