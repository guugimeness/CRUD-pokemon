#ifndef CRUD_H
#define CRUD_H

#include "Pokemon.h"
#include <vector>
using namespace std;

class CRUD {
public:
    CRUD(string fileName);
    virtual ~CRUD();
    bool adiciona(int tipo);
    void imprime(bool sorted = false);
    void imprime(string nome);
    bool remove(string nome);
    bool atualiza(string nome);
    static char opcao();
private:
    void grava();
    void recupera();
    vector<long unsigned int>* indice(string nome);

    string fileName;
    vector<Pokemon *> pokemons;
};

#endif /* CADASTRO_H */