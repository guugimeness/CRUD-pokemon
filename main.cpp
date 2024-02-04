#include "CRUD.h"
#include "Fogo.h"
#include "Agua.h"
using namespace std;

int main() {

    char opcao;
    string nome;

    CRUD pokedex("info.dat");

    do {
        opcao = pokedex.opcao();
        cout << endl;
        switch (opcao) {
            case 'P': {
                pokedex.imprime(false); // Na ordem de inserção
                break;
            }
            case 'N': {
                cout << "Insira o nome do pokemon: " << endl;
                cin >> nome;
                pokedex.imprime(nome);
                break;
            }
            case 'S': {
                pokedex.imprime(true);  // Do mais "forte" para o mais "fraco" 
                break;
            }
            case 'F': {
                pokedex.adiciona(FOGO);
                break;
            }
            case 'A': {
                pokedex.adiciona(AGUA);
                break;
            }
            case 'U': {
                cout << "Insira o nome do pokemon: " << endl;
                cin >> nome;
                pokedex.atualiza(nome);
                break;
            }
            case 'R': {
                cout << "Insira o nome do pokemon a ser removido: " << endl;
                cin >> nome;
                bool ok = pokedex.remove(nome);
                cout << "Remoção " << (ok ? "feita com sucesso!" : "deu errado!") << endl;
                break;
            }
        }
        cout << endl;
    } while(opcao != 'C');

}