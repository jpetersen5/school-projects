// Lab 01; Problem 3 - Jason Petersen
// Write a program that uses a while loop to read words 
// from standard input (cin) into a string. This is an 
// “infinite” while loop, which you break out of (and exit 
// the program) using a break statement. For each word 
// that is read, evaluate it by first using a sequence of if 
// statements to “map” an integral value to the word, 
// and then use a switch statement that uses that 
// integral value as its selector (this sequence of events 
// is not meant to be good programming style; it’s just 
// supposed to give you exercise with control flow). 
// Inside each case, print something meaningful. You 
// must decide what the “interesting” words are and what 
// the meaning is. You must also decide what word will 
// signal the end of the program. Test the program by 
// redirecting a file into the program’s standard input (if 
// you want to save typing, this file can be your program’s 
// source file).
#include <iostream>
using namespace std;

int main() {
    // initialize variables
    string word;
    int wordVal;

    cout << "Enter a word to begin: ";

    // input with words via cin
    while (true) {
        // reset variables each loop
        word = "";
        wordVal = 0;
        cin >> word;

        // break on "bye", otherwise calculate wordVal
        if (word == "bye")
            break;
        else
            for (int i = 0; i < word.length(); i++)
                wordVal += word[i]; // determine using ASCII values
        
        // reduce value to number of switch cases
        wordVal = wordVal % 4;

        // switch cases to print funky stuff
        switch (wordVal) {
            case 0: 
                cout << "You won the lottery! Maybe." << endl;
                break;
            case 1: 
                cout << "This is not an error." << endl;
                break;
            case 2: 
                cout << "Mystery prize." << endl;
                break;
            case 3: 
                cout << "Level up" << endl;
                break;
        }
    }

    return 0;
}