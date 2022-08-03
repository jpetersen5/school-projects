#include <iostream>
#include "Stack_char.h"
using namespace std;


// constructor and destructor do nothing
Stack::Stack() {}
Stack::~Stack() {}


void Stack::push(char value) {
        this->insertAtFront(value);
}


char Stack::pop() {
        char value = this->firstVal();
        this->removeFromFront();
        return value;
}


char& Stack::top() {
        char val = this->firstVal();
        char& valRef = val;
        return valRef;
}