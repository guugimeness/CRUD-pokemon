#include "Fogo.h"

Fogo::Fogo(string nome, int ataque, int defesa, int velAtk, int velDef, int vel, string atkEsp) :
Pokemon(nome, ataque, defesa, velAtk, velDef, vel), ataqueFogo(atkEsp) {}

Fogo::~Fogo() {}

int Fogo::getTipo() const {
    return FOGO;    
}

void Fogo::setAtaqueFogo(string atkEsp) {
    this->ataqueFogo = atkEsp;
}

string Fogo::getAtaqueFogo() const {
    return ataqueFogo;
}

void Fogo::imprime() const {
    Pokemon::imprime();
    cout << "Ataque especial: " << this->ataqueFogo << endl;
}



