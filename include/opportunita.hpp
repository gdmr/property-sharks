#include "tessera.hpp"
#include <iostream>

class Opportunita : public Tessera
{
private:
    bool bonus;
    int importo;
    

public:
 Opportunita(std::string nome, bool bonus, int importo);
 ~Opportunita();
 std::string getTipo() const override { return "Opportunita";}

};