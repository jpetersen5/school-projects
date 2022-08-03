#include <iostream>
#include "LinkedList.h"
using namespace std;


// linked list constructor
LinkedList::LinkedList() {
        // initialize the head and tail as NULL pointers
        first = NULL;
        last = NULL;
}

// linked list deconstructor
LinkedList::~LinkedList() {
        Node* temp = first;

        // loop through the nodes, deleting them each to deconstruct list
        while (temp != NULL) {
                Node* tempNext = temp->next;
                delete temp;
                temp = tempNext;
        }
        first = NULL;
}


// inserts a new Node at the end of list
void LinkedList::insertAtBack(int newVal) {
        // initialize a new node
        Node *newNode = new Node;
        newNode->val = newVal;
        newNode->next = NULL;

        // if this is first element
        if (first == NULL) {
                first = newNode;
                last = newNode;
        } else { // set new last node to this node
                last->next = newNode;
                last = last->next;
        }

        return;
}

// removes node from the end
bool LinkedList::removeFromBack() {
        // can't remove non-existant node
        if (last == NULL) {
                return false;
        }

        // removing only node leaves only NULL
        if (first == last) {
                delete last;
                first = NULL;
                last = NULL;
                return true;
        }

        // loop through nodes until node before last is found
        Node* temp = first;
        while (temp->next != last) {
                temp = temp->next;
        }

        // delete last node, make current node new last
        delete last;
        last = temp;
        last->next = NULL;

        return true;
}

// prints out the list
void LinkedList::print() {
        // can't print empty list
        if (first == NULL) {
                return;
        }

        // loop through to print each node's value
        Node* temp = first;
        while (temp != last) {
                cout << temp->val << ",";
                temp = temp->next;
        }
        cout << last->val;

        return;
}

// checks whether the list is empty
bool LinkedList::isEmpty() {
        return first == NULL;
}

// returns size of the list
int LinkedList::size() {
        // empty list is size 0
        if (first == NULL) {
                return 0;
        }

        // loop through elements to count them
        Node* temp = first;
        int size = 0;
        while (temp != last) {
                size++;
                temp = temp->next;
        }

        // account for last node
        size++;

        return size;
}

// destructor again
void LinkedList::clear() {
        Node* temp = first;

        // loop through the nodes, deleting them each to clear list
        while (temp != NULL) {
                Node* tempNext = temp->next;
                delete temp;
                temp = tempNext;
        }
        first = NULL;
}


// insert an node at the front of the list
void LinkedList::insertAtFront(int newVal) {
        // initialize a new node
        Node *newNode = new Node;
        newNode->val = newVal;

        // if it's the first node
        if (first == NULL) {
                first = newNode;
                last = newNode;
                newNode->next = NULL;
                return;
        }

        // otherwise
        newNode->next = first;

        // reassign it to a new first node
        first = newNode;

        return;
}

// remove a node from the front of the list
bool LinkedList::removeFromFront() {
        // can't remove non-existant node
        if (first == NULL) {
                return false;
        }

        // removing only node leaves only NULL
        if (first == last) {
                delete first;
                first = NULL;
                last = NULL;
                return true;
        }

        Node* temp = first->next;
        delete first;
        first = temp;

        return true;
}

// return value of first node
int LinkedList::firstVal() {
        return first->val;
}