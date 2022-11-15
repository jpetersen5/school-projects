// Lab 03; Problem 1 - Jason Petersen

//: C05:Handle.h
// Handle classes
#ifndef HANDLE_H
#define HANDLE_H

class Handle {
    struct Cheshire; // Class declaration only
    Cheshire* smile;

    public:
        Handle();
        ~Handle();
        int read();
        void change(int);
};

#endif // HANDLE_H ///:~ 