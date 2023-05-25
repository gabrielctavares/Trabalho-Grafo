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
        int cor;

    public:
        No(int n);
        No(int n, float p);
        ~No();
        void addArco(int idAdj, float p, bool ehPondArc);
        void removeArco(int idDest);//ainda n�o implementado
        No* getProxNo();
        void setProxNo(No* no);
        int getId();
        void setCor(int x);
        int getCor(No* n);
        int grauSaida();
        int grauEntrada(No* primeiro);


        bool ehEntrada (int id); // usado pela função grauEntrada

        bool temMultiarco(int* v, int n); //usado pela fun��o ehMultigrafo do TAD grafo

        int* getAdjacentes(int nNos); //retorna um vetor com os id's dos n�s adjacentes ao n� atual
};

#endif // NO_H
