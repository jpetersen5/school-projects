#include <iostream>
#include "Queue.h"
using namespace std;


int main() {
        Queue firstQueue;

        cout << "Size of Queue: " << firstQueue.size() << endl;

        cout << "is empty? " << firstQueue.isEmpty() << endl;

        cout << "Here is the Queue: [";
        firstQueue.print();
        cout << "]" << endl << endl;

        cout << "Testing exceptions..." << endl;

        firstQueue.dequeue();
        firstQueue.front();

        cout << endl;

        cout << "Enqueueing 10 elements..." << endl;

        firstQueue.enqueue(1);
        firstQueue.enqueue(2);
        firstQueue.enqueue(3);
        firstQueue.enqueue(4);
        firstQueue.enqueue(5);
        firstQueue.enqueue(6);
        firstQueue.enqueue(7);
        firstQueue.enqueue(8);
        firstQueue.enqueue(9);
        firstQueue.enqueue(100);

        cout << endl;

        cout << "Front of Queue: " << firstQueue.front() << endl;

        cout << "Size of Queue: " << firstQueue.size() << endl;

        cout << "is empty? " << firstQueue.isEmpty() << endl;

        cout << "Here is the Queue: [";
        firstQueue.print();
        cout << "]" << endl << endl;

        cout << "Dequeueing 2 elements..." << endl;
        firstQueue.dequeue();
        firstQueue.dequeue();

        cout << "Here is the Queue: [";
        firstQueue.print();
		cout << "]" << endl;

        return 0;
}