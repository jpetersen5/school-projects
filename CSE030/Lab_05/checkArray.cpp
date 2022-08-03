#include <iostream>
#include <fstream>
using namespace std;


int checkArraySort(string* A, int array_size) {
        // pass through any equal strings at the beginning of the array
        int j = 0;
        while (A[j] == A[j+1]) {
                j++;
        }

        // check the first two strings for order
        int sorted = A[j] < A[j+1] ? 1 : -1;

        // based on that order, check the rest of the strings order
        for (int i = j; i < array_size - 1; i++) {
                if (sorted == -1 && A[i] > A[i+1]) {
                        continue;
                } else if (sorted == 1 && A[i] < A[i+1]) {
                        continue;
                } else { // unsorted if strings don't follow first two order
                        return 0;
                }
        }

        // return ascending or descending
        return sorted;
}


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
        for (int i = 0; i < lines; i++) {
                getline(wordfile,word);
                wordfile >> wordsArr[i];
        }
        wordfile.close();

        // check using checkArraySort
        int sorted = checkArraySort(wordsArr, lines - 1);
        if (sorted == -1) {
                cout << "The array is sorted in descending order!" << endl;
        } else if (sorted) {
                cout << "The array is sorted in ascending order!" << endl;
        } else {
                cout << "The array is not sorted!" << endl;
        }

        delete[] wordsArr;

        return 0;
}