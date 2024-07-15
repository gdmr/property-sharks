#include "tessera.hpp"

Tessera::Tessera() : proprietario("banca"){}
Tessera::~Tessera(){}
void Tessera::setTitolo(std::string titolo){
    this->titolo = titolo;
}
void Tessera::setProprietario(std::string nuovoProprietario){
    proprietario= nuovoProprietario;
}
