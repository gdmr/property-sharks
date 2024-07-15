#include "tessera.hpp"
#include <iostream>

class Inconvenienti : public Tessera
{
private:
    int importo;
    

public:
 Inconvenienti(std::string nome, int importo);
 ~Inconvenienti();

};
