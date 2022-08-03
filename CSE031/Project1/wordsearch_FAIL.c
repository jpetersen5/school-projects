#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void resetPath(char*** path);
int nextStep(char*** path, char** arr, char* word, int c, int x, int y);
void stepAppend(char*** path, int c, int x, int y);
int bSize;


// Main function, DO NOT MODIFY
int main(int argc, char **argv) {
        if (argc != 2) {
                fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
                return 2;
        }
        int i, j;
        FILE *fptr;

        // Open file for reading puzzle
        fptr = fopen(argv[1], "r");
        if (fptr == NULL) {
                printf("Cannot Open Puzzle File!\n");
                return 0;
        }

        // Read the size of the puzzle block
        fscanf(fptr, "%d\n", &bSize);

        // Allocate space for the puzzle block and the word to be searched
        char **block = (char**)malloc(bSize * sizeof(char*));
        char *word = (char*)malloc(20 * sizeof(char));

        // Read puzzle block into 2D arrays
        for(i = 0; i < bSize; i++) {
                *(block + i) = (char*)malloc(bSize * sizeof(char));
                for (j = 0; j < bSize - 1; ++j) {
                        fscanf(fptr, "%c ", *(block + i) + j);
                }
                fscanf(fptr, "%c \n", *(block + i) + j);
        }
        fclose(fptr);

        printf("Enter the word to search: ");
        scanf("%s", word);

        // Print out original puzzle grid
        printf("\nPrinting puzzle before search:\n");
        printPuzzle(block);

        // Call searchPuzzle to the word in the puzzle
        searchPuzzle(block, word);

        return 0;
}

void printPuzzle(char** arr) {
        // This function will print out the complete puzzle grid (arr).
        // It must produce the output in the SAME format as the samples
        // in the instructions.
        // Your implementation here...

        int i, j;
        for (i = 0; i < bSize; i++) {
                for (j = 0; j < bSize; j++) {
                        printf("%c ", *(*(arr + i) + j));
                }
                printf("\n");
        }
        printf("\n");

}

void searchPuzzle(char** arr, char* word) {
        // This function checks if arr contains the search word. If the
        // word appears in arr, it will print out a message and the path
        // as shown in the sample runs. If not found, it will print a
        // different message as shown in the sample runs.
        // Your implementation here...
        int i, j;

        // check for lower case letters if any, replace with upper case
        // uses ASCII values to search for lower case range, converts
        // to upper case range of letters by subtracting 32
        i = 0;
        while (*(word + i) != '\0') {
                if (*(word + i) > 96 && *(word + i) < 123) {
                        *(word + i) = *(word + i) - 32;
                }
                i = i + 1;
        }
        int wordsize = i;

        // initialize the search path as double array of strings
        // 8 * bSize chosen since path size very likely will not exceed
        // 8 steps in one space
        char ***searchPath = (char***)malloc(bSize * sizeof(char**));

        // fill searchPath with all 0's initially
        for (i = 0; i < bSize; i++) {
                *(searchPath + i) = (char**)malloc(bSize * sizeof(char*));
                for (j = 0; j < bSize; j++) {
                        *(*(searchPath + i) + j) = (char*)malloc(bSize * sizeof(char));
                        *(*(searchPath + i) + j) = "0";
                }
        }

	
        for (i = 0; i < bSize; i++) {
                for (j = 0; j < bSize; j++) {
                        if (*(*(arr + i) + j) == *word) {
                                *(*(searchPath + i) + j) = "1";
                                if (nextStep(searchPath,arr,word,1,i,j)) {
                                        printf("Word found!\n");
                                        printf("Printing the search path:\n");
                                        for (i = 0; i < bSize; i++) {
                                                for (j = 0; j < bSize; j++) {
                                                        printf("%s\t", *(*(searchPath + i) + j));
                                                }
                                                printf("\n");
                                        }
                                }
                        }
                }
        }

}

void resetPath(char*** path) {
        // this function sets all of a searchpath's values to 0
        int i, j;
        for (i = 0; i < bSize; i++) {
                for (j = 0; j < bSize; j++) {
                        *(*(path + i) + j) = "0";
                }
        }
}

int nextStep(char*** path, char** arr, char* word, int c, int x, int y) {
        // this function checks all the values around the letter at
        // x y and returns a bool 1 or 0 if next letter is found. 0
        // returned when not found. recursive to the end of word
        // ensures junk data out of bounds is not checked
        if (*(word + c) == '\0') {
                return 1;
        }

        for (int i = -1; i <= 1; i++) {
                if (x + i < 0 || x + i >= bSize) {
                        continue;
                }
                for (int j = -1; j <= 1; j++) {
                        if ((y + j < 0 || y + j >= bSize) || (i == 0 && j == 0)) {
                                continue;
                        }
                        if (*(*(arr + x + i) + y + j) == *(word + c)) {
                                stepAppend(path,c + 1,x + i,y + j);
								return nextStep(path,arr,word,c + 1,x + i,y + j);
                        }
                }
        }

        // resetPath(path);
        return 0;
}

void stepAppend(char*** path, int c, int x, int y) {
        // correctly appends the step number to the position at which
        // the next letter has been found
        if (*(*(path + x) + y) == "0") {
                char *str = (char*)malloc(sizeof(char) + 2);
                sprintf(str,"%d",c);
                *(*(path + x) + y) = str;
        }
}