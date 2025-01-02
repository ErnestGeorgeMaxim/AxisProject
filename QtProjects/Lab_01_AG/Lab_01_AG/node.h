#ifndef NODE_H
#define NODE_H

#include<QPoint>
class Node{
public:
	Node();
	int getValue() { return this->m_value; };
	QPoint getPos() { return this->m_pos; };
	void setValue(int value) { this->m_value = value; };
	void setPos(QPoint pos) { this->m_pos = pos; };

private:
	int m_value;
	QPoint m_pos;
};

#endif// NODE_H

