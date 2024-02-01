#include "Pokemon.h"

Pokemon::Pokemon(string nome, int ataque, int defesa, int velAtk, int velDef, int vel) :
nome(nome), ataque(ataque), defesa(defesa), velocidadeAtk(velAtk), velocidadeDef(velDef), velocidade(vel) {
    this->XP = 0;
    this->HP = 100;
}

Pokemon::~Pokemon() {}

/*
    Getters e Setters
*/

void Pokemon::imprime() const {
    cout << "------------ " << this->nome << " Stats" << " ------------" << endl;
    cout << "Tipo: " << this->getTipo() << endl;
    cout << "Experiência(XP): " << this->XP << endl;
    cout << "Vida(HP): " << this->HP << endl;
    cout << "Ataque: " << this->ataque << endl;
    cout << "Defesa: " << this->defesa << endl; 
    cout << "Velocidade de Ataque: " << this->velocidadeAtk << endl;     
    cout << "Velocidade de Defesa: " << this->velocidadeDef << endl;
    cout << "Velocidade: " << this->velocidade << endl;
}

