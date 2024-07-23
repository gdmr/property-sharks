#include "tessera.hpp"
#include "giocatore.hpp"

class Prigione : public Tessera
{
private:
int giorniDiPrigione;

public:
Prigione(std::string nome, int giorni);
~Prigione();
void setGIorniDiPrigione(int giorni);
int getGIorniDiPrigione();
void vaiInPrigione(Giocatore g1);
 std::string getTipo() const override { return "Prigiones";}
};