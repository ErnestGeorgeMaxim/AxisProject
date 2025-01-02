#pragma once

#include "Node.h"

class Edge{
public:
	Edge();
	Edge(Node firstNode, Node secondNode) : firstNode(firstNode), secondNode(secondNode) {};
	Node getFirstNode();
	Node getSecondNode();
private:
	Node firstNode, secondNode;
};

