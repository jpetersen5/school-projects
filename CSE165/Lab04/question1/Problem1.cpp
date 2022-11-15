// Lab 04; Problem 1 - Jason Petersen
// Write a function that takes a pointer argument, modifies 
// what the pointer points to, and then returns the 
// destination of the pointer as a reference.
#include <iostream>
using namespace std;

int& reroute(int* point);

int main() {
    int point = 10;
    cout << "Pointer " << &point << " points to " << point << endl;
    cout << "After function, reference value is " << reroute(&point) << endl;

    return 0;
}

int& reroute(int* point) {
    int& ref = *point;
    ref += 10;
    return ref;
}