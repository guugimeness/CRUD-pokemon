#ifndef FOGO_H
#define FOGO_H

#include "Pokemon.h"

class Fogo : public Pokemon {
public:
    Fogo(string, int, int, int, int, int, string);
    virtual ~Fogo();
    virtual int getTipo() const;
    void setAtaqueFogo(string);
    string getAtaqueFogo() const;
    virtual void imprime() const;
private:
    string ataqueFogo; // Ataque especial do tipo fogo!
};

#endif /* FOGO_H */