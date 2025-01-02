#include <iostream>

class Printable {
public:
	virtual std::string getClassName() = 0;
};

class Entity : public Printable{
public:
	virtual std::string getName() { return "Entity"; }
	std::string getClassName() override { return "Entity"; }
};

class Player : public Entity{
private:
	std::string m_name;
public:
	Player(const std::string& name) : m_name(name) {}
	std::string getName() override { return m_name; }
	std::string getClassName() override { return "Player"; }
};

void printName(Entity* entity) {
	std::cout << entity->getName() << "\n";
}

void print(Printable* obj) {
	std::cout << obj->getClassName() << "\n";
}

int main() {
	Entity* e = new Entity();
	//printName(e);

	Player* p = new Player("EXANU");
	//printName(p);

	print(e);
	print(p);
	return 0;
}