#include "CRUD.h"
#include "Fogo.h"
#include "Agua.h"
#include <algorithm>
#include <fstream>
using namespace std;

CRUD::CRUD(string fileName) : fileName(fileName) {
    recupera(); // Perisistência das informações
}

CRUD::~CRUD() {
    // Deletando os objetos criados dinamicamente para manipular as informações
    for (auto objeto : pokemons) {
        delete objeto;
    }
    pokemons.clear();
}

// Recupera informações do arquivo para gerenciar em run time
void CRUD::recupera(){
    // Abrindo o arquivo
    ifstream database(fileName, ios::binary);

    // Verificando se o arquivo foi aberto
    if(!database.is_open()){
        cerr << "Não foi possivel abrir o arquivo!" << endl;
        return;
    }

    Fogo* f;
    Agua* a;
    string nomePokemon;
    int tipo, ataque, defesa, velAtk, velDef, vel, XP, HP;
    string ataqueEsp;
    unsigned long int nomeTamanho, ataqueTamanho;

    pokemons.clear(); // Limpando o vetor para ler do arquivo

    // Lendo tipo
    database.read(reinterpret_cast<char*>(&tipo), sizeof(tipo));

    while(database.good()) {
        // Lendo nome
        database.read(reinterpret_cast<char*>(&nomeTamanho), sizeof(nomeTamanho));
        nomePokemon.resize(nomeTamanho);
        database.read(reinterpret_cast<char*>(&nomePokemon[0]), (unsigned int)nomeTamanho);

        // Lendo ataque
        database.read(reinterpret_cast<char*>(&ataque), sizeof(ataque));

        // Lendo defesa
        database.read(reinterpret_cast<char*>(&defesa), sizeof(defesa));

        // Lendo velocidade de ataque
        database.read(reinterpret_cast<char*>(&velAtk), sizeof(velAtk));

        // Lendo velocidade de defesa
        database.read(reinterpret_cast<char*>(&velDef), sizeof(velDef));

        // Lendo velocidade
        database.read(reinterpret_cast<char*>(&vel), sizeof(vel));

        // Lendo atributo único de cada tipo
        database.read(reinterpret_cast<char*>(&ataqueTamanho), sizeof(ataqueTamanho));
        ataqueEsp.resize(ataqueTamanho);
        database.read(reinterpret_cast<char*>(&ataqueEsp[0]), (unsigned int)ataqueTamanho);

        // Lendo XP
        database.read(reinterpret_cast<char*>(&XP), sizeof(XP));

        // Lendo HP
        database.read(reinterpret_cast<char*>(&HP), sizeof(HP));

        if(tipo == FOGO) {
            f = new Fogo(nomePokemon, ataque, defesa, velAtk, velDef, vel, ataqueEsp);
            // XP e HP são atributos padronizados pelo construtor
            // Por isso, devem ser setados por fora
            f->setXP(XP);
            f->setHP(HP);
            pokemons.push_back(f);
        } else {
            a = new Agua(nomePokemon, ataque, defesa, velAtk, velDef, vel, ataqueEsp);
            a->setXP(XP);
            a->setHP(HP);
            pokemons.push_back(a);
        }

        // Lendo tipo
        database.read(reinterpret_cast<char*>(&tipo), sizeof(tipo));
    };
 
    // Fechando o arquivo
    database.close();
};

// Grava o que foi feito em run time no arquivo
void CRUD::grava(){
    // Abrindo o arquivo
    ofstream database(fileName, ios::binary);

    Pokemon* pokemon;
    Fogo* f;
    Agua* a;
    string nomePokemon, ataqueAgua, ataqueFogo;
    int tipo, ataque, defesa, velAtk, velDef, vel, XP, HP;
    unsigned long int qtdPokemons = pokemons.size(); // Evitar chamadas excessivas a size
    unsigned long int nomeTamanho;

    // Verificando se o arquivo foi aberto
    if(!database.is_open()){
        cerr << "Não foi possivel abrir o arquivo!" << endl;
        return;
    }

    for(unsigned long int i = 0; i < qtdPokemons; i++){
        pokemon = pokemons[i];

        nomePokemon = pokemon->getNome();
        nomeTamanho = nomePokemon.size();
        tipo = pokemon->getTipo();

        // Tipo
        database.write(reinterpret_cast<char*>(&tipo), sizeof(tipo));

        // Nome
        database.write(reinterpret_cast<char *>(&nomeTamanho), sizeof(nomeTamanho));
        database.write(reinterpret_cast<char*>(&nomePokemon[0]), (unsigned int)nomeTamanho);

        // Ataque
        ataque = pokemon->getAtaque();
        database.write(reinterpret_cast<char*>(&ataque), sizeof(ataque));

        // Defesa
        defesa = pokemon->getDefesa();
        database.write(reinterpret_cast<char*>(&defesa), sizeof(defesa));

        // Vel.Atk.
        velAtk = pokemon->getVelAtk();
        database.write(reinterpret_cast<char*>(&velAtk), sizeof(velAtk));

        // Vel.Def.
        velDef = pokemon->getVelDef();
        database.write(reinterpret_cast<char*>(&velDef), sizeof(velDef));

        // Vel
        vel = pokemon->getVelocidade();
        database.write(reinterpret_cast<char*>(&vel), sizeof(vel));

        // Ataque Especial
        switch (tipo) {
            case FOGO: {
                f = dynamic_cast<Fogo*>(pokemon);  // Convertendo para poder acessar o atributo especial
                ataqueFogo = f->getAtaqueFogo();
                nomeTamanho = ataqueFogo.size();
                database.write(reinterpret_cast<char *>(&nomeTamanho), sizeof(nomeTamanho));
                database.write(reinterpret_cast<char*>(&ataqueFogo[0]), (unsigned int)nomeTamanho);
                break;
            }
            case AGUA: {
                a = dynamic_cast<Agua*>(pokemon);
                ataqueAgua = a->getAtaqueAgua();
                nomeTamanho = ataqueAgua.size();
                database.write(reinterpret_cast<char *>(&nomeTamanho), sizeof(nomeTamanho));
                database.write(reinterpret_cast<char*>(&ataqueAgua[0]), (unsigned int)nomeTamanho);
                break;
            }
        }

        // XP
        XP = pokemon->getXP();
        database.write(reinterpret_cast<char*>(&XP), sizeof(XP));

        // HP
        HP = pokemon->getHP();
        database.write(reinterpret_cast<char*>(&HP), sizeof(HP));
    }

    // Fechando o arquivo
    database.close();
};

// Adiciona pokemon
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

// Remove pokemon
bool CRUD::remove(string nome) {
    bool ok = false;
    vector<long unsigned int>* pos = indice(nome); // Acha a posição do pokemon no vector
    unsigned long int size = pos->size();

    if(size == 0) {
        cout << "Este pokemon não está na sua pokedex!" << endl;
    } else if(size == 1){
        pokemons.erase(pokemons.begin() + (long int)(*pos)[0]);
        grava();
        ok = true;
    } else {    // Tratamento do caso em que há mais de um objeto com o mesmo nome
        long unsigned int indexParaRemover;
        cout << "Há mais de um pokemon com esse nome! Qual deles você deseja remover?" << endl;
        for (unsigned long int i = 0; i < size; i++){   // Mostrando as opções de escolha para o usuário
            cout << "[" << (i + 1) << "]: " << endl;
            pokemons[(*pos)[i]]->imprime();
            cout << endl;
        }
        cout << "Digite o índice " << "[" << 1 << "-" << size << "]: ";
        cin >> indexParaRemover;
        cout << endl;
        indexParaRemover = (*pos)[indexParaRemover-1]; // Para o usuário os arrays comecam em 1
        pokemons.erase(pokemons.begin() + (long int)indexParaRemover);
        grava();
        ok = true;
    }
    delete pos;
    return ok;
}

// Atualiza XP
bool CRUD::atualiza(string nome) {
    int XP;
    bool ok = false;
    vector<long unsigned int>* pos = indice(nome);
    unsigned long int size = pos->size();
    
    if(size == 0) {
        cout << "Este pokemon não está na sua pokedex!" << endl;
        return ok;
    } 

    cout << "Quando de XP quer adicionar para " << nome << "?" << endl;
    cin >> XP;
    cout << endl;

    if(size == 1) {
        pokemons[(long unsigned int)(*pos)[0]]->setXP(XP);
        grava();
        ok = true;
    } else {    // Tratamento do caso em que há mais de um objeto com o mesmo nome
        unsigned long int indexParaAdicionar;
        cout << "Há mais de um pokemon com esse nome! Para qual deles você deseja adicionar XP?" << endl;
        for (unsigned long int i = 0; i < size; i++){   // Mostrando as opções de escolha para o usuário
            cout << "[" << (i + 1) << "]: " << endl;
            pokemons[(*pos)[i]]->imprime();
            cout << endl;
        }
        cout << "Digite o índice " << "[" << 1 << "-" << size << "]: ";
        cin >> indexParaAdicionar;
        cout << endl;
        indexParaAdicionar = (*pos)[indexParaAdicionar-1]; // Para o usuário os arrays comecam em 1
        pokemons[indexParaAdicionar]->setXP(XP);
        grava();
        ok = true;
    }

    return ok;
}

// Imprime todos os pokemons
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

// Imprime pokemon por nome
void CRUD::imprime(string nome) {
    vector<long unsigned int>* pos = indice(nome);
        
    if(pos->size() == 0){
        cout << "Este pokemon não está na sua pokedex!" << endl;
    } else {
        for(unsigned long int i = 0; i < pos->size(); i++) {
            pokemons[(*pos)[i]]->imprime();
            cout << endl;
        }
    }
    delete pos;
}

// Menu de opções da pokedex
char CRUD::opcao() {
    char o;
    cout << "** Bem-vindo à sua Pokedex! **" << endl;
    cout << "[P] Mostrar todos os seus pokemons" << endl;
    cout << "[N] Mostrar um pokemon" << endl;
    cout << "[S] Mostrar todos os seus pokemons ordenado por força" << endl;
    cout << "[F] Adicionar pokemon de fogo" << endl;
    cout << "[A] Adicionar pokemon de água" << endl;
    cout << "[U] Atualizar XP de um pokemon" << endl;
    cout << "[R] Remover pokemon" << endl;
    cout << "[C] Fechar pokedex" << endl;
    cin >> o;
    return (toupper(o));
}

// Acha a posição do objeto no vector
vector<long unsigned int>* CRUD::indice(string nome) {
    vector<long unsigned int>* indexes = new vector<long unsigned int>;
    long unsigned int size = pokemons.size();
    long unsigned int pos = 0;
    
    for(pos = 0; pos < size; pos++) {
        if(pokemons[pos]->getNome() == nome){
            indexes->push_back(pos);
        }
    }
    return indexes;     // Retorna um vetor com a posição de objetos com o mesmo nome
}