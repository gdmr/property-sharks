#include "tessera.hpp"
#include <iostream>
#pragma once

class Inconvenienti : public Tessera
{
private:
    int importo;
    bool prigione;
    std::vector<Inconvenienti> setCarte; 
    

public:
Inconvenienti(const std::vector<Inconvenienti>& cards);  //costrutture per il set di carte
Inconvenienti(std::string nome, int importo, bool prigione); //costruttore singolo
virtual ~Inconvenienti();
std::string getTipo() const override { return "Inconvenienti";}
Inconvenienti pescaCarta(); 
int getImporto();
bool isPrigione();
};



