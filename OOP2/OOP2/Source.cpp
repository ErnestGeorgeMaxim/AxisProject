#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/*
Sa se scrie o ierarhie de componente ale unui calculator  **mostenire virtuaal doar pt diamant!
1. Clasa ComputerPart care este clasa abstracta avand metodele pur virtuale getPrice() si getProducer()
2. Derivate din ComputerPart avem clasele HDD, ExternalHDD,Display,Mouse,Keyboard
3. Scrieti 2 interfete HasMemory cu metCapacity() si getFrequency() si HasButtons cu met getNoOfButtons()
4. Acolo unde este cazul faceti clasele sa implementeze una din cele 2 interfete
5. Generati o serie de componente pe care sa le tineti minte intr-un singur vector
	-> sa se seoare vectorul in alti 2, unul care sa contina comp cu butoane altul pe ... cu memorie
	-> sa se sorteze comp cu butoane dupa nr de butoane


in toat eclasele vom avea nevoie de destructori virtuali

vector <ComputerPart*> componente;
populat vect cu componente
for (int i - 0; i < componente.size; i++)
	Hasbuttons* adr = dynamic_cast<HasButtons*> componente[i]->incerc sa fac conv a elem comp[i] la un obiect cu butoane
	if (adr)
		compbutoane.pushback(componente[i]);


comparare dupa nr butoane: ordonare cresc

bool comparatorButoane(HasButtons* h1, HasButtons* h2)
return h1->getnrbuttons() < h2->getnrbuttons();
*/

class ComputerPart {
public:
	virtual double getPrice() const = 0;
	virtual std::string getProducer() const = 0;
	virtual std::string getName() const = 0;

	virtual ~ComputerPart() = default;
};

class HasButtons {
public:
	virtual int getNumOfButtons() const = 0;
	virtual ~HasButtons() = default;
};

class HasMemory {
public:
	virtual double getCapacity() const = 0;
	virtual double getFrequency() const = 0;
	virtual ~HasMemory() = default;
};

class HDD : public ComputerPart, public HasMemory{
private:
	std::string name;
	std::string producer;
	double price;
	double capacity;
	double frequency;
public:
	HDD() = default;
	HDD(const std::string& producer, const std::string name, double price, double capacity, double frequency) {
		this->name = name;
		this->producer = producer;
		this->price = price;
		this->capacity = capacity;
		this->frequency = frequency;
	}
	
	virtual ~HDD() = default;

	std::string getProducer() const override {
		return producer;
	}
	std::string getName() const override {
		return name;
	}
	double getPrice() const override {
		return price;
	}
	double getCapacity() const override {
		return capacity;
	}
	double getFrequency() const override {
		return frequency;
	}

};

class ExternalHDD : public ComputerPart, public HasMemory{
private:
	std::string name;
	std::string producer;
	double price;
	double capacity;
	double frequency;
public:
	ExternalHDD() = default;
	ExternalHDD(const std::string& producer, const std::string name, double price, double capacity, double frequency) {
		this->name = name;
		this->producer = producer;
		this->price = price;
		this->capacity = capacity;
		this->frequency = frequency;
	}

	virtual ~ExternalHDD() = default;

	std::string getProducer() const override {
		return producer;
	}
	std::string getName() const override {
		return name;
	}
	double getPrice() const override {
		return price;
	}
	double getCapacity() const override {
		return capacity;
	}
	double getFrequency() const override {
		return frequency;
	}

};

class Display : public ComputerPart {
private:
	std::string name;
	std::string producer;
	double price;

public:
	Display() = default;
	Display(const std::string& name, const std::string& producer, double price) {
		this->name = name;
		this->producer = producer;
		this->price = price;
	}

	virtual ~Display() override = default;

	std::string getName() const override {
		return name;
	}
	std::string getProducer() const override {
		return producer;
	}
	double getPrice() const override {
		return price;
	}
};

class Mouse : public ComputerPart,public HasButtons{
private:
	std::string name;
	std::string producer;
	double price;
	int buttons;

public:
	Mouse() = default;
	Mouse(const std::string& name, const std::string& producer, double price, int buttons) {
		this->name = name;
		this->producer = producer;
		this->price = price;
		this->buttons = buttons;
	}

	virtual ~Mouse() override = default;

	std::string getName() const override {
		return name;
	}
	std::string getProducer() const override {
		return producer;
	}
	double getPrice() const override {
		return price;
	}
	int getNumOfButtons() const override {
		return buttons;
	}
}; 

class Keyboard : public ComputerPart, public HasButtons{
private:
	std::string name;
	std::string producer;
	double price;
	int buttons;

public:
	Keyboard() = default;
	Keyboard(const std::string& name, const std::string& producer, double price, int buttons) {
		this->name = name;
		this->producer = producer;
		this->price = price;
		this->buttons = buttons;
	}

	virtual ~Keyboard() override = default;

	std::string getName() const override {
		return name;
	}
	std::string getProducer() const override {
		return producer;
	}
	double getPrice() const override {
		return price;
	}
	int getNumOfButtons() const override {
		return buttons;
	}
};

int main() {

	std::vector<ComputerPart*> components;
	components.push_back(new HDD("Seagate", "LionsGate", 100.0, 1024, 7200));
	components.push_back(new ExternalHDD("WD", "Cacctus", 150.0, 2048, 5400));
	components.push_back(new Display("Cortex", "Dell", 200.0 ));
	components.push_back(new Mouse("XYE-231", "Logitech", 50.0, 5));
	components.push_back(new Keyboard("K70", "Corsair", 70.0, 104));

	std::vector<ComputerPart*> compMemory;
	std::vector<ComputerPart*> compButtons;

	for (int i = 0; i < components.size(); i++) {
		HasButtons* adrButoane = dynamic_cast<HasButtons*>(components[i]);
		if (adrButoane) {
			compButtons.push_back(components[i]);
		}
		HasMemory* adrMemorie = dynamic_cast<HasMemory*>(components[i]);
		if (adrMemorie) {
			compMemory.push_back(components[i]);
		}
	}

	std::sort(compButtons.begin(), compButtons.end(), [](ComputerPart* a, ComputerPart* b) {
		HasButtons* h1 = dynamic_cast<HasButtons*>(a);
		HasButtons* h2 = dynamic_cast<HasButtons*>(b);
		return h1->getNumOfButtons() < h2->getNumOfButtons(); });

	for (const auto& cell : compButtons) {
		HasButtons* hb = dynamic_cast<HasButtons*>(cell);
		if (hb) {
			std::cout << cell->getName() << " - " << cell->getProducer() << " - " << cell->getPrice() << "\n";
		}
	}

	std::sort(compMemory.begin(), compMemory.end(), [](ComputerPart* a, ComputerPart* b) {
		HasMemory* m1 = dynamic_cast<HasMemory*>(a);
		HasMemory* m2 = dynamic_cast<HasMemory*>(b);
		return m1->getFrequency() * m2->getCapacity() > m1->getCapacity() * m2->getFrequency(); });

	for (const auto& cell : compMemory) {
		HasMemory* hb = dynamic_cast<HasMemory*>(cell);
		if (hb) {
			std::cout << cell->getName() << " - " << cell->getProducer() << " - " << cell->getPrice() << "\n";
		}
	}

	for (auto d : components) {
		delete d;
	}

	return 0;
}