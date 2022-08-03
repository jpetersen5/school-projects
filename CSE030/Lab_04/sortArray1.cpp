#include <iostream>
using namespace std;


void sortArr(bool order, int arr[], int sz) {
        // if descending
        if (order) {
                for (int i = 0; i < sz - 1; i++) {
                        // initialize max value index
                        int imax = i;
                        // loop to check for maximum value (using indices beyond already found maximums)
                        for (int j = i + 1; j < sz; j++) {
                                if (arr[j] > arr[imax]) {
                                        imax = j;
                                }
                        }
                        // swap with a temporary variable
                        int temp;
                        temp = arr[i];
                        arr[i] = arr[imax];
                        arr[imax] = temp;
                }
        } else { // if ascending
                for (int i = 0; i < sz - 1; i++) {
                        // initialize min value index
                        int imin = i;
                        // loop to check for minimum value (using indices beyond already found minimums)
                        for (int j = i + 1; j < sz; j++) {
                                if (arr[j] < arr[imin]) {
                                        imin = j;
                                }
                        }
                        // swap with a temporary variable
                        if (imin != i) {
                                int temp;
                                temp = arr[i];
                                arr[i] = arr[imin];
                                arr[imin] = temp;
                        }
                }
        }
}


int main() {
        // initialize size of array and ask for input
        int sz;
        cout << "Enter the size of the array: ";
        cin >> sz;

        // check for valid size
        if (sz < 1) {
                cout << "ERROR: you entered an incorrect value for the array size!" << endl;
                return 0;
        }

        // initialize array to size and ask for value with a loop
        int arr [sz];
        cout << "Enter the numbers in the array, separated by a space, and press enter: ";
        for (int i = 0; i < sz; i++) {
                cin >> arr[i];
        }

        // initialize order and ask for input
        bool order;
        cout << "Sort in ascending (0) or descending (1) order? ";
        cin >> order;

        // call sortArr and print sorted array
        sortArr(order, arr, sz);
        string sorted = order ? "descending" : "ascending";
        cout << "This is the sorted array in " + sorted + " order: " << endl;
        for (int i = 0; i < sz; i++) {
                cout << arr[i] << " ";
        }
        cout << endl;

        return 0;
}