#include <iostream>
using namespace std;

const int vecSize = 10;


// create node structure for bins as a linked list
struct node {
        int* num;
        node* next;
};

// store number data as int* since input is 2D array
struct node* newNode(int* n) {
        node* temp = new node();
        temp->num = n;
        temp->next = NULL;

        return temp;
}


// inserts a new node at the end of the linked list
void insert(node*& head, int* n) {
        if (head == NULL) {
                head = newNode(n);
                return;
        }

        node* temp = head;
        while (temp->next != NULL)
                temp = temp->next;
        temp->next = newNode(n);
}

// delete nodes for sorting stability
int* del(node*& head) {
        if (head == NULL)
                return 0;

        node* temp = head;
        int* n = head->num;

        head = head->next;

        delete temp;
        return n;
}


void radixSort(int** arr, int size, int d) {

        // create buckets
        node** bins;
		bins = new node*[4]; // 4 for digits 0-3 (10 if the problem called for all digits)

        for (int i = 0; i < 4; i++)
                bins[i] = NULL;

        // store rows into bins based on digit values
        for (int i = d - 1; i >= 0; i--) {
                for (int j = 0; j < size; j++)
                        insert(bins[arr[j][i]],arr[j]);

                int x = 0, y = 0;

                // update array
                while (x < 4) {
                        while (bins[x] != NULL)
                                arr[y++] = del(bins[x]);
                        x++;
                }
        }

}


int main() {
        // intial variables
        int** arr;
        int i, j, arrSize;

        // input array
        cin >> arrSize;

        arr = new int*[arrSize];
        for (i = 0; i < arrSize; i++)
                arr[i] = new int[vecSize];

        for (i = 0; i < arrSize; i++)
                for (j = 0; j < vecSize; j++)
                        cin >> arr[i][j];

        // call function
        radixSort(arr,arrSize,vecSize);

        // print output
        for (i = 0; i < arrSize; i++) {
                for (j = 0; j < vecSize; j++)
                        cout << arr[i][j] << ";";
                cout << endl;
        }

        // delete
        for (i = 0; i < arrSize; i++)
                delete[] arr[i];
		delete[] arr;

        return 0;

}