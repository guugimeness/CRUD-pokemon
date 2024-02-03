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

void CRUD::recupera(){
    ifstream database(fileName, ios::binary);
    if(!database.is_open()){
        cerr << "Nao foi possivel abrir o arquivo" << endl;
        return;
    }

    string nomePokemon;
    int tipo;
    int ataque, defesa, velAtk, velDef, vel;
    string ataqueEsp;

    
    while(!database.eof()){
        nomePokemon.erase();

        database.read(reinterpret_cast<char*>(&tipo), sizeof(tipo));

        getline(database, nomePokemon);

        database.read(reinterpret_cast<char*>(&ataque), sizeof(ataque));
        database.read(reinterpret_cast<char*>(&defesa), sizeof(defesa));
        database.read(reinterpret_cast<char*>(&velAtk), sizeof(velAtk));
        database.read(reinterpret_cast<char*>(&velDef), sizeof(velDef));
        database.read(reinterpret_cast<char*>(&vel), sizeof(vel));

        // Ainda nao implementado por causa da gravacao em funcao CRUD::grava
        //getline(database, ataqueEsp);

        // Com certeza tem jeito de melhorar essa parte
        if(tipo == AGUA)
            pokemons.push_back(new Agua(nomePokemon, ataque, defesa, velAtk, velDef, vel, ataqueEsp));
        else
            pokemons.push_back(new Fogo(nomePokemon, ataque, defesa, velAtk, velDef, vel, ataqueEsp));

        database.peek();
    };

};

void CRUD::grava(){
    ofstream database(fileName, ios::binary);

    Pokemon* pokemon;
    string nomePokemon;
    unsigned int nomeTamanho;
    int ataque, defesa, velAtk, velDef, vel;
    int tipo;

    unsigned long int qtdPokemons = pokemons.size(); // Evitar chamadas excessivas a size
    for(unsigned long int i = 0; i < qtdPokemons; i++){
        pokemon = pokemons[i];

        nomePokemon = pokemon->getNome();
        nomeTamanho = nomePokemon.size();

        tipo = pokemon->getTipo();

        // Tipo
        database.write(reinterpret_cast<const char*>(&tipo), sizeof(tipo));

        // Nome
        database.write(reinterpret_cast<const char*>(&nomePokemon[0]), nomeTamanho * sizeof(char));
        database.write("\n", 1);
        // Ataque
        ataque = pokemon->getAtaque();
        database.write(reinterpret_cast<const char*>(&ataque), sizeof(int));
        // Defesa
        defesa = pokemon->getDefesa();
        database.write(reinterpret_cast<const char*>(&defesa), sizeof(int));
        // Vel.Atk.
        velAtk = pokemon->getVelAtk();
        database.write(reinterpret_cast<const char*>(&velAtk), sizeof(int));
        // Vel.Def.
        velDef = pokemon->getVelDef();
        database.write(reinterpret_cast<const char*>(&velDef), sizeof(int));
        // Vel
        vel = pokemon->getVelocidade();
        database.write(reinterpret_cast<const char*>(&vel), sizeof(int));
        // AtaqueEsp
        // O getAtaqueEspecial nao esta implementado ent n pode ser escrito, tera fix dps
        //database.write(reinterpret_cast<const char*>(&(pokemon->getAtaqueEspecial())[0]));
    }
    database.close();
};

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
