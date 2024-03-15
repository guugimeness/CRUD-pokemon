#include "Agua.h"

Agua::Agua(string nome, int ataque, int defesa, int velAtk, int velDef, int vel, string atkEsp) :
Pokemon(nome, ataque, defesa, velAtk, velDef, vel), ataqueAgua(atkEsp) {}

Agua::~Agua() {}

int Agua::getTipo() const {
    return AGUA;    
}

void Agua::setAtaqueAgua(string atkEsp) {
    this->ataqueAgua = atkEsp;
}

string Agua::getAtaqueAgua() const {
    return ataqueAgua;
}

void Agua::imprime() const {
    Pokemon::imprime();
    cout << "Ataque especial: " << this->ataqueAgua << endl;
}