// Lab 03; Problem 3 - Jason Petersen

#ifndef PROBLEM3H_H
#define PROBLEM3H_H

// int array class
class intArr {
    int* arr;
    int size;

    public:
        intArr();
        intArr(int inSize);
        ~intArr();
        int getSize();
        int* getArrPoint();

};

#endif