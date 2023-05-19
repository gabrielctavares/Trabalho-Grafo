#include "No.h"
#include <iostream>

using namespace std;

No::No(int n)
{
    //construtor de n� sem peso
    id = n;
    peso = 0;
    proxNo = NULL;
    adjacentes = NULL;
}

No::No(int n, float p)
{
    //construtor de n� sem peso
    id = n;
    peso = p;
    proxNo = NULL;
    adjacentes = NULL;
}

No::~No()
{
    //destrutor
    Arco* aux;
    while(adjacentes!=NULL)
    {
        aux = adjacentes;
        adjacentes = aux->getProxArc();
        delete aux;
        //deleta cada arco da lista de adjac�ncia do n�
    }
}

No* No::getProxNo()
{
    return proxNo;
}

void No::setProxNo(No* no)
{
    proxNo = no;
}

int No::getId()
{
    return id;
}

void No::addArco(int idAdj, float p, bool ehPondArc)
{
    Arco* novo;

    //cria um novo arco que � ponderado ou n�o de acordo com o tipo de grafo
    if(ehPondArc)
        novo = new Arco(idAdj, p);
    else
        novo = new Arco(idAdj);

    if(adjacentes!=NULL){ //se o n� j� possui arcos
        Arco* aux;
        for(aux = adjacentes; aux->getProxArc()!=NULL; aux = aux->getProxArc());//percorre a lista de adjac�ncia at� encontrar o �ltimo arco
        aux->setProxArc(novo);
    }
    else //se o n� n�o possui arcos
        adjacentes = novo;
}

void No::removeArco(int idDest)
{
    if(adjacentes==NULL)
        return;

    Arco* aux;
    Arco* anterior = NULL;
    for(aux = adjacentes; aux!=NULL && aux->getIdDest()!=idDest; aux=aux->getProxArc())
        anterior = aux;

    if(anterior==NULL)
        adjacentes = aux->getProxArc();
    else if(aux!=NULL)
        anterior->setProxArc(aux->getProxArc());
    else
    {
        cout << "Erro: o n� n�o possui esse arco" << endl;
        return;
    }

    delete aux;
}

bool No::temMultiarco(int* v, int n)
{
    if(adjacentes==NULL)//se n� n�o possui arcos, n�o tem multiarco
        return false;

    Arco* aux;
    bool resultado = false;

    for(aux = adjacentes; aux!=NULL; aux = aux->getProxArc()){
        int arc = aux->getIdDest();
        v[arc-1]++;//marca os n�s que s�o destinos dos arcos que saem do n� atual
    }

    for(int i=0; i<n; i++){
        if(v[i]>1)//se h� repeti��o de destino, h� multiarco
            resultado = true;
        v[i]=0;//zera o vetor para n�o afetar a verifica��o no pr�ximo n� do grafo
    }
    return resultado;
}

int* No::getAdjacentes(int nNos)
{
    if(adjacentes==NULL)
        return NULL;
    int* vet = new int [nNos-1];
    int i=0;

    for(Arco* aux=adjacentes; aux!=NULL && i<nNos-1; aux = aux->getProxArc(), i++)
        vet[i] = aux->getIdDest();

    for(; i<nNos-1; i++)
        vet[i] = -1;

    return vet;
}

void No::setCor(int x){

    cor = x;
}

int No::getCor(){

    return cor;
}
