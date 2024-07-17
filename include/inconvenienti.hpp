#include "tessera.hpp"
#include <iostream>

class Inconvenienti : public Tessera
{
private:
    int importo;
    bool prigione;
    

public:
 Inconvenienti(std::string nome, int importo, bool prigione);
 ~Inconvenienti();

};
