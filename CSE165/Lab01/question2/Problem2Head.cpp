// Lab 01; Problem 2 Header CPP - Jason Petersen
#include "Problem2Head.h"
#include <iostream>
using namespace std;

// each function prints number, name, arguments,
// return type, and return value where applicable.
void printFunc1(char val) {
    cout << "--Function 1--" << endl << "Name: printFunc1" 
        << endl << "Arguments: char, with value " << val 
        << endl << "Return type: void" << endl 
        << "Return value: NULL" << endl << endl;
    return;
}

int printFunc2(int num, float dec) {
    cout << "--Function 2--" << endl << "Name: printFunc2" 
        << endl << "Arguments: int, with value " << num 
        << endl << "\tfloat, with value " << dec << endl 
        << "Return type: int" << endl << "Return value: " 
        << num << endl << endl;
    return num;
}

float printFunc3() {
    cout << "--Function 3--" << endl << "Name: printFunc3" 
        << endl << "Arguments: none" << endl
        << "Return type: float" << endl 
        << "Return value: 1.0" << endl << endl;
    return 1.0;
}