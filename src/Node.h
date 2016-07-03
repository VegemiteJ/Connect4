#ifndef NODE_H
#define NODE_H

class Node
{
public:
	Node();
	Node(Node* parent);
	~Node();

private:
	Node* myChildren;
	Node* parent;

	int* moveSeq;
	int numMoves;

    //Tuple of [row, col] location to evaluation
	int* currentEvalLoc;
	
};

#endif