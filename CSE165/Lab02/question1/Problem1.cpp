// Lab 02; Problem 1 - Jason Petersen
// Write a function that takes a char* argument. Using new, 
// dynamically allocate an array of char that is the size 
// of the char array that’s passed to the function. Using 
// array indexing, copy the characters from the argument to 
// the dynamically allocated array (don’t forget the null 
// terminator) and return the pointer to the copy. In your 
// main( ), test the function by passing a static quoted 
// character array, then take the result of that and pass 
// it back into the function. Print both strings and both 
// pointers so you can see they are different storage. 
// Using delete, clean up all the dynamic storage.
#include <iostream>
using namespace std;

char* charfunc(char* charArr) {
    // calculate size of input array
    int size = sizeof(charArr) / sizeof(char);
    // dynamically allocate new array
    char* charArrCopy = new char(size);

    // copy
    for (int i = 0; i < size; i++) {
        charArrCopy[i] = charArr[i];
    }

    return charArrCopy;
}

int main() {
    // call function to initialize arrays
    char* firstArr = charfunc("Hello");
    char* secondArr = charfunc(firstArr);

    // output
    cout << "char array 1: " << firstArr << endl 
    << "pointer: " << &firstArr << endl << endl;
    cout << "char array 2: " << secondArr << endl 
    << "pointer: " << &secondArr << endl << endl;

    delete[] firstArr;
    delete[] secondArr;

    return 0;
}