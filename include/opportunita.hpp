#include "tessera.hpp"
#include <iostream>
#pragma once

class Opportunita : public Tessera
{
private:
    bool bonus;
    int importo;
    std::vector<Opportunita> setCarte; 

public:
Opportunita(const std::vector<Opportunita>& cards);  //costrutture per il set di carte
 Opportunita(std::string nome, bool bonus, int importo);
virtual  ~Opportunita();
 std::string getTipo() const override { return "opportunita";}
Opportunita pescaCarta(); 
bool isBonus();
int getImporto();
};