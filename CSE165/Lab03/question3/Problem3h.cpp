// Lab 03; Problem 3 - Jason Petersen

#include <iostream>
#include "Problem3h.h"

// default constructor
intArr::intArr() {
    size = 10;
    std::cout << "Constructing with size " << size << std::endl;
    arr = new int[size];
    for (int i = 0; i < size; i++)
        arr[i] = i;
}

// constructor with size input
intArr::intArr(int inSize) {
    size = inSize;
    std::cout << "Constructing with size " << size << std::endl;
    arr = new int[size];
    for (int i = 0; i < size; i++)
        arr[i] = i;
}

// destructor
intArr::~intArr() {
    std::cout << "Destructing" << std::endl;
    delete arr;
}

int intArr::getSize() {
    return size;
}

int* intArr::getArrPoint() {
    return arr;
}