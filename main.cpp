#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <bits/stdc++.h>
#include <iterator>
#include <list>
#include "Grafo.h"

using namespace std;

Grafo* geraGrafo(string caminhoArquivo, string caminhoSaida, bool direcionado, bool pondAresta, bool pondVertice);
int exibeMenu();

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

    Grafo* grafo = geraGrafo(arquivoEntrada, arquivoSaida, direcionado, pondAresta, pondVertice);

    //imprimeOpcoes();
//    grafo->imprimeGrafo();
//
//    cout << "Componentes fortemente conexas:\n";
//    vector<vector<No*>> result = grafo->compFortConex();
//    for (vector<No*> component : result) {
//        for (No* no : component) {
//            cout << no->getId() << " ";
//        }
//        cout << ""<< endl;
//    }
//
//
//    cout << "Ordem do grafo: " << grafo->ordemGrafo() << endl;
//    for(int i=0; i<grafo->ordemGrafo(); i++){
//        cout << "Grau do no " << i+1 << ": " << grafo->grauNo(i+1)[0] << endl;
//    }
//    cout << "Eh 4-regular?(0 - falso / 1 - verdadeiro): " << grafo->verificaK(4) << endl;
//
//
//    cout << "Imprimindo grafo oficial --------" << endl;
//    grafo->imprimeGrafo();
//    cout << "----------------------" << endl;
//
//    cout << "Imprimindo grafo complementar --------" << endl;
//    //grafo->complementarGrafo()->imprimeGrafo();
//    cout << "----------------------" << endl;
//
//    cout << "Fecho transitivo direto do no 1: ";
//    list<int> fechoDireto;
//    grafo->fechoTransDir(1, fechoDireto);
//
//    cout << "Fecho transitivo indireto do no 1: ";
//    list<int> fechoIndireto;
//    grafo->fechoTransInd(1, fechoIndireto);
//
//    cout << "O no 1 eh adjacente a 4?(0 - falso / 1 - verdadeiro): " << grafo->ehAdjacente(1, 4) << endl;
//
//    cout << "O grafo eh euleriano?(0 - falso / 1 - verdadeiro): " << grafo->ehEuleriano() << endl;
//
//    for(int i=1; i<=grafo->ordemGrafo(); i++)
//        cout << "O no " << i << " eh no de articulacao?(0 - falso / 1 - verdadeiro): " << grafo->ehNoArt(i) << endl;
//
//    //cout << "Eh conexo? " << grafo->ehConexo() << endl;
//    //cout << "Eh bipartido? " << grafo->ehBipartido() << endl;
//    cout << "N de componentes conexas: " << grafo->compCon() << endl;
//
float* alphas = new float[5];
    alphas[0] = 0.05;
    alphas[1] = 0.1;
    alphas[2] = 0.15;
    alphas[3] = 0.3;
    alphas[4] = 0.5;

int valMenu = exibeMenu();
int idMenu1;

while(valMenu != 0)
{
    switch(valMenu)
    {
    case 1:
        cout << "Digite o id do no: ";
        cin >> idMenu1;
        if(grafo->grauNo(idMenu1)!= NULL)
        {
            cout << "Grau de saida do no: " << grafo->grauNo(idMenu1)[0]<<endl;
            if(direcionado)
                cout << "Grau de entrada do no: " << grafo->grauNo(idMenu1)[1]<<endl;
        }
        break;
    case 2:
        cout << "O grau do grafo eh: " << grafo->grauGrafo() <<endl;
        break;
    case 3:
        cout << "Digite o id do primeiro no: ";
        cin >> idMenu1;
        int idMenu2;
        cout << "Digite o id do segundo no: ";
        cin >> idMenu2;
        if(grafo->ehAdjacente(idMenu1,idMenu2))
            cout << "Sao adjacentes"<<endl;
        else
            cout << "Nao sao adjacentes"<<endl;
        break;
    case 4:{
        cout << "Digite o id do no: ";
        int id;
        cin >> id;
        list<int> adj;
        grafo->listaAdjacentes(id, adj);
        if(!adj.empty()){
            cout << "Nos adjacentes a " << id << ": " << endl;
            for(list<int>::iterator i = adj.begin(); i!=adj.end(); ++i){
                cout << *i << " ";
            }
            cout << endl;
        }
        break;
    }
    case 5:
        int K;
        cout << "Digite o valor K: ";
        cin >> K;
        if(grafo->verificaK(K))
        cout << "O grafo eh " << K << "-regular"<<endl;
        else
            cout << "O grafo nao eh " << K << "-regular"<<endl;
        break;
    case 6:{
        cout<< "=======Grafo complementar=========" << endl;
        Grafo* complementar = grafo->complementarGrafo();
        complementar->imprimeGrafo();
        cout<< "==================================" << endl;
        break;
    }
    case 7:
        if(grafo->ehCompleto())
            cout << "O grafo eh completo"<<endl;
        else
            cout << "O grafo nao eh completo"<<endl;
        break;
    case 8:
        if(grafo->ehConexo())
            cout << "O grafo eh conexo" <<endl;
        else
            cout << "O grafo nao eh conexo" <<endl;
        break;
    case 9:
        cout << "Digite o id do no: ";
        cin >> idMenu1;
        if(grafo->ehNoArt(idMenu1))
            cout << "O no eh de articulacao" << endl;
        else
            cout << "O no nao eh de articulacao" <<endl;
        break;
    case 10:
        grafo->imprimeIdNoArt();
        break;
    case 11:
        cout << "Sequencia de graus:"<<endl;
        grafo->seqGraus();
        break;
    case 12:
        if(grafo->ehNulo())
        cout << "O grafo eh nulo" <<endl;
        else
        cout << "O grafo nao eh nulo"<<endl;
        break;
    case 13:
        if(grafo->ehTrivial())
        cout << "O grafo eh trivial"<<endl;
        else
        cout << "O grafo nao eh trivial"<<endl;
        break;
    case 14:
        cout << "O grafo possui " << grafo->compCon() << " componentes conexas"<<endl;
        break;
    case 15:
        cout << "O grafo possui ordem " << grafo->ordemGrafo() <<endl;
        break;
    case 16:
        if(grafo -> ehEuleriano())
        cout << "O grafo eh euleriano" <<endl;
        else
        cout << "O grafo nao eh euleriano" <<endl;
        break;

    case 17:
    {
        cout << "Executando algoritmo guloso..." << endl;
        list<int> solucaoGuloso;
        grafo->cobertVertPondG(solucaoGuloso);
        cout << "Executado!" << endl;
        break;
    }
    case 18:
    {
        cout << "Executando algoritmos randomizados..." << endl;
        for(int i=0; i<5; i++){
            cout << "Com alpha igual a " << alphas[i] << endl;
            list<int> solucaoRando;
            grafo->cobertVertPondGR(solucaoRando, 1000, alphas[i]);
            cout << "Executado!" << endl;
        }
        break;
    }
    case 19:
    {
        cout << "Executando algoritmo reativo..." << endl;
        list<int> solucaoReativo;
        grafo->cobertVertPondGRR(solucaoReativo, 5000, alphas, 5);
        cout << "Executado!" << endl;
        break;
    }
    default:
        cout << "Opcao invalida" <<endl;
        break;
    }
    valMenu = exibeMenu();
}

    delete grafo;
    return 0;
}

Grafo* geraGrafo(string caminhoArquivo, string caminhoSaida, bool direcionado, bool pondAresta, bool pondVertice)
{
    ifstream arquivo;
    arquivo.open(caminhoArquivo);
    if (!arquivo)
    {
        cout << "ERROR - FILE NOT FOUND";
        exit(-1);
    }

    int numeroNo = 0;
    std::string buffer = "";
    getline(arquivo, buffer); // Primeira linha
    numeroNo = std::stoi(buffer);

    Grafo *g = new Grafo(numeroNo, direcionado, pondAresta, pondVertice, caminhoSaida);
    int i = 0;

    if(pondAresta){
        int tempNo1, tempNo2, tempPeso;
        while (arquivo >> tempNo1 >> tempNo2 >> tempPeso)
        {
            i++;
            std::cout << i << " Line Read: " << tempNo1 << " " << tempNo2 << " " << tempPeso << std::endl;

            g->addArco(tempNo1, tempNo2, tempPeso);
            tempPeso = 0;
            tempNo1 = 0;
            tempNo2 = 0;
        }
    }
    else{
        char aux;
        int tempNo1, tempNo2;
        while(arquivo >> aux >> tempNo1 >> tempNo2){
            i++;
            std::cout << i << " Line Read: " << aux << " " << tempNo1 << " " << tempNo2 << std::endl;

            g->addArco(tempNo1, tempNo2, 0);
            tempNo1 = 0;
            tempNo2 = 0;
        }
    }

    arquivo.close();
    ofstream saida(caminhoSaida, ios::trunc);
    if(saida.is_open()){
        saida << "---------Logs----------" << endl;
        saida.close();
    }
    else
        cout << "Erro: nao foi possivel abrir arquivo de saida" << endl;
    return g;
}

int exibeMenu(){
    int opMenu;

    cout << "\n 1- Verificar o Grau de um vertice" << endl;
    cout << " 2- Verificar o Grau de G" << endl;
    cout << " 3- Verificar adjacencia entre vertices" << endl;
    cout << " 4- Listar os adjacentes de um vertice" << endl;
    cout << " 5- Verificar se o Grafo eh K-Regular" << endl;
    cout << " 6- Retornar o Grafo Complementar G" << endl;
    cout << " 7- Verificar se o Grafo eh Completo" << endl;
    cout << "8- Verificar se o Grafo eh conexo" << endl;
    cout << "9- Verificar se um dado Vertice eh de Articulacao" << endl;
    //cout << "10- Verificar se uma dada Aresta é Ponte" << endl;
    cout << "10- Listar os nos de articulacao" << endl;
    cout << "11- Mostrar sequencia de graus" << endl;
    cout << "12- Verificar se o grafo eh nulo" << endl;
    cout << "13- Verificar se o grafo eh trivial" << endl;
    cout << "14- Verificar o numero de componentes conexas do grafo" <<endl;
    cout << "15- Verificar a ordem do grafo" << endl;
    cout << "16- Verificar se o grafo eh euleriano" << endl;
    cout << "17- Cobertura de Vertices Ponderados Guloso" << endl;
    cout << "18- Cobertura de Vertices Ponderados Guloso Randomizado" << endl;
    cout << "19- Cobertura de Vertices Ponderados Guloso Randomizado Reativo" << endl;
    cout << " 0- Sair" << endl;
    cout << "\nOpcao: ";
    cin >> opMenu;
    return opMenu;
}
 void imprimeOpcoes(){

 }
