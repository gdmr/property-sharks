#include "banca.hpp"
#include "tabellone.hpp"
#include "dado.hpp"

class Gioco
{
private:
    std::vector<Giocatore> giocatori;
    Tabellone tabellone;
    Banca banca;
    Dado dadi;
    bool fine;

public:
    Gioco(Giocatore g);
    ~Gioco();
    void inizializza();
    void eseguiTurno();
    std::vector<Giocatore> getListaGiocatori();
    void gestisciTurno();
    void gioca();
    bool controlloVittoria();
    bool fineGioco();
};

