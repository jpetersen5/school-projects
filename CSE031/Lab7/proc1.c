#include <stdio.h>


int sum(int m, int n) {
        return m + n;
}

int main() {
        int m = 10;
        int n = 5;

        printf("%d\n", sum(m,n));

        return 0;
}