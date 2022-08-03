#include <iostream>
#include "Queue_char.h"
using namespace std;


// constructor and destructor do nothing
Queue::Queue() {}
Queue::~Queue() {}


void Queue::enqueue(char value) {
        this->insertAtBack(value);
}


char Queue::dequeue() {
        try {
                if (this->isEmpty()) { throw 1; }
                char value = this->firstVal();
                this->removeFromFront();
                return value;
        }
        catch (int e) {
                cout << "Call to dequeue() generated an exception, because the queue is empty" << endl;
        }
}


char& Queue::front() {
        try {
                if (this->isEmpty()) { throw 2; }
                char val = this->firstVal();
                char& valRef = val;
                return valRef;
        }
        catch (int e) {
                cout << "Call to front() generated an exception, because the queue is empty" << endl;
        }
}