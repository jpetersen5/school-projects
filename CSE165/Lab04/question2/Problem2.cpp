// Lab 04; Problem 2 - Jason Petersen
// Create a function that takes an argument of a reference 
// to a pointer to a pointer and modifies that argument. 
// In main( ), call the function.
#include <iostream>
using namespace std;

void refptrptr(char**& inp);

int main() {
    char hello[] = "Hello World";
    char* hPtr = hello;
    char** hPtrPtr = &hPtr;

    cout << hello << endl;
    cout << &hPtr << " ---> " << *hPtr << endl;
    cout << &hPtrPtr << " ---> " << &(*hPtrPtr) << endl;

    cout << "modify pointer..." << endl;
    refptrptr(hPtrPtr);
    cout << *(*hPtrPtr) << endl;

    return 0;
}

void refptrptr(char**& inp) {
    (*inp) += 10;
}