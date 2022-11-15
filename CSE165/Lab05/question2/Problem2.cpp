// Lab 05; Problem 2 - Jason Petersen
// Create a vector< Counted*> and fill it with pointers 
// to new Counted objects (from Exercise 1). Move through 
// the vector and print the Counted objects, then move 
// through again and delete each one.
#include <iostream>
#include <vector>
using namespace std;

class Counted {
    private:
    int id;
    static int count;
    public: // constructor and destructor print on use
    Counted() : id(count++) {
        cout << "An object is being created is created, id: " << id << endl;
    }
    ~Counted() {
        cout << "The created object is being destroyed, id: " << id << endl;
    }
    // prints Counted's ID
    void print() {
        cout << id << " ";
    }
};

// initialize count
int Counted::count = 0;

int main() {
    // create vector
    vector<Counted*> v;
    int vsize = 5;
    // fill vector
    for (int i = 0; i < vsize; i++) {
        v.push_back(new Counted);
    }

    // print vector of Counted IDs in array format
    cout << "Vector of Counted objects: [ ";
    for (int i = 0; i < vsize; i++) {
        (*v[i]).print();
    }
    cout << "]" << endl;

    // delete using vector functions
    for (int i = 0; i < vsize; i++) {
        Counted* t = v.back();
        v.pop_back();
        delete t;
    }

    return 0;
}