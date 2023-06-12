#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <bits/stdc++.h>
#include <iterator>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

Grafo::Grafo(bool ehDigraf, bool ehPondArco, bool ehPondNo)
{
    //constr�i grafo vazio
    n = 0;
    primeiro = NULL;
    ehDigrafo = ehDigraf;
    ehPonderadoNo = ehPondNo;
    ehPonderadoArco = ehPondArco;
}

Grafo::Grafo(int num, bool ehDigraf, bool ehPondArco, bool ehPondNo)
{
    //constr�i grafo com o n�mero de n�s informado
    n = 0;
    primeiro = NULL;
    ehDigrafo = ehDigraf;
    ehPonderadoNo = ehPondNo;
    ehPonderadoArco = ehPondArco;
    for(int i=0; i<num; i++){
        addNo(i+1, 0);
    }
}

Grafo::~Grafo()
{
    cout << "Destruindo grafo" << endl;
    No* aux;
    while(primeiro!=NULL){
        aux = primeiro;
        primeiro = aux->getProxNo();
        delete aux;
        //deleta cada n� da lista de n�s do grafo
    }
    primeiro = NULL;
}

void Grafo::addNo(int id, float peso)
{
    //confere se o id j� est� sendo usado por algum n� do grafo
    for(No* aux = primeiro; aux!=NULL; aux = aux->getProxNo())
        if(id == aux->getId())
        {
            cout << "Erro: id repetido!" << endl;
            return;
        }

    No* no;
    if(ehPonderadoNo)
        no = new No(id, peso); //inicializa um objeto do tipo n� para grafos ponderados no n�
    else
        no = new No(id); //inicializa um objeto do tipo n� para grafos n�o ponderados no n�
    if(n==0)//se o grafo � vazio, o n� adicionado ser� o primeiro n� da lista
    {
        primeiro = no;
    }
    else
    {
        No* aux;
        for(aux = primeiro; aux->getProxNo()!=NULL; aux = aux->getProxNo());//encontra o �ltimo n� na lista de n�s do grafo
        aux->setProxNo(no);//adiciona o n� no final da lista
    }
    //acrescenta 1 na quantidade de n�s do grafo
    n++;
}

void Grafo::removeNo(int id)
{
    if(n==0)
        cout<<"ERRO: lista vazia!" << endl;
    else
    {
        No* aux = primeiro;
        for(No* aux2=NULL; aux!=NULL; aux2 = aux ,aux = aux->getProxNo())
        {
            if(id==aux->getId())
            {
                aux2->setProxNo(aux->getProxNo());
                delete aux;
                n--;
                return;
            }
        }
    }
}

void Grafo::addArco(int orig, int dest, float p)
{
    No* auxOrig;
    No* auxDest;

    for(auxOrig = primeiro; auxOrig->getId()!=orig && auxOrig!=NULL; auxOrig = auxOrig->getProxNo());

    if(auxOrig==NULL){
        cout << "Erro: n� n�o est� contido no grafo" << endl;
        return;
    }

    //verifica se o n� dest est� contido no grafo
    for(auxDest = primeiro; auxDest->getId()!=dest && auxDest!=NULL; auxDest = auxDest->getProxNo());

    if(auxDest==NULL){
        cout << "Erro: n� n�o est� contido no grafo" << endl;
        return;
    }

    auxOrig->addArco(dest, p, ehPonderadoArco);
    if(!ehDigrafo){
        //adiciona um arco saindo de dest e indo at� orig em grafos n�o direcionados
        auxDest->addArco(orig, p, ehPonderadoArco);
    }
}

void Grafo::removeArco(int idOrig, int idDest)
{
    if(n==0)
    {
        cout << "Erro: grafo vazio" << endl;
        return;
    }

    No* auxOrig;
    for(auxOrig = primeiro; auxOrig!=NULL && auxOrig->getId()!=idOrig; auxOrig=auxOrig->getProxNo());

    if(auxOrig==NULL)
    {
        cout << "Erro: o grafo n�o possui esse n�" << endl;
        return;
    }

    auxOrig->removeArco(idDest);
    if(ehDigrafo)
        return;

    No* auxDest;
    for(auxDest = primeiro; auxDest!=NULL && auxDest->getId()!=idDest; auxDest=auxDest->getProxNo());

    if(auxDest==NULL)
    {
        cout << "Erro: o grafo n�o possui esse n�" << endl;
        return;
    }

    auxDest->removeArco(idOrig);
}

bool Grafo::ehAdjacente(int id1, int id2)
{
    No* no1;
    for(no1 = primeiro; no1!=NULL && no1->getId()!= id1; no1 = no1->getProxNo());
    if(no1 == NULL)
        return false;

    No* no2;
    for(no2 = primeiro; no2!=NULL && no2->getId()!= id2; no2 = no2->getProxNo());
    if(no2 == NULL)
        return false;

    if(!ehDigrafo)
        return no1->ehAdjacente(id2);

    return (no1->ehAdjacente(id2) || no2->ehAdjacente(id1));
}

bool Grafo::ehMultigrafo()
{
    if(n==0)
        return false; //se grafo � vazio, n�o � multigrafo

    No* aux;
    int* v = new int [n*2]; //vetor que contar� o n�mero de arcos incidentes em cada n�

    for(int i=0; i<n*2; i++)
        v[i] = 0;

    for(aux = primeiro; aux!=NULL; aux=aux->getProxNo())
        if(aux->temMultiarco(v, n*2))//verifica se o n� tem multiarco
            return true;

    return false;
}

void Grafo::auxFechoTransDir(No* no, list<int> &fTransDireto, list<int> &lVisitado)
{
    lVisitado.push_back(no->getId());
    fTransDireto.push_back(no->getId());

    list<int> adj;
    no->getAdjacentes(adj);

    if(adj.empty())
        return;

    list<int>::iterator it;

    for(it = adj.begin(); it!=adj.end(); ++it)
    {
        bool visitado = (find(lVisitado.begin(), lVisitado.end(), *it) != lVisitado.end());
        if(!visitado){
            fTransDireto.push_back(*it);
            lVisitado.push_back(*it);
            No* aux;
            for(aux = primeiro; aux!=NULL && aux->getId()!=*it; aux = aux->getProxNo());
            auxFechoTransDir(aux, fTransDireto, lVisitado);
        }
    }

    fTransDireto.sort();
    fTransDireto.unique();
}

void Grafo::fechoTransDir(int idNo, list <int> &fTransDireto)
{
    if(n==0)
        return;
    if(!ehDigrafo){
        cout << "Erro: grafo nao eh direcionado!" << endl;
        return;
    }

    No* aux;
    for(aux = primeiro; aux!=NULL && aux->getId()!= idNo; aux = aux->getProxNo());

    if(aux==NULL)
        return;

    list<int> visitado;
    auxFechoTransDir(aux, fTransDireto, visitado);

    list<int>::iterator it;
    for(it = fTransDireto.begin(); it!=fTransDireto.end(); ++it){
        cout << *it << ", ";
    }
    cout << endl;
    return;
}


Grafo* Grafo::auxFechoTransInd()
{
    Grafo* invertido = new Grafo(n, ehDigrafo, ehPonderadoNo, ehPonderadoArco);
    No* aux;
    for(aux = primeiro; aux!=NULL; aux = aux->getProxNo()){
        list<int> adjacentes;
        aux->getAdjacentes(adjacentes);
        list<int>::iterator i;
        for(i=adjacentes.begin(); i!=adjacentes.end(); ++i)
            invertido->addArco(*i, aux->getId(), 0);
    }
    return invertido;
}

void Grafo::fechoTransInd(int idNo, list <int> &fTransIndireto)
{
    Grafo* invertido = auxFechoTransInd();
    invertido->fechoTransDir(idNo, fTransIndireto);
    delete invertido;
}

void Grafo::vizAberto(int idNo, list <int> &lista){

    No* aux;

    for(aux = primeiro; aux!=NULL && aux->getId()!= idNo; aux = aux->getProxNo());

    if(aux==NULL)
        return;

    list<int> adj;
    aux->getAdjacentes(adj);
}

void Grafo::vizFechado(int idNo, list <int> &lista){

    No* aux;

    for(aux = primeiro; aux!=NULL && aux->getId()!= idNo; aux = aux->getProxNo());

    if(aux==NULL)
        return;

    list<int> adj;
    adj.push_back(idNo);
    aux->getAdjacentes(adj);
}

/*
bool Grafo::auxBipartido(int n_passo, No* no){
    bool coloriuCerto = false;
    Coloracao corPreenchida = Coloracao::SEMCOR;

    if(n_passo%2 == 0)
        corPreenchida = Coloracao::AZUL;
        else
            corPreenchida = Coloracao::VERDE;

    if(no->getCor() == Coloracao::SEMCOR){
        no->setCor(corPreenchida);

        for(list<int> x : no->getAdjacentes(x)){
            coloriuCerto = auxBipartido(n_passo+1, no->getProx());
            if(!coloriuCerto){
                break;
            }
        }
    } else{
        if(no->getCor() != corPreenchida){
            return false;
        }
    }
    return true;
}


bool Grafo::ehBipartido(No* no){
    while(no->getProxNo()!=nullptr)
        no->setCor(Coloracao::SEMCOR);

    bool ehBipart = auxBipartido(nNos,no);

    return ehBipart;
}
*/

int* Grafo::grauNo(int id){

    No* auxNo;
    int grau;
    for(auxNo = primeiro; auxNo != NULL; auxNo = auxNo -> getProxNo())
    {
        if(auxNo->getId() == id)
        break;
    }

    if(auxNo == NULL)
    {
        cout << "Erro! Id de no invalido"<<endl;
        return NULL;
    }

    grau = auxNo->grauSaida();

    if(ehDigrafo) // Se e digrafo imprime o grau de entrada e de saida
    {
        int *vet = new int[2];
        vet[0] = grau;
        vet[1] = auxNo -> grauEntrada(primeiro);
        return vet;
    }
    int *vet = new int[1];
    vet[0] = grau;
    return vet;
    //return auxNo -> grauSaida(); // Retorna o grau do no, e para digrafos retorna o grau de saida do no
}

bool Grafo::verificaK (int k){

    if (n == 0)
    {
        cout << "Grafo nulo" <<endl;
        return false;
    }

    for(No* aux = primeiro; aux != NULL; aux = aux -> getProxNo())
    {
        if(grauNo(aux->getId())[0] != k)
        {
            return false;
        }
    }
    return true;
}

int Grafo::ordemGrafo()
{
    return this->n;
}

bool Grafo::ehTrivial()
{
    return (this->n == 1);// && (primeiro->getAdjacentes(1) == NULL);
}

bool Grafo::ehNulo()
{
    if(n == 0)
        return true;

    No* atual = primeiro;
    while(atual != NULL){
        if(atual->temArestas())
            return false;

        atual = atual->getProxNo();
    }

    return true;
}

bool Grafo::ehCompleto()
{
    if (n == 0)
    {
        cout << "Grafo nulo" <<endl;
        return false;
    }
    else
        return verificaK(n-1);
}

void Grafo::seqGraus()
{
    if (n == 0)
    {
        cout << "Grafo nulo" <<endl;
        return;
    }

    int seq[n], t = 0, aux;

    for(No* auxNo = primeiro; auxNo!= NULL; auxNo = auxNo -> getProxNo())
    {
            seq[t] = grauNo(auxNo -> getId())[0];
            t++;
    }

    cout << "<";

    for(int i=0; i<n; i++)
    {
        for (int j = i+1; j<n; j++)
        {
            if(seq[j] < seq[i])
            {
                aux = seq[i];
                seq[i] = seq[j];
                seq[j] = aux;
            }
        }
        if(i != n-1)
            cout << seq[i] << ", ";
        else
            cout << seq[i] << ">" << endl;
    }
}

Grafo* Grafo::complementarGrafo()
{
    Grafo* complementar = new Grafo(this->n, this->ehDigrafo, this->ehPonderadoNo, this->ehPonderadoArco);

    for (No* origem = primeiro; origem != NULL; origem = origem->getProxNo())
    {
        if(ehDigrafo){
            for (No* destino = primeiro; destino != NULL; destino = destino->getProxNo())
            {
                if(origem->getId() == destino->getId())
                    continue;

                if(!origem->ehEntrada(destino->getId())){
                    complementar->addArco(origem->getId(), destino->getId(), 0);
                }
            }
        }
        else{
            for (No* destino = origem->getProxNo(); destino != NULL; destino = destino->getProxNo())
            {
                if(!origem->ehEntrada(destino->getId())){
                    complementar->addArco(origem->getId(), destino->getId(), 0);
                }
            }
        }

    }

    return complementar;
}

bool Grafo::ehEuleriano()
{
    if(ehDigrafo)
        return false;

    No* aux;
    for(aux = primeiro; aux!=NULL; aux = aux->getProxNo()){
        if(aux->grauSaida()%2!=0)
            return false;
    }
    return true;
}

void Grafo::imprimeGrafo()
{
    if(primeiro==NULL)
        return;
    else
    {
        No* aux;
        for(aux=primeiro; aux!=NULL; aux = aux->getProxNo()){
            cout << aux->getId();
            if(ehPonderadoNo)
                cout << " (" << aux->getPeso() << ")";
            cout << " - ";
            aux->imprimeNo(ehPonderadoArco);
            cout << endl;
        }
    }
}

void Grafo::subgrafoInd(){

}

void Grafo::arestaPonte(){

}

