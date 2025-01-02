#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Character {
private:
    std::string name;
    int level;
    int health;

public:
    Character() : name("unknown"), level(0), health(0) {}
    Character(const std::string& name, const int& level, const int& health) {
        this->name = name;
        this->level = level;
        this->health = health;
    }

    std::string getName() const { return name; }
    int getLevel() const { return level; }
    int getHealth() const { return health; }

    void setName(const std::string& name) {
        this->name = name;
    }
    void setLevel(const int& level) {
        this->level = level;
    }
    void setHealth(const int& health) {
        this->health = health;
    }

    virtual void attack(Character& b) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Character& c) {
        os << "Name : " << c.name << ", Level : " << c.level << ", Health : " << c.health << "\n";
        return os;
    }

    virtual ~Character() = default;
};

class Warrior : public Character {
private:
    std::string power;
    std::string weapon;

public:
    Warrior() : Character(), power(""), weapon("") {}
    Warrior(const std::string& name, const int& level, const int& health, const std::string& power, const std::string& weapon)
        : Character(name, level, health), power(power), weapon(weapon) {}

    std::string getPower() { return power; }
    std::string getWeapon() { return weapon; }

    void setPower(std::string power) {
        this->power = power;
    }
    void setWeapon(std::string weapon) {
        this->weapon = weapon;
    }

    void attack(Character& b) override {
        std::cout << "The warrior attacked character " << b.getName() << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Warrior& c) {
        os << "Name : " << c.getName() << ", Level : " << c.getLevel() << ", Health : " << c.getHealth() << ", Power : " << c.power << ", Weapon : " << c.weapon << "\n";
        return os;
    }

    ~Warrior() = default;
};

class Mage : public Character {
private:
    std::string magic;

public:
    Mage() : Character(), magic("") {}
    Mage(const std::string& name, const int& level, const int& health, const std::string& magic)
        : Character(name, level, health), magic(magic) {}

    std::string getMagic() { return magic; }
    void setMagic(std::string magic) {
        this->magic = magic;
    }

    void attack(Character& b) override {
        std::cout << "The mage attacked character " << b.getName() << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Mage& c) {
        os << "Name : " << c.getName() << ", Level : " << c.getLevel() << ", Health : " << c.getHealth() << ", Magic : " << c.magic << "\n";
        return os;
    }

    ~Mage() = default;
};

class Assassin : public Character {
private:
    int agility;
    std::string secretWeapon;

public:
    Assassin() : Character(), agility(0), secretWeapon("") {}
    Assassin(const std::string& name, const int& level, const int& health, const int& agility, const std::string& secretWeapon)
        : Character(name, level, health), agility(agility), secretWeapon(secretWeapon) {}

    int getAgility() { return agility; }
    std::string getSecretWeapon() { return secretWeapon; }

    void setAgility(int agility) {
        this->agility = agility;
    }
    void setSecretWeapon(std::string secretWeapon) {
        this->secretWeapon = secretWeapon;
    }

    void attack(Character& b) override {
        std::cout << "The assassin attacked character " << b.getName() << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Assassin& c) {
        os << "Name : " << c.getName() << ", Level : " << c.getLevel() << ", Health : " << c.getHealth() << ", Agility : " << c.agility << ", SecretWeapon : " << c.secretWeapon << "\n";
        return os;
    }

    ~Assassin() = default;
};

class Game {
public:
    std::vector<Character*> characters;

    void addCharacter(Character* a) {
        characters.push_back(a);
    }

    void characterFight(Character& a, Character& b) {
        a.attack(b);
    }

    void print() {
        for (const auto& cell : characters) {
            std::cout << *cell;
        }
    }

    ~Game() {
        for (auto& character : characters) {
            delete character;
        }
    }
};

int main() {
    Game a;
    a.addCharacter(new Assassin("Picky", 5, 10, 5, "Dagger"));
    a.addCharacter(new Warrior("Valus", 10, 30, "Sword of Justice", "Maligra"));
    a.addCharacter(new Mage("Yrui", 10, 9, "Oblivion"));
    a.addCharacter(new Warrior("Garen", 18, 50, "Arrows of Carnage", "The IronWill"));
    a.addCharacter(new Assassin("Mikasa", 10, 14, 10, "Dagger of Avalon"));

    std::sort(a.characters.begin(), a.characters.end(), [](Character* a, Character* b) {
        return a->getHealth() < b->getHealth();
        });

    std::vector<Warrior*> warriors;
    std::vector<Mage*> mages;
    std::vector<Assassin*> assassins;

    for (int i = 0; i < a.characters.size(); i++) {
        Warrior* adrWarrior = dynamic_cast<Warrior*>(a.characters[i]);
        if (adrWarrior) {
            warriors.push_back(adrWarrior);
        }
        Mage* adrMage = dynamic_cast<Mage*>(a.characters[i]);
        if (adrMage) {
            mages.push_back(adrMage);
        }
        Assassin* adrAssassin = dynamic_cast<Assassin*>(a.characters[i]);
        if (adrAssassin) {
            assassins.push_back(adrAssassin);
        }
    }

    for (int i = 0; i < a.characters.size() - 1; i++) {
        for (int j = i + 1; j < a.characters.size(); j++) {
            a.characterFight(*a.characters[i], *a.characters[j]);
        }
    }

    a.print();

    return 0;
}
