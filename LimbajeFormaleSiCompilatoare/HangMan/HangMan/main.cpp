#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <random>
#include <ctime>

void createUnknowWord(const std::string& choosenWord, std::string& newWord) {
    newWord = choosenWord;
    for (int i = 1; i < newWord.size() - 1; i++)
        newWord[i] = '_';
}

bool checkLetter(std::string& newWord, const std::string& choosenWord, char letter) {
    std::smatch match;
    std::string sLetter(1, letter);
    std::string::const_iterator searchStart(choosenWord.cbegin());
    bool found = false;

    while (std::regex_search(searchStart, choosenWord.cend(), match, std::regex(sLetter))) {
        newWord[match.position() + (searchStart - choosenWord.cbegin())] = letter;
        searchStart = match.suffix().first;
        found = true;
    }
    return found;
}

int underscoreCounter(const std::string& newWord) {
    int count = 0;
    for (int i = 1; i < newWord.size() - 1; i++)
        if (newWord[i] == '_')
            count++;
    return count;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<std::string> wordList = { "ELICOPTER", "FERIBOT", "ACOPERIS", "CAMPENEASCA",
        "ROMANIA", "TRANSPORT", "CONSTRUCTIE", "ARHITECTURA", "INDUSTRIALIZARE", "HIPOPOTAM",
        "CASA", "MASA", "FRUNZA", "BUNICA", "LUNA", "SOARE", "COPAC", "VACA", "LEU", "LAPTE",
        "SUPRAVIETUIRE", "DESCOMPUNERE", "AERONAVIGABIL", "PSIHOPEDAGOGIE", "MULTICULTURALITATE",
        "ELECTROENCEFALOGRAF", "INCONSTITUTIONALITATE", "SUBMINERALIZARE", "ANTICONSTITUTIONAL",
        "PLOAIE", "PADURE", "VACANTA", "FRUCTE", "FLOARE", "BROASCA", "PAMANT", "STELE", "CRAVATA",
        "CAPSUNA", "ANTIDISCRIMINATORIU" };

    std::string choosenWord = wordList[std::rand() % wordList.size()];
    std::string newWord;
    createUnknowWord(choosenWord, newWord);

    int mistakes = 6;
    bool notGuessed = false;
    char letter;

    std::cout << "Bun venit in HangMan\n";
    std::cout << "Se permit 6 greseli.\n";
    std::cout << "Cuvantul pe care trebuie sa-l ghiciti este: " << newWord << "\n";

    while (!notGuessed && mistakes > 0) {
        std::cout << "Introduceti o litera (MAJUSCULA): ";
        std::cin >> letter;

        if (!std::isupper(letter)) {
            std::cout << "Va rugam sa introduceti doar litere mari!\n";
            continue;
        }

        if (checkLetter(newWord, choosenWord, letter)) {
            std::cout << "Cuvantul actualizat: " << newWord << "\n";
        }
        else {
            mistakes--;
            std::cout << "Litera nu se gaseste in cuvant. Mai aveti " << mistakes << " greseli permise!\n";
        }

        if (underscoreCounter(newWord) == 0) {
            std::cout << "Felicitari! Ati ghicit cuvantul: " << newWord << "\n";
            notGuessed = true;
        }
    }

    if (mistakes == 0) {
        std::cout << "Ai pierdut! Cuvantul corect era: " << choosenWord << "\n";
    }

    return 0;
}