#include <iostream>
#include <fstream>
using namespace std;


int main() {
        // initialize opening input file
        ifstream wordfile("words_in.txt");

        // initialize variables for file
        string word;
        int lines = 0;

        // loop to count lines
        while (!wordfile.eof()) {
                getline(wordfile,word);
                lines = !word.empty() ? lines + 1 : lines;
        }
        wordfile.close();

        // create array and loop again to assign values
        string * wordsArr;
        wordsArr = new string [lines];
        wordfile.open("words_in.txt",ios::in);
        wordfile >> wordsArr[0];
        for (int i = 1; i < lines; i++) {
                getline(wordfile,word);
                wordfile >> wordsArr[i];
        }
        wordfile.close();

        // create output file
        ofstream wordsout;
        wordsout.open("words_out.txt");

        // write to output file
        for (int i = 0; i < lines; i++) {
                wordsout << wordsArr[i] << endl;
        }
        wordsout.close();

        delete[] wordsArr;

        return 0;
}