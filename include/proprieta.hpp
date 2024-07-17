#include "tessera.hpp"
#include <iostream>

class Proprieta : public Tessera
{
private:
    int costoProprieta;
    int costoCasa;
    int costoAlbergo;
    int numCase;
    bool albergo;
    

public:
     Proprieta(std::string nome, int costoProprieta, int costoCasa, int costoAlbergo);
    ~Proprieta();
    void aggiungiCasa();
    void costruisciAlbergo();
    int calcolaPagamento();
    int getNumeroCase();
    int getCosto();
};
