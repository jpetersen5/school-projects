// Lab 03; Problem 1 - Jason Petersen
#include <iostream>

//: C05:UseHandle.cpp
//{L} Handle
// Use the Handle class
#include "Handle.h"
using namespace std;

int main() {
    Handle u;
    cout << "Handle value: " << u.read() << endl;
    u.change(1);
    cout << "Handle value: " << u.read() << endl;

    return 0;
} ///:~