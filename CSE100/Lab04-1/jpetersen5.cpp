#include <iostream>
using namespace std;


int left(int ind)   {  return 2 * ind;  }
int right(int ind)  {  return 2 * ind + 1;  }


void maxHeapify(int* arr, int sz, int ind) {
        int max;
        int l = left(ind);
        int r = right(ind);

        // compare elements to find max value's index
        max = (l < sz && arr[l] > arr[ind]) ? l : ind;
        max = (r < sz && arr[r] > arr[max]) ? r : max;

        // max is larger value than given index
        if (max != ind) {

                // swap places so max value rises
                int temp = arr[ind];
                arr[ind] = arr[max];
                arr[max] = temp;

                // recurse so subtree doesn't violate max heap
                maxHeapify(arr, sz, max);
        }

}


void buildMaxHeap(int* arr, int sz) {

        for (int i = sz / 2; i >= 0; i--)
                maxHeapify(arr, sz, i);

}


void heapsort(int* arr, int sz) {

        // build max heap
        buildMaxHeap(arr, sz);

        for (int i = sz - 1; i >= 0; i--) {

                // swap max num to correct position (end of subarray)
                int temp = arr[0];
                arr[0] = arr[i];
                arr[i] = temp;

                // decrement size as heap gets smaller
                sz--;

                // restore max heap
                maxHeapify(arr, sz, 0);

        }

}


int main() {

        // intial variables
        int* arr;
        int arrSize;

        // input array
        cin >> arrSize;
        arr = new int[arrSize];
        for (int i = 0; i < arrSize; i++)
                cin >> arr[i];

        // call function
        heapsort(arr,arrSize);

        // print output
        for (int i = 0; i < arrSize; i++)
                cout << arr[i] << ";";

        delete[] arr;

        return 0;
}