#include "opportunita.hpp"

Opportunita::Opportunita(std::string nome, bool bonus, int importo){
setTitolo(nome);
this->bonus=bonus;
this->importo=importo;
}

Opportunita::~Opportunita(){}
