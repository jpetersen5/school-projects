#include <iostream>
using namespace std;


int main() {

        int* arr;
        int arrSize = 1;

        // recieve input
        cin >> arrSize;
        arr = new int[arrSize];

        // initial input
        for (int i = 0; i < arrSize; i++) {  cin >> arr[i];  }

        // take input and sort
        int i, j, k;
        for (i = 1; i < arrSize; i++) {
                k = arr[i];
                j = i - 1;

                // moves any numbers larger than k up one element until there is no more larger elements
                while (arr[j] > k && j >= 0) {
                        arr[j+1] = arr[j];
                        j = j - 1;
                }

                // move k to new open space
                arr[j+1] = k;

                // print as function runs
                for (int c = 0; c < i + 1; c++) {
                        cout << arr[c] << ";";
                }
                cout << endl;

        }


        // free space
        delete[] arr;

        return 0;
}