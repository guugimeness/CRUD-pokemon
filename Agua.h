#ifndef AGUA_H
#define AGUA_H

#include "Pokemon.h"

class Agua : public Pokemon {
public:
    Agua(string, int, int, int, int, int, string);
    virtual ~Agua();
    virtual int getTipo() const;
    void setAtaqueAgua(string);
    string getAtaqueAgua() const;
    virtual void imprime() const;
private:
    string ataqueAgua; // Ataque especial do tipo água!
};

#endif /* FOGO_H */