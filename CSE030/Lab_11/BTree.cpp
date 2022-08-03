#include <iostream>
#include "BTree.h"
using namespace std;


// construct tree by setting root to NULL
BTree::BTree() {
        // cout << "constructing tree: root NULL" << endl;
        this->root = NULL;
}

// deconstruct tree by calling destroy tree
BTree::~BTree() {
        // cout << "destroying tree" << endl;
        destroy_tree();
}


// return the tree's root address
Node *BTree::BTree_root() {
        // cout << "returning root: " << this->root << endl;
        return this->root;
}

// destroy the tree recursively down the leaves
void BTree::destroy_tree(Node *leaf) {
        // cout << "destroying leaf: " << leaf << endl;
        if (leaf == NULL) { return; }

        // if the leaf has children, recursively destroy
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);

        delete leaf;

        return;
}

// recursively search for correct empty node to insert key value
void BTree::insert(int key, Node *leaf) {
        // if the insert is the first, insert as root value
        if (this->root == NULL) {
                this->root = new Node;
                this->root->key_value = key;
                this->root->left = NULL;
                this->root->right = NULL;

                return;
        }

        // cout << "inserting leaf with " << key << " value, current leaf is " << leaf->key_value << endl;
        // check left leaf
        if (key < leaf->key_value) {

                // if next leaf is NULL value, insert there
                if (leaf->left == NULL) {
                        leaf->left = new Node;
                        leaf->left->key_value = key;
                        leaf->left->left = NULL;
                        leaf->left->right = NULL;

                        return;

                } else { insert(key,leaf->left); } // recurse

        } else { // check right leaf

                // if next leaf is NULL value, insert here
                if (leaf->right == NULL) {
                        leaf->right = new Node;
                        leaf->right->key_value = key;
                        leaf->right->left = NULL;
                        leaf->right->right = NULL;

                        return;

                } else { insert(key,leaf->right); } // recurse

        }
}

// recursively search for key within the tree and return leaf address if found. NULL if not found
Node *BTree::search(int key, Node *leaf) {
        // return nothing if leaf is doesn't exist
        if (leaf == NULL) { return NULL; }

        // cout << "searching for leaf with " << key << " value, current leaf is " << leaf->key_value << endl;
        // compare leaf value to key searching for
        if (leaf->key_value == key) {
                return leaf;
        } else if (key < leaf->key_value) { // compare left leaf
                search(key,leaf->left);
        } else { // compare right leaf
                search(key,leaf->right);
        }
}

// insert beginning at root
void BTree::insert(int key) {
        insert(key,this->root);
        return;
}

// search beginning at root
Node *BTree::search(int key) {
        search(key,this->root);
}

// destroy beginning at root
void BTree::destroy_tree() {
        destroy_tree(this->root);
}
