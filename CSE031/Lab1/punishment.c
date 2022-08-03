#include <stdio.h>


int main() {
        // initialize, recieve input, and confirm validity with while loop
        int repeat;

        printf("Enter the number of times to repeat the punishment phrase: ");
        scanf("%d", &repeat);

        while (repeat <= 0) { // can only print positive integer number of lines
                printf("You entered an invalid value for the number of repetitions!\n");
                printf("Enter the number of times to repeat the punishment phrase: ");
                scanf("%d", &repeat);
        }

        printf("\n");


        // repeat same process for typo line
        int typo;

        printf("Enter the repetition line where you want to introduce the typo: ");
        scanf("%d", &typo);

        while (typo <= 0 || typo > repeat) { // can't have a typo on a line greater than the # printed
                printf("You entered an invalid value for the typo placement!\n");
                printf("Enter the repetition line where you want to introduce the typo: ");
                scanf("%d", &typo);
        }

        printf("\n");


        // loop based on inputs, if statement to check for typo line
        int i;
        for (i = 0; i < repeat; i = i + 1) {
                if (i + 1 == typo) {
                        printf("Progranming in c is phun!\n");
                        continue;
                }

                printf("Programming in C is fun!\n");
        }


        return 0;
}