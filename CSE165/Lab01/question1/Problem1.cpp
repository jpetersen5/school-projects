// Lab 01; Problem 1 - Jason Petersen
// Using Stream2.cpp and Numconv.cpp as guidelines, create a 
// program that asks for the radius of a circle and prints the
// area of that circle. You can just use the ‘*’ operator to 
// square the radius. Do not try to print out the value as 
// octal or hex (these only work with integral types).
#include <iostream>
using namespace std;

int main() {
    // initialize variables
    double r, pi = 3.14159;
    cout << "Enter the radius of a circle: ";
    cin >> r;
    // calculate area (pi*r^2) as decimal and value of pi
    cout << "Area: " << pi * r * r << " or " << r * r << "pi." << endl;

    return 0;
}