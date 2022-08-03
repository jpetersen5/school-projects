#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printArr(int *a, int size, char *name){
        //Your code here
        printf("%s array's contents: ",name);
        for (int i = 0; i < size; i++) printf("%d ",*(a + i));
        printf("\n");
}

int* arrCopy(int *a, int size){
        //Your code here
        int *aC = (int *) malloc (size * sizeof(int)); // dynamically create copy

        // loop in reverse
        for (int i = 0; i < size; i++) { // copied array pointer increments from 0, original array pointer decrements from the end of the "array"
                *(aC + i) = *(a + size - 1 - i);
        }

        return aC;
}

int main(){
    int n;
    int *arr;
    int *arr_copy;
    int i;
    printf("Enter the size of array you wish to create: ");
    scanf("%d", &n);

    //Dynamically create an int array of n items
    //Your code here
    arr = (int *) malloc (n * sizeof(int));

    //Ask user to input content of array
    //Your code here
    for (i = 0; i < n; i++) {
        printf("Enter array element #%d: ",i + 1);
        scanf("%d",(arr + i));
    }
    printf("\n");

/*************** YOU MUST NOT MAKE CHANGES BEYOND THIS LINE! ***********/

    //Print original array
    printArr(arr, n, "Original");

    //Copy array with contents in reverse order
    arr_copy = arrCopy(arr, n);

    //Print new array
    printArr(arr_copy, n, "Copied");

    printf("\n");

    return 0;
}