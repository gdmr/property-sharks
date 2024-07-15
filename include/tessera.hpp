#include <string>

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
};
