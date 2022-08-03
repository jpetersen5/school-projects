#include <iostream>
using namespace std;


void sortArr(bool order, int arr[], int sz) {
        int saved;
        int j;
        // if descending
        if (order) {
                for (int i = 1; i < sz; i++) {
                        saved = arr[i];
                        j = i;
                        while (j > 0 && arr[j-1] < saved) {
                                arr[j] = arr[j-1];
                                j = j-1;
                        }
                        arr[j] = saved;
                }
        } else { // if ascending
                for (int i = 1; i < sz; i++) {
                        saved = arr[i];
                        j = i;
                        while (j > 0 && arr[j-1] > saved) {
                                arr[j] = arr[j-1];
                                j = j-1;
                        }
                        arr[j] = saved;
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