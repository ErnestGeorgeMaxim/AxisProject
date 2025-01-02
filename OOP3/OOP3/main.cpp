#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

enum AnimalType {
    UNKOWN,
    AQUATIC,
    AERIAL,
    FELINE,
    HERBIVORE
};

class DoesSound {
public:
    virtual std::string sound() = 0;
    virtual std::string sound(int loudness) = 0;
};

class Animal : public DoesSound {
private:
    AnimalType species;
    std::string soundType;

public:
    Animal() : species(UNKOWN), soundType(" ") {}
    Animal(const AnimalType& t, const std::string& soundType) {
        this->species = t;
        this->soundType = soundType;
    }

    AnimalType getSpecies() {
        return species;
    }

    std::string sound() override {
        return soundType;
    }

    std::string sound(int loudness) override {
        if (loudness == 0)
            return soundType;
        else {
            std::string loudSound = soundType;
            for (char& c : loudSound)
                c = toupper(c);
            return loudSound;
        }
    }
};

class Squidward : public Animal {
public:
    Squidward() : Animal(AnimalType::AQUATIC, "flup flup") {};
};

class Spongbob : public Animal {
public:
    Spongbob() : Animal(AnimalType::AQUATIC, "ahahahahaaha") {};
};

class Chicken : public Animal {
public:
    Chicken() : Animal(AnimalType::AERIAL, "cot cot") {};
};

class Colibri : public Animal {
public:
    Colibri() : Animal(AnimalType::AERIAL, "cip cip") {};
};

class Kitten : public Animal {
public:
    Kitten() : Animal(AnimalType::FELINE, "meow") {};
};

class Lion : public Animal {
public:
    Lion() : Animal(AnimalType::FELINE, "roar") {};
};

class Elephant : public Animal {
public:
    Elephant() : Animal(AnimalType::HERBIVORE, "huuuuu") {};
};

class Cow : public Animal {
public:
    Cow() : Animal(AnimalType::HERBIVORE, "muuu") {};
};

class Cage : public DoesSound {
private:
    std::vector<Animal*> animals;
    AnimalType acceptedType;
    int capacity;
    std::string soundType;

public:
    Cage(const int& capacity, const AnimalType& acceptedType, const std::string& soundType) {
        this->capacity = capacity;
        this->acceptedType = acceptedType;
        this->soundType = soundType;
    }

    bool addAnimal(Animal* animal) {
        if (animal->getSpecies() == acceptedType && animals.size() < capacity) {
            this->animals.push_back(animal);
            return true;
        }
        return false;
    }

    std::string sound() override {
        return soundType;
    }

    std::string sound(int loudness) override {
        if (loudness == 0)
            return soundType;
        else {
            std::string loudSound = soundType;
            for (char& c : loudSound)
                c = toupper(c);
            return loudSound;
        }
    }

    void visit() {
        srand(static_cast<unsigned>(time(0)));
        int loudness = rand() % 2;
        std::cout << sound(loudness) << std::endl;
        for (const auto& cell : animals) {
            std::cout << cell->sound(loudness) << std::endl;
        }
    }

    ~Cage() {
        animals.clear();
    }
};

class Aquarium : public Cage {
public:
    Aquarium(int capacity) : Cage(capacity, AnimalType::AQUATIC, "splash splash") {};
};

class HerbivorePen : public Cage {
public:
    HerbivorePen(int capacity) : Cage(capacity, AnimalType::HERBIVORE, "scartz scartz") {};
};

class FelinePen : public Cage {
public:
    FelinePen(int capacity) : Cage(capacity, AnimalType::FELINE, "scartz scartz") {};
};

class Aviary : public Cage {
public:
    Aviary(int capacity) : Cage(capacity, AnimalType::AERIAL, "plfu plfu") {};
};

int main() {
    Aviary aviary(4);
    FelinePen felinePen(2);
    HerbivorePen herbivorePen(3);

    Cow cow1, cow2;
    Elephant elephant;
    Chicken chicken;
    Kitten kitten;
    Lion lion;

    herbivorePen.addAnimal(&cow1);
    herbivorePen.addAnimal(&cow2);
    herbivorePen.addAnimal(&elephant);

    aviary.addAnimal(&chicken);

    felinePen.addAnimal(&kitten);
    felinePen.addAnimal(&lion);

    std::cout << "Herbivore Pen visit:\n";
    herbivorePen.visit();

    std::cout << "\nAviary visit:\n";
    aviary.visit();

    std::cout << "\nFeline Pen visit:\n";
    felinePen.visit();

    return 0;
}
