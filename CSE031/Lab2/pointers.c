#include <stdio.h>


int main() {

        int x=0, y=0, *px=&x, *py=&y, arrSize=10;
        int arr[arrSize];

        for (int i = 0; i < arrSize; i++) *(arr+i) = i*2;

        printf("x:  %d\n",x);
        printf("y:  %d\n",y);
        printf("px: %p\n",px);
        printf("py: %p\n",py);
        printf("arr[0]: %d\n",arr[0]);

        printf("[ ");
        for (int i = 0; i < arrSize; i++) printf("%d ",*(arr+i));
        printf("]\n");

        printf("value that point arr points to: %d\n",*arr);
        printf("address of arr: %p\n",arr);

        return 0;

}