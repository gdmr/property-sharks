#include "inconvenienti.hpp"

Inconvenienti::Inconvenienti(std::string nome, int importo){
    setTitolo(nome);
    this->importo=importo;
}

Inconvenienti::~Inconvenienti(){}