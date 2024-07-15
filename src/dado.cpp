#include "dado.hpp"

Dado::Dado() {
    std::srand(std::time(0));
}

Dado::~Dado() {}

int lancia() {
    return (std::rand() % 6) + 1;  // Restituisce un numero casuale tra 1 e 6
}

int Dado::lanciaDadi() {
    int risultato1 = lancia();
    int risultato2 = lancia();
    return risultato1 + risultato2;
}