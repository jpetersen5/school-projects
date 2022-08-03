#include <iostream>
#include "Stack.h"
using namespace std;


// constructor and destructor do nothing
Stack::Stack() {}
Stack::~Stack() {}


void Stack::push(int value) {
        this->insertAtFront(value);
}


int Stack::pop() {
        int value = this->firstVal();
        this->removeFromFront();
        return value;
}


int& Stack::top() {
        int val = this->firstVal();
        int& valRef = val;
        return valRef;
}