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

