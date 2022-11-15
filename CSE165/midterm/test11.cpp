#include <iostream>
using namespace std;

struct A {
    public:
    A() { cout << "A\n"; }
    virtual ~A() { cout << "~A\n"; }
};

class B : public A {
    public:
    B() { cout << "B\n"; }
    virtual ~B() { cout << "~B\n"; }
};

class C : public B {
    public:
    C() { cout << "C\n"; }
    virtual ~C() { cout << "~C\n"; }
};

int main() {
    A* a = new B;
    if (true) { C c; }
    delete a;
    return 0;
}