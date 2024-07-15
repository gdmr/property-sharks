#include "tabellone.hpp"

Tabellone::Tabellone() {
    creaTabellone(16, 4, 4);
}

Tabellone::~Tabellone() {}

void Tabellone::creaTabellone(int numeroCaselle, int numeroInconvenienti, int numeroOpportunita) {
    caselle = std::vector<Proprieta>{
        Proprieta("Viale Monte Bello", 100, 20, 50),
        Proprieta("Corso della Vittoria", 120, 22, 55),
        Proprieta("Via Roma", 150, 25, 60),
        Proprieta("Piazza Grande", 180, 28, 65),
        Proprieta("Lungomare", 200, 30, 70),
        Proprieta("Vicolo Stretto", 90, 18, 45),
        Proprieta("Piazza del Popolo", 160, 26, 62),
        Proprieta("Via delle Rose", 130, 23, 57),
        Proprieta("Via Verdi", 140, 24, 58),
        Proprieta("Corso Italia", 170, 27, 63),
        Proprieta("Piazza Navona", 190, 29, 68),
        Proprieta("Vicolo Corto", 85, 17, 42),
        Proprieta("Via del Sole", 110, 21, 52),
        Proprieta("Largo San Marco", 175, 28, 65),
        Proprieta("Viale dei Fiori", 195, 31, 72),
        Proprieta("Via dei Mille", 125, 24, 58)

    };

}
