#include "tessera.hpp"
#include "giocatore.hpp"
#pragma once

class Prigione : public Tessera
{
private:
int giorniDiPrigione;

public:
Prigione(std::string nome, int giorni);
virtual ~Prigione();
void setGIorniDiPrigione(int giorni);
int getGIorniDiPrigione();
void vaiInPrigione(Giocatore g1);
 std::string getTipo() const override { return "prigione";}
};