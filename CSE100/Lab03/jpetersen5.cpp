#include <iostream>
using namespace std;


int maxCrossSubArr(int* arr, int p, int q, int r) {

        // intialize variables
        int leftsum = -2147483647, rightsum = -2147483647;
        int sum = 0;

        // loop to low from mid, sum and compare
        for (int i = q; i >= p; i--) {
                sum += arr[i];
                if (sum > leftsum) {
                        leftsum = sum;
                }
        }

        // reset sum
        sum = 0;

        // loop to high from mid, sum and compare
        for (int i = q + 1; i <= r; i++) {
                sum += arr[i];
                if (sum > rightsum) {
                        rightsum = sum;
                }
        }

        // prevent wrong numbers from being included
        if (leftsum == -2147483647) {  leftsum = 0;  }
        if (rightsum == -2147483647) {  rightsum = 0;  }

        return leftsum + rightsum;

}


int maxSubArr(int* arr, int p, int r) {

        // if arr is only one element
        if (r == p) {  return arr[p];  }

        // create midpoint
        int q = (p + r) / 2;

        // find sums by calling recursively
        int leftsum = maxSubArr(arr,p,q);
        int rightsum = maxSubArr(arr,q+1,r);
        int crosssum = maxCrossSubArr(arr,p,q,r);

        // compare sums and return max
        if (leftsum >= rightsum && leftsum >= crosssum) {
                return leftsum;
        } else if (rightsum >= leftsum && rightsum >= crosssum) {
                return rightsum;
        } else {
                return crosssum;
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

        // call function and print output
        cout << maxSubArr(arr,0,arrSize-1);

        delete[] arr;
        return 0;
}