#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// create node structure for linked list implementation
// x and y are locations on wordsearch grid, step is step number
struct Node {
        int x, y, step;
        struct Node* next;
};

// adds node to the end of the linked list, provided the head
// grid locations are given by i and j, step is determing from
// previous Node's step value + 1
void addNode(struct Node** head, int i, int j) {
        struct Node *temp = *head;
        int s = 1;

        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->x = i;
        new_node->y = j;
        if (head == NULL) {
                (*head) = new_node;
                return;
        }

        while(temp->next != NULL) {
                temp = temp->next;
                s = temp->step + 1;
        }
        new_node->step = s;

        temp->next = new_node;
}

// deletes node at the end of the list and sets previous Node's
// next value to NULL (prevent double-free error)
void delNode(struct Node** head) {
        struct Node *prev = *head;
        struct Node *temp = prev->next;

        if (temp == NULL) {
                free(prev);
                return;
        }

        while(temp->next != NULL) {
                prev = prev->next;
                temp = temp->next;
        }

        prev->next = NULL;
        free(temp);
}


// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
struct Node* path(char** arr, char* word);
int searchNext(char** arr, char* word, int x, int y, struct Node** head);
char* concat(char* s1, char* s2);
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
        int i, j, step;

        // initialize head Node for search path (only used for baseline)
        // the grid location is -1,-1 since this Node isn't used in
        // creating and printing the step path. Node's with 0 as step
        // value are the "head" Nodes that mark path beginnings
        struct Node* head = (struct Node*)malloc(sizeof(struct Node));
        head->x = -1;
        head->y = -1;
        head->step = 0;
        head->next = NULL;

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

        // initialize the search path as grid of strings
        char ***searchPath = (char***)malloc(bSize * sizeof(char**));

        // fill searchPath with all 0's initially
		for (i = 0; i < bSize; i++) {
                *(searchPath + i) = (char**)malloc(bSize * sizeof(char*));
                for (j = 0; j < bSize; j++) {
                        *(*(searchPath + i) + j) = (char*)malloc(bSize * sizeof(char));
                        *(*(searchPath + i) + j) = "0";
                }
        }

        // creates a linked list of the search paths
        // integer "search" is 0 or 1 as a boolean for determining a
        // complete path. searchNext is called recursively to return
        // a 0 or 1, based on whether it arrives at a NULL character
        // or not. If a complete path is found, a new "head" Node
        // with step value 0 is created so the loop can continue and
        // find a new path. Paths are able to overlap so long as the
        // beginning letter does not overlap (implicit). When a path
        // does not complete, searchNext recursively deletes the
        // Nodes it created, as well as the beginning letter
        int search = 0;
        for (i = 0; i < bSize; i++) {
                for (j = 0; j < bSize; j++) {
                        if (*(*(arr + i) + j) == *word) {
                                addNode(&head,i,j);
                                search = searchNext(arr, word + 1, i, j, &head);
                                if (search) {
                                        addNode(&head,-1,-1);
                                        struct Node* tempHead;
                                        tempHead = head->next;
                                        while (tempHead->next != NULL)
                                                tempHead = tempHead->next;
                                        tempHead->step = 0;
                                        continue;
                                }
                                delNode(&head);
                        }
                }
        }

        // edit search path based on finished linked list
        // a temp Node is created at the first head to search
        // through all Nodes, replacing 0's or appending step
        // numbers to given locations. Head Nodes, with step value
        // of 0, are skipped in this process. Integers are
        // converted to strings with sprintf, then appended to
        // correct location using a concatenate function
        struct Node* temp;
        temp = head->next;
        while (temp != NULL) {
                if (temp->step == 0) {
                        temp = temp->next;
                        continue;
                }
                char* tempStep = (char*)malloc(sizeof(char) + 1);
                sprintf(tempStep, "%d", temp->step);
				if (*(*(searchPath + temp->x) + temp->y) == "0")
                        *(*(searchPath + temp->x) + temp->y) = tempStep;
                else
                        *(*(searchPath + temp->x) + temp->y) = concat(*(*(searchPath + temp->x) + temp->y), tempStep);
                temp = temp->next;
        }

        // print search path if head is not the only node
        if (head->next != NULL) {
                printf("Word found!\nPrinting the search path:\n");
                for (i = 0; i < bSize; i++) {
                        for (j = 0; j < bSize; j++)
                                printf("%s\t", *(*(searchPath + i) + j));
                        printf("\n");
                }
        }
        else
                printf("Word not found!\n");
}

// recursively finds the next letter until out of letters
// updates linked list as it goes, deletes if path fails
// upon finding null character, path is a success and can
// return 1 (true). Otherwise, if a character is not found,
// return 0 (false) as the path is a failure. The ranges
// -1 < i, j < 1 are to search the 8 values surrounding the
// given location. If statements ensure that the values are
// within bounds and will not cause a segfault
int searchNext(char** arr, char* word, int x, int y, struct Node** head) {
        if (*word == '\0') {
                return 1;
        }

        int search = 0;
        for (int i = -1; i <= 1; i++) {
                if (x + i < 0 || x + i >= bSize) {
                        continue;
                }
                for (int j = -1; j <= 1; j++) {
                        if ((y + j < 0 || y + j >= bSize) || (i == 0 && j == 0)) {
                                continue;
                        }
                        if (*(*(arr + x + i) + y + j) == *word) {
                                addNode(head, x+i, y+j);
                                search = searchNext(arr,word + 1,x + i,y + j,head);
                                if (search)
                                        return search;
                                delNode(head);
                       }
                }
        }

        return 0;
}


// concatenates two strings (modified from stack overflow)
char* concat(char *s1, char *s2) {
        char *result = malloc(strlen(s1) + strlen(s2) + 1);
        strcpy(result, s1);
        strcat(result, s2);
        return result;
}