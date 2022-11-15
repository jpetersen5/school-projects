// Lab 04; Problem 3 - Jason Petersen
// This exercise creates the design pattern called proxy. 
// Start with a base class Subject and give it three 
// functions: f(), g(), and h(). Now inherit a class 
// Proxy and two classes Implementation1 and 
// Implementation2 from Subject. Proxy should contain a 
// pointer to a Subject, and all the member functions for 
// Proxy should just turn around and make the same calls 
// through the Subject pointer. The Proxy constructor 
// takes a pointer to a Subject that is installed in the 
// Proxy (usually by the constructor). In main(), create 
// two different Proxy objects that use the two different 
// implementations. Now modify Proxy so that you can 
// dynamically change implementations.
#include <iostream>
using namespace std;

class Subject {
    public:
        virtual void f() {
            cout << "Subject f()" << endl;
        }
        virtual void g() {
            cout << "Subject g()" << endl;
        }
        virtual void h() {
            cout << "Subject h()" << endl;
        }
};

class Proxy : public Subject {
    private:
        Subject* subPtr;

    public:
        Proxy(Subject* sub) {
            subPtr = sub;
        }

        void f() {
            subPtr->f();
        }
        void g() {
            subPtr->g();
        }
        void h() {
            subPtr->h();
        }

        void implementation(Subject* sub) {
            subPtr = sub;
        }

};

class Implementation1 : public Subject {
    public:
        void f() {
            cout << "Implementation1 f()" << endl;
        }
        void g() {
            cout << "Implementation1 g()" << endl;
        }
        void h() {
            cout << "Implementation1 h()" << endl;
        }
};

class Implementation2 : public Subject {
    public:
        void f() {
            cout << "Implementation2 f()" << endl;
        }
        void g() {
            cout << "Implementation2 g()" << endl;
        }
        void h() {
            cout << "Implementation2 h()" << endl;
        }
};

int main() {
    Implementation1 imp1;
    Implementation2 imp2;

    Proxy prx(&imp1);

    prx.f();
    prx.g();
    prx.h();
    
    prx.implementation(&imp2);

    prx.f();
    prx.g();
    prx.h();

    return 0;
}