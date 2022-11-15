// Lab 03; Problem 2 - Jason Petersen
// Create a Text class that contains a string object to 
// hold the text of a file. Give it two constructors: a 
// default constructor and a constructor that takes a 
// string argument that is the name of the file to open. 
// When the second constructor is used, open the file 
// and read the contents into the string member object. 
// Add a member function contents() to return the strings 
// so (for example) it can be printed. In main(), open a 
// file using Text and print the contents.

#include <iostream>
#include "Problem2h.h"
using namespace std;

// creates a Text object and inputs dummy file
int main() {
    Text myfile("text.txt");
    cout << myfile.contents() << endl;

    return 0;
}