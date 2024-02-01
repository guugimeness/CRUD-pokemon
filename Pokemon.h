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
    void setNome(string);
    string getNome() const;
    void setXP(int);
    int getXP() const;
    void setHP(int);
    int getHP() const;
    void setAtaque(int);
    int getAtaque() const;
    void setDefesa(int);
    int getDefesa() const;
    void setVelAtk(int);
    int getVelAtk() const;
    void setVelDef(int);
    int getVelDef() const;
    void setVelocidade(int);
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