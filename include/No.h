#ifndef NO_H
#define NO_H

#include "Arco.h"
class No
{
    private:
        int id; //armazena o id do n�
        float peso; //armazena o peso do n�
        No *proxNo; //ponteiro para o pr�ximo n� na lista de n�s do grafo
        Arco *adjacentes; //ponteiro para o primeiro arco da lista de adjac�ncia

    public:
        No(int n);
        ~No();
        void addArco(int idAdj, float p);
        void removeArco(int idDest);//ainda n�o implementado
        No* getProxNo();
        void setProxNo(No* no);
        int getId();

        bool temMultiarco(int* v, int n); //usado pela fun��o ehMultigrafo do TAD grafo

        Arco* getFechoTransDir(std::list<int> &fechoTransDir);
};

#endif // NO_H
