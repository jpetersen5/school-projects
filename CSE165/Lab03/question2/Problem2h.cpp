// Lab 03; Problem 2 - Jason Petersen

#include "Problem2h.h"
#include <iostream>
#include <fstream>

// default constructs empty string from empty (no) file
Text::Text() {
    std::cout << "Constructing with no file" << std::endl;
    filetext = "";
}

// constructs Text string from given filename
Text::Text(std::string fileName) {
    std::cout << "Constructing with file " << fileName << std::endl;
    
    // initialize and read file
    // repurposed code, credit https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    std::getline(std::ifstream(fileName), filetext, '\0');
}

// returns contents of filetext
std::string Text::contents() {
    return filetext;
}