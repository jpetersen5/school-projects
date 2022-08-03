#include <iostream>
using namespace std;


int main() {
	// variable for array's size
	int sz;

	// get input for the array's size
	cout << "Enter the size of the array: ";
	cin >> sz;

	// check for incorrect inputs of array size
	if (sz < 1) {
		cout << "ERROR: you entered an incorrect value for the array size!" << endl;

		return 0;
	}

	// create array variable and ask for inputs
	int usr_arr [sz];
	cout << "Enter the numbers in the array, seperated by a space, and press enter: ";

	// process inputs
	for (int i = 0; i < sz; i++) {
		cin >> usr_arr[i];

		// while processing inputs, simultaneously check for increasing
		if (i > 0 && usr_arr[i] < usr_arr[i-1]) {
			// if not increasing, end process
			cout << "This is NOT an increasing array!" << endl;

			return 0;
		}
	}

	// if the program gets to this point, the array must be increasing
	cout << "This IS an increasing array!" << endl;

	return 0;
}

