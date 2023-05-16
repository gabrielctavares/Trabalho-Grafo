#include "Grafo.h"
#include <iostream>

using namespace std;

Grafo::Grafo(bool ehDigraf, bool ehPondNo, bool ehPondArco)
{
    //constr�i grafo vazio
    n = 0;
    primeiro = NULL;
    ehDigrafo = ehDigraf;
    ehPonderadoNo = ehPondNo;
    ehPonderadoArco = ehPondArco;
}

Grafo::Grafo(int num, bool ehDigraf, bool ehPondNo, bool ehPondArco)
{
    //constr�i grafo com o n�mero de n�s informado
    n = 0;
    primeiro = NULL;
    ehDigrafo = ehDigraf;
    ehPonderadoNo = ehPondNo;
    ehPonderadoArco = ehPondArco;

    if(!ehPondNo)
    {
        for(int i=0; i<num; i++){
            addNo(i+1, 0);
        }
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
    No* aux;
    for(aux = primeiro; aux->getId()!=orig && aux!=NULL; aux = aux->getProxNo());
    if(aux!=NULL)
        aux->addArco(dest, p, ehPonderadoArco);
    else
        cout << "Erro: n� n�o est� contido no grafo" << endl;
}

void Grafo::removeArco(int idNo, int idDest)
{
    if(n==0)
    {
        cout << "Erro: grafo vazio" << endl;
        return;
    }

    No* aux;
    for(aux = primeiro; aux!=NULL && aux->getId()!=idNo; aux=aux->getProxNo());

    if(aux!=NULL)
        aux->removeArco(idDest);
    else
        cout << "Erro: o grafo n�o possui esse n�" << endl;
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

/*
void Grafo::auxFechoTransDir(No* no, list<int> &fTransDireto)
{
    //n�o funciona se grafo n�o � GAD
    int* listaAdjacentes = no->getAdjacentes();

    if(listaAdjacentes==NULL)
        return;

    for(int i=0; listaAdjacentes[i]!=-1; i++){
        fTransDireto.push_back(listaAdjacentes[i]);
        No* aux;
        for(aux = primeiro; aux!=NULL && aux->getId()!=listaAdjacentes[i]; aux = aux->getProxNo());
        auxFechoTransDir(aux, list<int> &fTransDireto);
    }

    fTransDireto.sort();
    fTransDireto.unique();

    delete listaAdjacentes;
}

void Grafo::fechoTransDir(int idNo, list <int> &fTransDireto)
{
    if(n==0)
        return;
    if(ehMultigrafo())
        return;

    //precisa de fun��o que verifica se o grafo � GAD, pois esse algoritmo n�o funciona se h� ciclos

    No* aux;
    for(aux = primeiro; aux!=NULL && aux->getId()!= idNo; aux = aux->getProxNo());

    if(aux==NULL)
        return;

    auxFechoTransDir(aux, fTransDireto);
    return;
}*/
