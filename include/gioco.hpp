#include "banca.hpp"
#include "tabellone.hpp"

class Gioco
{
private:
    std::vector<Giocatore> giocatori;
    Tabellone tabellone;
    Banca banca;
public:
    Gioco();
    ~Gioco();
    void inizializza();
    void gestisciTurno();
    bool controlloVittoria();
};

