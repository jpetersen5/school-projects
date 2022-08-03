#include <iostream>
#include <string>
using namespace std;


// create structure for linked lists
struct node {
        int num;
        node* next;
};

struct node* newNode(int n) {
        node* temp = new node();
        temp->num = n;
        temp->next = NULL;

        return temp;
}


void insert(node*& head, int n) {
        node* temp = newNode(n);
        temp->next = head;
        head = temp;
}

void del(node*& head, int k) {
        if (head == NULL)
                return;

        node* temp = head;
        if (temp->num == k) {
                head = head->next;
                delete temp;
                return;
        }

        while (temp->num != k) {
                if (temp->next->num == k) {
                        node* nex = temp->next->next;
                        delete temp->next;
                        temp->next = nex;
                        return;
                }
                temp = temp->next;
        }

}


int search(node*& head, int k) {
        if (head == NULL)
                return -1;

        node* temp = head;
        int c = 0;
        while (temp->num != k) {
                if (temp->next == NULL)
                        return -1;

                temp = temp->next;
                c++;
        }

        return c;
}


void printHash(node** hash, int m) {
        node* temp;
        for (int i = 0; i < m; i++) {
                temp = hash[i];
                cout << i << ":";
                while (temp != NULL) {
                        cout << temp->num << "->";
                        temp = temp->next;
                }
                cout << ";" << endl;
        }
}


int main() {
        // initial variabls
        node** htable;
        int m, k;

        // input array
        cin >> m;

        htable = new node*[m];

        string inp;
        cin >> inp;

        while (inp != "e") {
                if (inp[0] == 'i') {
                        k = stoi(inp.substr(1));
                        insert(htable[k % m], k);
                }
                else if (inp[0] == 'd') {
                        k = stoi(inp.substr(1));
                        cout << k << ":";
                        int j = search(htable[k % m], k);

                        if (j != -1) {
                                del(htable[k % m], k);
                                cout << "DELETED";
                        }
                        else
                                cout << "DELETE_FAILED";

                        cout << ";" << endl;
                }
                else if (inp[0] == 's') {
                        k = stoi(inp.substr(1));
                        cout << k << ":";
                        int j = search(htable[k % m], k);

                        if (j != -1)
                                cout << "FOUND_AT" << k % m << "," << j;
                        else
                                cout << "NOT_FOUND";

                        cout << ";" << endl;
                }
                else if (inp == "o")
                        printHash(htable, m);
                cin >> inp;
        }

        return 0;
}