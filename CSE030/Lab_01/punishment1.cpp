#include <iostream>
using namespace std;


int main() {
	int lines;
	cout << "Enter the number of lines for the punishment: ";
	cin >> lines;
	while (lines <= 0){
		cout << "You entered an incorrect value for the number of lines!" << endl << "Enter the number of lines for the punishment: ";
		cin >> lines;
	}
	for (int i = 1; i <= lines; i++){
		cout << "I will always use object oriented programming. ";
	}
	cout << endl;
}


