#include "tessera.hpp"
#include <iostream>

class Opportunita : public Tessera
{
private:
    bool bonus;
    int importo;
    std::vector<Opportunita> setCarte; 

public:
Opportunita(const std::vector<Opportunita>& cards);  //costrutture per il set di carte
 Opportunita(std::string nome, bool bonus, int importo);
 ~Opportunita();
 std::string getTipo() const override { return "Opportunita";}
Opportunita pescaCarta(); 
};