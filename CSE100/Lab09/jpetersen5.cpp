#include <iostream>
using namespace std;

// set constant size for # of ASCII symbols, technically can be changed if needed
const int numsym = 6;
void huffman(char syms[], int freqs[]);


// create node structure for storing frequency of symbol, the symbol, and branch nodes.
// frequency is used in creating the huffman tree, i.e. deciding which symbols will
// get the least amount of bits for maximum efficiency.
// a node's path through the huffman tree is stored as its new encoding
struct node {
        int frequency;
        char symbol;
        struct node *left, *right;
        string code;
};

// huffman tree is a heap that stores the nodes in a binary structure.
// it stores a size to keep track when a value is popped
struct huffTree {
        int size;
        struct node** tree;
};


// standard function to create a new node with provided frequency and symbol.
// other values are defaulted
struct node* newNode(int n, char sym) {
        struct node* temp = new node();
        temp->frequency = n;
        temp->symbol = sym;
        temp->left = NULL;
        temp->right = NULL;
        temp->code = "";

        return temp;
}

// huffman tree allocation of memory and assignment of size (0 with no elements yet)
struct huffTree* createTree() {
        struct huffTree* tempTree = new huffTree();
        tempTree->tree = (struct node**)malloc(numsym * sizeof(struct node*));
        tempTree->size = 0;

        return tempTree;
}

// standard function for swapping the location of two nodes in the tree
void swapNode(struct node** first, struct node** second) {
        struct node* temp = *first;
        *first = *second;
        *second = temp;
}

// standard function to heapify a list (the huffman tree)
void heapify(struct huffTree* huff, int ind) {
        int min = ind;
        int left = 2 * ind + 1;
        int right = 2 * ind + 2;

        min = (left < huff->size && huff->tree[left]->frequency < huff->tree[min]->frequency) ? left : min;
        min = (right < huff->size && huff->tree[right]->frequency < huff->tree[min]->frequency) ? right : min;

        if (min != ind) {
                swapNode(&huff->tree[min], &huff->tree[ind]);
                heapify(huff, min);
        }
}

// standard function to remove and return a minimum value from the tree
struct node* pop(struct huffTree* huff) {
        struct node* temp = huff->tree[0];
        huff->tree[0] = huff->tree[huff->size - 1];

        --huff->size;
        heapify(huff, 0);

        return temp;
}

// insert a node into the huffman tree
// compares input node to branches and moves down to correct position to insert
void insertHuffTree(struct huffTree* huff, struct node* treeNode) {
        int ind = huff->size;
        ++huff->size;

        while (ind && treeNode->frequency < huff->tree[(ind - 1) / 2]->frequency) {
                huff->tree[ind] = huff->tree[(ind - 1) / 2];
                ind = (ind - 1) / 2;
        }

        huff->tree[ind] = treeNode;
}

// repeatedly heapifies the tree to create a correct huffman tree
void buildHeap(struct huffTree* huff) {
        int n = huff->size - 1;
        int ind;

        for (ind = (n - 1) / 2; ind >= 0; --ind)
                heapify(huff, ind);
}

// fills huffman tree's list with nodes corresponding to frequencies + symbols
struct huffTree* createHeap(char syms[], int freqs[]) {
        struct huffTree* tempTree = createTree();

        for (int i = 0; i < numsym; ++i)
                tempTree->tree[i] = newNode(freqs[i], syms[i]);

        tempTree->size = numsym;
        buildHeap(tempTree);

        return tempTree;
}

// creates a complete tree with connecting parent nodes, then returns the root node
struct node* buildTree(char syms[], int freqs[]) {
        struct node *left, *right, *main;

        struct huffTree* huff = createHeap(syms, freqs);

        while (huff->size != 1) {
                left = pop(huff);
                right = pop(huff);
                main = newNode(left->frequency + right->frequency, '0');

                main->left = left;
                main->right = right;

                insertHuffTree(huff, main);
        }

        return pop(huff);
}


// driver code, with initial symbols ABCDEF and desired input numbers
int main() {
        char symbols[] = {'A','B','C','D','E','F'};
        int* freqArr = new int[numsym];
        int i;

        for (i = 0; i < numsym; i++)
                cin >> freqArr[i];

        huffman(symbols, freqArr);

        return 0;
}


// prints a huffman tree in the desired way.
// recursively searches down paths, creating a string containing the symbols alongside their encoding
void printHuff(struct node* root, int codes[], int main, string &outs) {
        if (root->left) {
                codes[main] = 0;
                printHuff(root->left, codes, main + 1, outs);
        }

        if (root->right) {
                codes[main] = 1;
                printHuff(root->right, codes, main + 1, outs);
        }

        if (!(root->left) && !(root->right)) {
                outs += root->symbol;
                outs += ":";
                for (int i = 0; i < main; i++)
                        outs += to_string(codes[i]);
                outs += '\0';
        }
}

// calls previous functions to build a tree and retrieve root node, then prints the codes
// to a string using printHuff. this string is then split and displayed on a new line for
// each symbol
void huffman(char syms[], int freqs[]) {
        struct node* root = buildTree(syms, freqs);

        string outs;
        int arr[numsym];
        printHuff(root, arr, 0, outs);

        for (int k = 0; k < numsym; k++) {
                int i = 0;
                while (outs[i] != syms[k])
                        i++;

                while (outs[i] != '\0')
                        cout << outs[i++];

                cout << endl;
        }
}