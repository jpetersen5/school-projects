#define QUEUE_CHAR_H
#include "LinkedList_char.h"
using namespace std;


class Queue: public LinkedList {

        public:
                Queue();
                ~Queue();
                void enqueue(char value);
                char dequeue();
                char& front();

};


#endif