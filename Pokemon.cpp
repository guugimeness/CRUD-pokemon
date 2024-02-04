#include "Pokemon.h"

Pokemon::Pokemon(string nome, int ataque, int defesa, int velAtk, int velDef, int vel) :
nome(nome), ataque(ataque), defesa(defesa), velocidadeAtk(velAtk), velocidadeDef(velDef), velocidade(vel) {
    this->XP = 0;
    this->HP = 100;
}

Pokemon::~Pokemon() {}

void Pokemon::setNome(string nome) {
    this->nome = nome;
}

string Pokemon::getNome() const {
    return this->nome;
}

void Pokemon::setXP(int XP) {
    this->XP += XP;
}

int Pokemon::getXP() const {
    return this->XP;
}

void Pokemon::setHP(int HP) {
    this->HP = HP;
}

int Pokemon::getHP() const {
    return this->HP;
}

void Pokemon::setAtaque(int ataque) {
    this->ataque = ataque;
}

int Pokemon::getAtaque() const {
    return this->ataque;
}

void Pokemon::setDefesa(int defesa) {
    this->defesa = defesa;
}

int Pokemon::getDefesa() const {
    return this->defesa;
}

void Pokemon::setVelAtk(int velAtk) {
    this->velocidadeAtk = velAtk;
}

int Pokemon::getVelAtk() const {
    return this->velocidadeAtk;
}

void Pokemon::setVelDef(int velDef) {
    this->velocidadeDef = velDef;
}

int Pokemon::getVelDef() const {
    return this->velocidadeDef;
}

void Pokemon::setVelocidade(int vel) {
    this->velocidade = vel;
}

int Pokemon::getVelocidade() const {
    return this->velocidade;
}

void Pokemon::imprime() const {
    cout << "------------ " << this->nome << " Stats" << " ------------" << endl;
    cout << "Tipo: " << (this->getTipo() ? "Água" : "Fogo") << endl;
    cout << "Experiência(XP): " << this->XP << endl;
    cout << "Vida(HP): " << this->HP << endl;
    cout << "Ataque: " << this->ataque << endl;
    cout << "Defesa: " << this->defesa << endl; 
    cout << "Velocidade de Ataque: " << this->velocidadeAtk << endl;     
    cout << "Velocidade de Defesa: " << this->velocidadeDef << endl;
    cout << "Velocidade: " << this->velocidade << endl;
}

bool Pokemon::comparaAtaque(const Pokemon* p1, const Pokemon* p2) {
    return p1->ataque > p2->ataque  ;
}