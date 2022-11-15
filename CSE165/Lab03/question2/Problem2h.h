// Lab 03; Problem 2 - Jason Petersen

#ifndef PROBLEM2H_H
#define PROBLEM2H_H
#include <string>

// Text class to contain the contents of a
// file into a string
class Text {
    std::string filetext;

    public:
        Text();
        Text(std::string fileName); // constructor given filename to open
        std::string contents();

};

#endif