#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

class Queue
{
public:
	Queue();
	~Queue();
	
	void push(Node top);
	Node* pop(void);
	Node* peek(void);
};

#endif