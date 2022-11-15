// Lab 05; Problem 3 - Jason Petersen
//  In AddingVirtuals.cpp, make all the member functions 
// of Pet pure virtual, but provide a definition for 
// name(). Fix Dog as necessary, using the base-class 
// definition of name().

//: C15:AddingVirtuals.cpp
// Adding virtuals in derivation
#include <iostream>
#include <string>
using namespace std;

class Pet {
    string pname;

    public: 
    Pet(const string& petName) : pname(petName) {}
    virtual string name() = 0;
    virtual string speak() = 0;
};

// name() definition
string Pet::name() { return pname; }

class Dog : public Pet {
    public:
    Dog(const string& petName) : Pet(petName) {}
    // New virtual function in the Dog class:
    virtual string sit() {
        return Pet::name() + " sits";
    }
    string speak() { // Override
        return Pet::name() + " says 'Bark!'";
    }
    string name() {
        return Pet::name();
    }
};

int main() {
    Pet* p = new Dog("bob");
    cout << p->speak() << endl;

    delete p;
    return 0;
}