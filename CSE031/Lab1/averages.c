#include <stdio.h>


int main() {
        // initialize variables, input sums and counts
        int input=1, count=1, evenSum=0, evenNum=0, oddSum=0, oddNum=0;

        // while loop to track inputs until a 0 is entered
        while (input != 0) {

                // check for proper grammar
                if ((count == 11 || count == 12) || count == 13) {
                        printf("Please enter the %dth integer: ",count);
                } else if (count % 10 == 1) {
                        printf("Please enter the %dst integer: ",count);
                } else if (count % 10 == 2) {
                        printf("Please enter the %dnd integer: ",count);
                } else if (count % 10 == 3) {
                        printf("Please enter the %drd integer: ",count);
                } else {
                        printf("Please enter the %dth integer: ",count);
                }

                // recieve input
                scanf("%d",&input);
                if (input == 0) {  break;  }

                // sum the digits by modulo and division by 10 to isolate digits
                int n = input;
                if (n < 0) {  n = n / -1;  }
                int mod, sum=0;
                while (n > 0) {
                        mod = n % 10;
                        sum = sum + mod;
                        n = n / 10;
                }

                // use the sum to determine if input should be added to odds or evens
                if (sum % 2 == 0) {
                        evenSum = evenSum + input;
                        evenNum = evenNum + 1;
                } else {
                        oddSum = oddSum + input;
                        oddNum = oddNum + 1;
                }

                // increment
                count = count + 1;
        }

        printf("\n");

        // create averages (typecast) and print
        if (evenNum > 0) {
                double evenAvg = (double) evenSum / evenNum;
                printf("Average of inputs whose digits sum up to an even number: %.2f\n",evenAvg);
        }
        if (oddNum > 0) {
                double oddAvg = (double) oddSum / oddNum;
                printf("Average of inputs whose digits sum up to an odd number: %.2f\n",oddAvg);
        }

        // in case they input nothing
        if (evenNum == 0 && oddNum == 0) {
                printf("There is no average to compute.\n");
        }


        return 0;
}