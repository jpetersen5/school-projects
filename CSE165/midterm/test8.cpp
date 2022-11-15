#include <iostream>
using namespace std;

struct A {
    public:
    A() { cout << "A\n"; }
};

class B : public A {
    public:
    B() { cout << "B\n"; }
};

int main() {
    if (true) { B b; }
    A* a = new B;
    delete a;
    return 0;
}