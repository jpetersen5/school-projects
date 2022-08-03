#include <iostream>
using namespace std;

int main() {
	// variable for array dimensions
	int arr_dim;

	// ask for array dimensions
	cout << "Enter the size of a 2D array: ";
	cin >> arr_dim;

	// check for correct array dimensions
	if (arr_dim < 1) {
		cout << "ERROR: you entered an incorrect value for the array size!" << endl;
		return 0;
	} else if (arr_dim > 10) {
		cout << "ERROR: your array is too large! Enter 1 to 10." << endl;
		return 0;
	}

	// initialize array and count for negatives
	int arr [arr_dim][arr_dim];
	int c_neg = 0;

	// ask for array inputs
	for (int i = 0; i < arr_dim; i++) {

		cout << "Enter the values in the array for row " << i + 1 << ", separated by a space, and press enter: ";

		// input values while checking for negatives
		for (int j = 0; j < arr_dim; j++) {
			cin >> arr[i][j];
			if (arr[i][j] < 0) {
				c_neg++;
			}
		}
	}

	// output negative values amount
	if (c_neg == 0) {
		cout << "All values are non-negative!" << endl;
	} else {
		cout << "There are " << c_neg << " negative values!" << endl;
	}

	return 0;
}
