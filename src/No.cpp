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

void No::addArco(int idAdj, float p)
{
    if(adjacentes!=NULL){ //se o n� j� possui arcos
        Arco* aux;
        for(aux = adjacentes; aux->getProxArc()!=NULL; aux = aux->getProxArc());//percorre a lista de adjac�ncia at� encontrar o �ltimo arco
        Arco* novo = new Arco(idAdj, p);
        aux->setProxArc(novo); //cria o novo arco
    }
    else
        adjacentes = new Arco(idAdj, p);
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
