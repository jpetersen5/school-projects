// Lab 03; Problem 3 - Jason Petersen
// Create a class containing an array of int. Index 
// through this array using a pointer to member.

#include <iostream>
#include "Problem3h.h"
using namespace std;

int main() {
    // initialize object
    intArr arr(25);

    // output object contents with pointer notation
    cout << "Contents: " << endl << "[ ";
    for (int i = 0; i < arr.getSize(); i++)
        cout << *(arr.getArrPoint() + i) << " ";
    cout << "]" << endl;

    return 0;
}