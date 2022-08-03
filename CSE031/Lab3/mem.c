#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

 int main() {
        int num;
        int *ptr;
        int **handle;

        num = 14;
        ptr = (int *)malloc(2 * sizeof(int));
        *ptr = num;
        handle = (int **)malloc(1 * sizeof(int *));
        *handle = ptr;

        // Insert extra code here
        printf("num:\t%d\t\t%p\n",num,&num);
        printf("ptr:\t%p\t%p\n",ptr,&ptr);
        printf("handle:\t%p\t%p\n",handle,&handle);

        return 0;
}