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
        ~No();
        void addArco(int idAdj, float p);
        void removeArco(int idDest);//ainda não implementado
        No* getProxNo();
        void setProxNo(No* no);
        int getId();

        bool temMultiarco(int* v, int n); //usado pela função ehMultigrafo do TAD grafo

        Arco* getFechoTransDir(std::list<int> &fechoTransDir);
};

#endif // NO_H
