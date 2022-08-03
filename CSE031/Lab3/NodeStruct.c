#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct Node {
    int iValue;
    float fValue;
    struct Node *next;
};

int main() {

    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    head->iValue = 5;
    head->fValue = 3.14;

        // Insert extra code here
        printf("head:\t%p\n",head);
        printf("\t%p\n",&head);
        printf("iValue:\t%p\n",&(head->iValue));
        printf("fValue:\t%p\n",&(head->fValue));
        printf("next:\t%p\n",&(head->next));

        return 0;
}