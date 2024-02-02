#include "CRUD.h"
#include "Fogo.h"
#include "Agua.h"
#include <algorithm>
#include <fstream>
using namespace std;

CRUD::CRUD(string fileName) : fileName(fileName) {
    recupera();
}

CRUD::~CRUD() {}

bool CRUD::adiciona(int tipo) {
    int ataque, defesa, velAtk, velDef, vel;
    string nome, ataqueEsp;
    Pokemon* p;

    cin.ignore();
    cout << "Nome do pokemon: ";
    getline(cin, nome);
    cout << "Ataque: ";
    cin >> ataque;
    cout << "Defesa: ";
    cin >> defesa;
    cout << "Velocidade de ataque: ";
    cin >> velAtk;
    cout << "Velocidade de defesa: ";
    cin >> velDef;
    cout << "Velocidade: ";
    cin >> vel;

    switch(tipo) {
        case FOGO: {
            cout << "Ataque especial de fogo: ";
            cin.ignore();
            getline(cin, ataqueEsp);
            p = new Fogo(nome, ataque, defesa, velAtk, velDef, vel, ataqueEsp);
            break;
        }
        case AGUA: {
            cout << "Ataque especial de água: ";
            cin.ignore();
            getline(cin, ataqueEsp);
            p = new Agua(nome, ataque, defesa, velAtk, velDef, vel, ataqueEsp);
            break;
        }
    }

    pokemons.push_back(p);
    grava();
    return true;
}

void CRUD::imprime(bool sorted) {
    vector<Pokemon*> copy = pokemons;

    if(sorted) {
        sort(copy.begin(), copy.end(), Pokemon::comparaAtaque);
    }

    for(long unsigned int i = 0; i<copy.size(); i++) {
        copy[i]->imprime();
        cout << endl;
    }
}

void CRUD::imprime(string nome) {
    int pos = indice(nome);

    if(pos != -1) {
        pokemons[(long unsigned int)pos]->imprime();
    } else {
        cout << "Este pokemon não está na sua pokedex!" << endl;
    }
}

bool CRUD::remove(string nome) {
    bool ok = false;
    int pos = indice(nome); // Acha a posição do pokemon no vector

    if(pos != -1) {
        pokemons.erase(pokemons.begin() + pos);
        grava();
        ok = true;
    }
    
    return ok;
}

bool CRUD::atualiza(string nome) {
    string oi = nome;
    bool ok = true;
    return ok;
}

char CRUD::opcao() {
    char o;
    cout << "** Bem-vindo à sua Pokedex! **" << endl;
    cout << "[P] Mostrar todos os seus pokemons" << endl;
    cout << "[N] Mostrar um pokemon" << endl;
    cout << "[S] Mostrar todos os seus pokemons ordenado por força" << endl;
    cout << "[F] Adicionar pokemon de fogo" << endl;
    cout << "[A] Adicionar pokemon de água" << endl;
    cout << "[R] Remover pokemon" << endl;
    cout << "[C] Fechar pokedex" << endl;
    cin >> o;
    return (toupper(o));
}

void CRUD::grava() {
    
}

void CRUD::recupera() {
    
}

int CRUD::indice(string nome) {  // Acha a posição do objeto no vector
    long unsigned int size = pokemons.size();
    long unsigned int pos = 0;
    
    while(pos < size && pokemons[pos]->getNome() != nome) {
        pos++;
    }

    if(pos < size){
        return (int)pos;
    } else {
        return -1;
    }
}
