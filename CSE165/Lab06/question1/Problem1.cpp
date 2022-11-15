// Lab 06; Problem 1 - Jason Petersen
// Create a class (say myClass) containing both a const 
// (say float f1) and a non-const (say const float f2) float. 
// Initialize f1 and f2 using the constructor initializer list. 

class myClass {
    private:
    float f1;
    const float f2;

    public:
    myClass() : f1(0), f2(0) {}
};

int main() {
    myClass c1;

    return 0;
}