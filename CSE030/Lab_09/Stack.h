#ifndef STACK_H
#define STACK_H
#include "LinkedList.h"
using namespace std;


class Stack: public LinkedList {

        public:
                Stack();
                ~Stack();
                void push(int value);
                int pop();
                int& top();

};


#endif