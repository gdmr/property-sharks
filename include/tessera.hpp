#include <string>
#include <vector>
#pragma once

class Tessera
{
private:
    std::string titolo;
    std::string proprietario;
public:
    Tessera();
    ~Tessera();
    void setTitolo(std::string titolo);
    void setProprietario(std::string proprietario);
    std::string getTitolo();
    std::string getProprietario();
    virtual std::string getTipo() const = 0;
};
