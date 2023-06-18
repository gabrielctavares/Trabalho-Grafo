#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <bits/stdc++.h>
#include <iterator>
#include <list>
#include <Grafo.h>

using namespace std;

Grafo* geraGrafo(string caminhoArquivo, bool direcionado, bool pondAresta, bool pondVertice);

int main(int argc, const char* argv[]){
    if(argc != 6){
        cout << "ERRO: Entrada Invalida" << endl;
        cout << "Esperado: arquivo_entrada arquivo_saida direc[0,1] pondAresta[0,1] pondVertice[0,1]" << endl;
        return 1;
    }

    string arquivoEntrada(argv[1]);
    string arquivoSaida(argv[2]);
    bool direcionado = (strcmp(argv[3], "1") == 0);
    bool pondAresta = (strcmp(argv[4], "1") == 0);
    bool pondVertice = (strcmp(argv[5], "1") == 0);

    Grafo* grafo = geraGrafo(arquivoEntrada, direcionado, pondAresta, pondVertice);

    //imprimeOpcoes();
    grafo->imprimeGrafo();

    cout << "Componentes fortemente conexas:\n";
    vector<vector<No*>> result = grafo->compFortConex();
    for (vector<No*> component : result) {
        for (No* no : component) {
            cout << no->getId() << " ";
        }
        cout << ""<< endl;
    }

    /*
    cout << "Ordem do grafo: " << grafo->ordemGrafo() << endl;
    for(int i=0; i<grafo->ordemGrafo(); i++){
        cout << "Grau do no " << i+1 << ": " << grafo->grauNo(i+1)[0] << endl;
    }

    */
    cout << "Eh 4-regular? " << grafo->verificaK(4) << endl;


    cout << "Imprimindo grafo oficial --------" << endl;
    grafo->imprimeGrafo();
    cout << "----------------------" << endl;

    cout << "Imprimindo grafo complementar --------" << endl;
    grafo->complementarGrafo()->imprimeGrafo();
    cout << "----------------------" << endl;

    cout << "Fecho transitivo direto do no 1: ";
    list<int> fechoDireto;
    grafo->fechoTransDir(1, fechoDireto);

    cout << "Fecho transitivo indireto do no 1: ";
    list<int> fechoIndireto;
    grafo->fechoTransInd(1, fechoIndireto);

    cout << "O no 1 � adjacente a 4?(0 - falso / 1 - verdadeiro): " << grafo->ehAdjacente(1, 4) << endl;

    cout << "O grafo � euleriano?(0 - falso / 1 - verdadeiro): " << grafo->ehEuleriano() << endl;

    delete grafo;
    return 0;
}

Grafo* geraGrafo(string caminhoArquivo, bool direcionado, bool pondAresta, bool pondVertice)
{
    ifstream arquivo;
    arquivo.open(caminhoArquivo);
    if (!arquivo)
    {
        cout << "ERROR - FILE NOT FOUND";
        exit(-1);
    }

    int tempNo1, tempNo2, tempPeso, numeroNo = 0;
    std::string buffer = "";

    getline(arquivo, buffer); // Primeira linha
    numeroNo = std::stoi(buffer);

    Grafo *g = new Grafo(numeroNo, direcionado, pondAresta, pondVertice);
    int i = 0;
    while (arquivo >> tempNo1 >> tempNo2 >> tempPeso)
    {
        i++;
        std::cout << i << " Line Read: " << tempNo1 << " " << tempNo2 << " " << tempPeso << std::endl;

        g->addArco(tempNo1, tempNo2, tempPeso);
        tempPeso = 0;
        tempNo1 = 0;
        tempNo2 = 0;
    }
    arquivo.close();
    return g;
}

int exibeMenu(){
    int opMenu;

    cout << " 1- Verificar o Grau de um vértice" << endl;
    cout << " 2- Verificar o Grau de G" << endl;
    cout << " 3- Verificar adjacência entre vértices" << endl;
    cout << " 4- Listar os adjacentes de um vértice" << endl;
    cout << " 5- Dado um conjunto x de vértices, retornar o grafo induzido por x" << endl;
    cout << " 6- Verificar se o Grafo é K-Regular" << endl;
    cout << " 7- Retornar o Grafo Complementar G" << endl;
    cout << " 8- Verificar se o Grafo é Completo" << endl;
    cout << " 9- Verificar se o Grafo é Bipartido" << endl;
    cout << "10- Verificar se o Grafo é conexo" << endl;
    cout << "11- Verificar se um dado Vértice é de Articulação" << endl;
    cout << "12- Verificar se uma dada Aresta é Ponte" << endl;
    cout << "13- Remover Vértice" << endl;
    cout << "14- Remover Aresta" << endl;
    cout << "15- Fecho Transitivo" << endl;
    cout << "16- Fecho Intransitivo" << endl;
    cout << "17- Cobertura de Vértices Guloso" << endl;
    cout << "18- Cobertura de Vértices Guloso Randomizado" << endl;
    cout << "19- Cobertura de Vértices Guloso Randomizado Reativo" << endl;
    cout << " 0- Sair" << endl;
    cout << "\nOpção: ";
    cin >> opMenu;
    return opMenu;
}
 void imprimeOpcoes(){

 }
