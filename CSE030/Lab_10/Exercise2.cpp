#include <iostream>
#include "Queue_char.h"
using namespace std;


int main() {
        Queue firstQueue;

        cout << "Function call\t\tOutput\t\tFront\tQueue\tRear" << endl;
        cout << "dequeue()\t\t"; firstQueue.dequeue();
        cout << "enqueue(D)\t\t"; firstQueue.enqueue('D'); cout << "\t\t"; firstQueue.print(); cout << endl;
        cout << "enqueue(A)\t\t"; firstQueue.enqueue('A'); cout << "\t\t"; firstQueue.print(); cout << endl;
        cout << "dequeue()\t\t" << firstQueue.dequeue() << "\t\t"; firstQueue.print(); cout << endl;
        cout << "size()\t\t\t" << firstQueue.size() << "\t\t"; firstQueue.print(); cout << endl;
        cout << "enqueue(D)\t\t"; firstQueue.enqueue('D'); cout << "\t\t"; firstQueue.print(); cout << endl;
        string empty = firstQueue.isEmpty() ? "true" : "false";
        cout << "isEmpty()\t\t" << empty << "\t\t"; firstQueue.print(); cout << endl;
        cout << "front()\t\t\t" << firstQueue.front() << "\t\t"; firstQueue.print(); cout << endl;
        cout << "enqueue(T)\t\t"; firstQueue.enqueue('T'); cout << "\t\t"; firstQueue.print(); cout << endl;
        cout << "front()\t\t\t" << firstQueue.front() << "\t\t"; firstQueue.print(); cout << endl;

        return 0;
}