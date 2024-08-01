#include "tabellone.hpp"

Tabellone::Tabellone() {
    creaTabellone();
}

Tabellone::~Tabellone() {}

void Tabellone::creaTabellone() {
inconvenienti = std::vector<Inconvenienti>{
    Inconvenienti("Vai in prigione", 0, true),
    Inconvenienti("Bollo auto", 50, false),
    Inconvenienti("Eccesso di velocità", 100, true),
    Inconvenienti("Vai in prigione", 0, true)
    };

opportunita = std::vector<Opportunita>{
    Opportunita("Piccolo boost", false, 500),
    Opportunita("Evasione fiscale", true, 10),
    Opportunita("Esci di prigione", true, 0),
    Opportunita("Giorno fortunato", false, 100),
};


caselle.push_back(std::make_shared<Proprieta>("START", 100, 20, 50));
caselle.push_back(std::make_shared<Proprieta>("Corso della Vittoria", 120, 22, 55));
caselle.push_back(std::make_shared<Proprieta>("Via Roma", 150, 25, 60));
caselle.push_back(std::make_shared<Proprieta>("Piazza Grande", 180, 28, 65));
caselle.push_back(std::make_shared<Opportunita>(opportunita));
caselle.push_back(std::make_shared<Proprieta>("Vicolo Stretto", 90, 18, 45));
caselle.push_back(std::make_shared<Proprieta>("Piazza del Popolo", 160, 26, 62));
caselle.push_back(std::make_shared<Proprieta>("Via delle Rose", 130, 23, 57));
caselle.push_back(std::make_shared<Proprieta>("Via Verdi", 140, 24, 58));
caselle.push_back(std::make_shared<Proprieta>("Corso Italia", 170, 27, 63));
caselle.push_back(std::make_shared<Proprieta>("Piazza Navona", 190, 29, 68));
caselle.push_back(std::make_shared<Proprieta>("Vicolo Corto", 85, 17, 42));
caselle.push_back(std::make_shared<Proprieta>("Via del Sole", 110, 21, 52));
caselle.push_back(std::make_shared<Proprieta>("Largo San Marco", 175, 28, 65));
caselle.push_back(std::make_shared<Proprieta>("Viale dei Fiori", 195, 31, 72));
caselle.push_back(std::make_shared<Prigione>("Prigione", 2));
caselle.push_back(std::make_shared<Proprieta>("Viale degli Angeli", 210, 33, 75));
caselle.push_back(std::make_shared<Proprieta>("Corso Garibaldi", 135, 23, 56));
caselle.push_back(std::make_shared<Proprieta>("Via Mazzini", 160, 26, 61));
caselle.push_back(std::make_shared<Proprieta>("Lungotevere", 200, 30, 70));
caselle.push_back(std::make_shared<Inconvenienti>(inconvenienti));
caselle.push_back(std::make_shared<Proprieta>("Vicolo Largo", 95, 19, 47));
caselle.push_back(std::make_shared<Proprieta>("Piazza Garibaldi", 155, 25, 60));
caselle.push_back(std::make_shared<Proprieta>("Lungomare", 150, 30, 70));
caselle.push_back(std::make_shared<Proprieta>("Corso Vittorio", 190, 29, 68));
caselle.push_back(std::make_shared<Proprieta>("Vicolo Corto", 85, 17, 42));
caselle.push_back(std::make_shared<Proprieta>("Via del Campo", 105, 20, 50));
caselle.push_back(std::make_shared<Proprieta>("Largo Augusto", 180, 28, 65));
caselle.push_back(std::make_shared<Proprieta>("Viale della Libertà", 195, 31, 72));
caselle.push_back(std::make_shared<Proprieta>("Via dei Castagni", 125, 24, 58));
caselle.push_back(std::make_shared<Proprieta>("Via lunario", 195, 31, 72));
caselle.push_back(std::make_shared<Proprieta>("Corso alberti", 125, 24, 58));
 
}

std::shared_ptr<Tessera> Tabellone::getTessera(int posizione) {
if (posizione >= 0 && posizione < static_cast<int>(caselle.size())) {
        return caselle[posizione];
    }
    return nullptr;
}

std::vector<std::shared_ptr<Tessera>> Tabellone::getCaselle(){
    return caselle;
}


Opportunita Tabellone::getOpportunita() const {
    // Usa un generatore di numeri casuali
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<std::size_t> distribuzione(0, opportunita.size() - 1);
    std::size_t indiceCasuale = distribuzione(rng);
    return opportunita[indiceCasuale];
}

Inconvenienti Tabellone::getInconveniente() const {
    // Usa un generatore di numeri casuali
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<std::size_t> distribuzione(0, inconvenienti.size() - 1);
    std::size_t indiceCasuale = distribuzione(rng);
    return inconvenienti[indiceCasuale];
}