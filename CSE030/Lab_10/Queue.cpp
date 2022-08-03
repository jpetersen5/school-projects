#include <iostream>
#include "Queue.h"
using namespace std;


// constructor and destructor do nothing
Queue::Queue() {}
Queue::~Queue() {}


void Queue::enqueue(int value) {
        this->insertAtBack(value);
}


int Queue::dequeue() {
        try {
                if (this->isEmpty()) { throw 1; }
                int value = this->firstVal();
                this->removeFromFront();
                return value;
        }
        catch (int e) {
                cout << "Call to dequeue() generated an exception, because the queue is empty" << endl;
        }
}


int& Queue::front() {
        try {
                if (this->isEmpty()) { throw 2; }
                int val = this->firstVal();
                int& valRef = val;
                return valRef;
        }
        catch (int e) {
                cout << "Call to front() generated an exception, because the queue is empty" << endl;
        }
}