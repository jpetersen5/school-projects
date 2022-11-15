// Lab 05; Problem 1 - Jason Petersen
// Create a class Counted that contains an int id and a static 
// int count. The default constructor should begin: 
// Counted() : id(count++). It should also print its id and 
// that it’s being created. The destructor should print that 
// it’s being destroyed and its id. Test your class.
#include <iostream>
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
};

// initialize count
int Counted::count = 0;

int main() {
    // create on stack
    Counted count0;
    
    // create on smaller scope
    if (true) { Counted count1; }

    // create on heap and delete
    Counted* count2 = new Counted;
    delete count2;

    return 0;
}