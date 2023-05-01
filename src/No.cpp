#include "No.h"
#include <iostream>

using namespace std;

No::No(int n)
{
    //construtor de nó sem peso
    id = n;
    peso = 0;
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
        //deleta cada arco da lista de adjacência do nó
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

void No::addArco(int idAdj, float p)
{
    if(adjacentes!=NULL){ //se o nó já possui arcos
        Arco* aux;
        for(aux = adjacentes; aux->getProxArc()!=NULL; aux = aux->getProxArc());//percorre a lista de adjacência até encontrar o último arco
        Arco* novo = new Arco(idAdj, p);
        aux->setProxArc(novo); //cria o novo arco
    }
    else
        adjacentes = new Arco(idAdj, p);
}

bool No::temMultiarco(int* v, int n)
{
    if(adjacentes==NULL)//se nó não possui arcos, não tem multiarco
        return false;

    Arco* aux;
    bool resultado = false;

    for(aux = adjacentes; aux!=NULL; aux = aux->getProxArc()){
        int arc = aux->getIdDest();
        v[arc-1]++;//marca os nós que são destinos dos arcos que saem do nó atual
    }

    for(int i=0; i<n; i++){
        if(v[i]>1)//se há repetição de destino, há multiarco
            resultado = true;
        v[i]=0;//zera o vetor para não afetar a verificação no próximo nó do grafo
    }
    return resultado;
}
