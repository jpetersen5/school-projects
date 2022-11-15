// Lab 02; Problem 2 - Jason Petersen
// Write two classes, each of which has a member 
// function that takes a pointer to an object of the 
// other class. Create instances of both objects in 
// main() and call the aforementioned member function 
// in each class.
#include <iostream>
using namespace std;
class c1;
class c2;

// only function is to print a pointer of a c2 object
class c1 {
    public: 
        void printPoint(c2 *objPoint) {
            cout << "Class 2 (c2) object pointer: " 
            << objPoint << endl;
        }
};

// only function is to print a pointer of a c1 object
class c2 {
    public:
        void printPoint(c1 *objPoint) {
            cout << "Class 1 (c1) object pointer: " 
            << objPoint << endl;
        }
};

int main() {
    // initialize objects
    c1 class1Object;
    c2 class2Object;

    // call class functions
    class1Object.printPoint(&class2Object);
    class2Object.printPoint(&class1Object);

    return 0;
}