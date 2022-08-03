#ifndef STACK_CHAR_H
#define STACK_CHAR_H
#include "LinkedList_char.h"
using namespace std;


class Stack: public LinkedList {

        public:
                Stack();
                ~Stack();
                void push(char value);
                char pop();
                char& top();

};


#endif