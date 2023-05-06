#include "Grafo.h"
#include <iostream>

using namespace std;

Grafo::Grafo()
{
    //constr�i grafo vazio
    n = 0;
    primeiro = NULL;
}

Grafo::Grafo(int num)
{
    //constr�i grafo com o n�mero de n�s informado
    n = 0;
    primeiro = NULL;
    for(int i=0; i<num; i++){
        addNo(i+1);
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

void Grafo::addNo(int id)
{
    //confere se o id j� est� sendo usado por algum n� do grafo
    for(No* aux = primeiro; aux!=NULL; aux = aux->getProxNo())
        if(id == aux->getId())
        {
            cout << "Erro: id repetido!" << endl;
            return;
        }

    No* no = new No(id); //inicializa um objeto do tipo n�
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
        aux->addArco(dest, p);
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

list <int> Grafo::fechoTransDir(int idNo)
{
    list <int> fTransDireto;
    if(n==0)
        return fTransDireto;


    No* aux;
    for(aux = primeiro; aux!=NULL && aux->getId()!= idNo; aux = aux->getProxNo());

    if(aux==NULL)
        return fTransDireto;

    Arco* adj;
    aux->getFechoTransDir(&fTransDireto);
    return fTransDireto;
}
