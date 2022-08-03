#include <iostream>
using namespace std;

int main() {
	// variable for input string
	string inp;

	// get input for string
	cout << "Enter the string to reverse: ";
	getline(cin, inp);

	// variable for reverse of string
	string inp_r = "";

	// reverse the string by looping through it backwards
	for (int i = inp.length() - 1; i >= 0; i--) {
		inp_r = inp_r + inp[i];
	}

	// return reversed string
	cout << "The reverse of the string is: " << inp_r << endl;

	return 0;
}
