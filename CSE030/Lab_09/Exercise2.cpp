#include <iostream>
#include "Stack_char.h"
using namespace std;


int main() {
        Stack firstStack;

        cout << "Function call\t\tOutput\t\tStack Contents" << endl;
        string empty = firstStack.isEmpty() ? "true" : "false";
        cout << "isEmpty()\t\t" << empty << "\t\t"; firstStack.print(); cout << endl;
        cout << "push(A)\t\t\t"; firstStack.push('A'); cout << "\t\t"; firstStack.print(); cout << endl;
        cout << "push(Y)\t\t\t"; firstStack.push('Y'); cout << "\t\t"; firstStack.print(); cout << endl;
        cout << "size()\t\t\t" << firstStack.size() << "\t\t"; firstStack.print(); cout << endl;
        cout << "pop()\t\t\t" << firstStack.pop() << "\t\t"; firstStack.print(); cout << endl;
        empty = firstStack.isEmpty() ? "true" : "false";
        cout << "isEmpty()\t\t" << empty << "\t\t"; firstStack.print(); cout << endl;
        cout << "push(D)\t\t\t"; firstStack.push('D'); cout << "\t\t"; firstStack.print(); cout << endl;
        cout << "top()\t\t\t" << firstStack.top() << "\t\t"; firstStack.print(); cout << endl;
        cout << "push(T)\t\t\t"; firstStack.push('T'); cout << "\t\t"; firstStack.print(); cout << endl;
        cout << "pop()\t\t\t" << firstStack.pop() << "\t\t"; firstStack.print(); cout << endl;

        return 0;
}