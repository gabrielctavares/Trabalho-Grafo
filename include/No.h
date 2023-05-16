#ifndef NO_H
#define NO_H

#include "Arco.h"
class No
{
    private:
        int id; //armazena o id do nó
        float peso; //armazena o peso do nó
        No *proxNo; //ponteiro para o próximo nó na lista de nós do grafo
        Arco *adjacentes; //ponteiro para o primeiro arco da lista de adjacência

    public:
        No(int n);
        No(int n, float p);
        ~No();
        void addArco(int idAdj, float p, bool ehPondArc);
        void removeArco(int idDest);//ainda não implementado
        No* getProxNo();
        void setProxNo(No* no);
        int getId();

        bool temMultiarco(int* v, int n); //usado pela função ehMultigrafo do TAD grafo

        int* getAdjacentes(int nNos); //retorna um vetor com os id's dos nós adjacentes ao nó atual
};

#endif // NO_H
