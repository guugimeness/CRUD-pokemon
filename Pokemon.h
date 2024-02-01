#ifndef POKEMON_H
#define POKEMON_H   

#include <string>
#include <iostream>
using namespace std;

enum TIPO {FOGO, AGUA};

class Pokemon{
public:
    Pokemon(string, int, int, int, int, int);
    virtual ~Pokemon();
    void setNome(string nome);
    string getNome() const;
    void setXP(int XP);
    int getXP(int XP) const;
    void setHP(int HP);
    int getHP() const;
    void setAtaque(int ataque);
    int getAtaque() const;
    void setDefesa(int defesa);
    int getDefesa() const;
    void setVelAtk(int velocidadeAtk);
    int getVelAtk() const;
    void setVelDef(int velocidadeDef);
    int getVelDef() const;
    void setVelocidade(int velocidade);
    int getVelocidade() const;
    virtual int getTipo() const = 0; // Método abstrato
    virtual void imprime() const;
private:
    string nome;
    int XP;
    int HP;
    int ataque;
    int defesa;
    int velocidadeAtk;
    int velocidadeDef;
    int velocidade;
};

#endif /* POKEMON_H */