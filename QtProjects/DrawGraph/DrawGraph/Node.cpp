#include "Node.h"

int Node::getId(){
	return this->id;
}

QPoint Node::getPosition(){
	return this->position;
}

void Node::setId(int id){
	this->id = id;
}

void Node::setPosition(QPoint position){
	this->position = position;
}
