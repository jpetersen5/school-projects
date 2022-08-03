#include <iostream>
using namespace std;


int partition(int* arr, int p, int r) {
        int x = arr[r];
        int i = p - 1;

        for (int j = p; j < r; j++)
                if (arr[j] <= x) {
                        i++;
                        int temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                }

        int temp2 = arr[i+1];
        arr[i+1] = arr[r];
        arr[r] = temp2;

        return i + 1;
}


int randomPartition(int* arr, int p, int r) {
        int i = rand() % (r + 1 - p) + p; // random integer in the range p to r

        int temp = arr[r];
        arr[r] = arr[i];
        arr[i] = temp;

        return partition(arr,p,r);
}


void randomQuicksort(int* arr, int p, int r) {

        if (p < r) {
                int q = randomPartition(arr,p,r);
                randomQuicksort(arr,p,q-1);
                randomQuicksort(arr,q+1,r);
        }

}


int main() {
        srand(time(NULL));

        // intial variables
        int* arr;
        int arrSize;

        // input array
		cin >> arrSize;
        arr = new int[arrSize];
        for (int i = 0; i < arrSize; i++)
                cin >> arr[i];

        // call function
        randomQuicksort(arr,0,arrSize-1);

        // print output
        for (int i = 0; i < arrSize; i++)
                cout << arr[i] << ";";

        delete[] arr;

        return 0;
}