#pragma once

#include <QPoint>

class Node{
public:
	Node();
	Node(int id, QPoint position) : id{ id }, position{ position } {};
	int getId();
	QPoint getPosition();
	void setId(int id);
	void setPosition(QPoint position);
private:
	int id;
	QPoint position;
};

