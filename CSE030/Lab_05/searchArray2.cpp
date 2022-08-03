#include <iostream>
#include <fstream>
using namespace std;


int checkArraySort(string* A, int array_size) {
        // check ends for order
        int sorted = A[0] < A[array_size - 1] ? 1 : -1;

        // based on that order, check the rest of the strings order
        for (int i = 0; i < array_size - 1; i++) {
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


int binarySearchL(string* A, int array_size, string key) {
        int start = 0;
        int end = array_size;
        int mid = (start + end) / 2;
        while (A[mid] != A[end-1]) {
                if (A[mid] == key) {
                        return mid;
                }
                if (A[mid] < key) {
                        start = mid;
                } else if (A[mid] > key) {
                        end = mid;
                }
                mid = (start + end) / 2;
        }

        // search failed
        return -1;
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
        wordfile >> wordsArr[0];
        for (int i = 1; i < lines; i++) {
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

        // search using binary search
        string k;
        cout << "Enter a string to search for: ";
        cin >> k;
        int result = binarySearchL(wordsArr,lines,k);
        if (result == -1) {
                cout << "The key " << k << " was not found in the array!" << endl;
        } else {
                cout << "Found key " << k << " at index " << result << endl;
        }

        delete[] wordsArr;

        return 0;
}