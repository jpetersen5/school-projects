// Lab 03; Problem 1 - Jason Petersen
// Modify the Handle.h, Handle.cpp, and UseHandle.cpp 
// files at the end of Chapter 5 to use constructors 
// and destructors.
#include <iostream>

//: C05:Handle.cpp {O}
// Handle implementation
#include "Handle.h"

// Define Handle's implementation:
struct Handle::Cheshire {
    int i;
};

Handle::Handle() {
    std::cout << "Constructing" << std::endl;
    smile = new Cheshire;
    smile->i = 0;
}

Handle::~Handle() {
    std::cout << "Destructing" << std::endl;
    delete smile;
}

int Handle::read() {
    return smile->i;
}

void Handle::change(int x) {
    smile->i = x;
} ///:~