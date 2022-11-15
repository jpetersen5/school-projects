// Lab 06; Problem 2 - Jason Petersen
// Create a header file (say myHeader1.h) containing a 
// namespace (say myNamespace). Inside the namespace create 
// two function declarations (say fun1 and fun2). Now create 
// a second header file (say myHeader2.h) that includes the 
// first one (i.e., include “myHeader1.h”) and continues the 
// namespace, adding two more function declarations(say fun3 
// and fun4). Now create a cpp file (say main.cpp) that 
// includes the second header file (i.e., include 
// “myHeader2.h”). Inside a function definition (say test1) 
// in main.cpp, call fun1 and fun2 using a scope resolution 
// operator. Inside a separate function definition (say test2) 
// in main.cpp, call fun3 and fun4 using a using directive to 
// your namespace. Inside main(), call test1 and test2.
#include "myHeader2.h"

void test1() {
    myNamespace::fun1();
    myNamespace::fun2();
}

void test2() {
    using namespace myNamespace;

    fun3();
    fun4();
}


int main() {
    test1();
    test2();

    return 0;
}