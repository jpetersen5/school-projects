#include <iostream>
using namespace std;


void merge(int* arrToSort, int p, int q, int r) {

        // initialize variables
        int* arrL;
        int* arrR;
        int n1 = q - p + 1;
        int n2 = r - q;

        // create left and right arrays
        arrL = new int[n1+1];
        arrR = new int[n2+1];

        // fill left array
        // cout << "left: ";
        for (int i = 0; i < n1; i++) {
                arrL[i] = arrToSort[p + i];
                // cout << arrL[i] << " ";
        }
        // cout << endl;

        // fill right array
        // cout << "right: ";
        for (int i = 0; i < n2; i++) {
                arrR[i] = arrToSort[q + i + 1];
                // cout << arrR[i] << " ";
        }
        // cout << endl;

        // cap arrays
        arrL[n1] = 2147483647;
        arrR[n2] = 2147483647;

        int i=0,j=0;
        // merge
        // cout << "merge: ";
        for (int k = p; k < r + 1; k++) {

                // left array is less than right array
                if (arrL[i] <= arrR[j]) {
                        arrToSort[k] = arrL[i];
                        i++;
                        // cout << arrToSort[k] << " ";
                } else {
                        arrToSort[k] = arrR[j];
                        j++;
                        // cout << arrToSort[k] << " ";
                }

        }
        // cout << endl << endl;
		
		delete[] arrL;
		delete[] arrR;
}


void mergesort(int* arrToSort, int p, int r) {

        // ensure elements > 1
        if (p < r) {

                // calculate midpoint
                int q = (p + r) / 2;

                // recurse
                mergesort(arrToSort,p,q);
                mergesort(arrToSort,q+1,r);

                // merge
                merge(arrToSort,p,q,r);

        }

}


int main() {

        // intial variables
        int* arr;
        int arrSize;

        // input array
        cin >> arrSize;
        arr = new int[arrSize];
        for (int i = 0; i < arrSize; i++) {     cin >> arr[i];  }

        // call function
        mergesort(arr,0,arrSize-1);

        // print output
        for (int i = 0; i < arrSize; i++) {     cout << arr[i] << ";";  }
        // cout << endl;

        delete[] arr;
        return 0;

}