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
	int typo;
	cout << "Enter the line for which we want to make a typo: ";
	cin >> typo;
	while (typo <= 0 || typo > lines){
		cout << "You entered an incorrect value for the line typo!" << endl << "Enter the line for which we want to make a typo: ";
		cin >> typo;
	}
	for (int i = 1; i <= lines; i++){
		if (i == typo){
			cout << "I will always use object oriented programing. ";
			continue;
		}
		cout << "I will always use object oriented programming. ";
	}
	cout << endl;
}



