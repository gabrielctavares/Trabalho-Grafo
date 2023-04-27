#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"

class Grafo
{
    private:
        No *primeiro; //ponteiro para o primeiro n� da lista de n�s do grafo
        int n; //armazena a quantidade de n�s que tem no grafo

    public:
        Grafo();
        Grafo(int num);
        ~Grafo();

        void addNo(int id); //adiciona n� com o id informado
        void removeNo(int id); //remove o n� com o id informado

        void addArco(int orig, int dest, float p);
        void removeArco(int idNo, int idArc);
        //aqui ainda precisa da fun��o de get e set da aresta

        bool ehAdjacente(No* x, No* y); // TODO: verificar se � isso mesmo

        void vizAberto(); //TODO: colocar os parametros/retorno da fun��o
        void vizFechado(); //TODO: colocar os parametros/retorno da fun��o
        int grauNo(No* no);
        void leituraArquivo(); //TODO: colocar os parametros/retorno da fun��o
        void kRegular();
        void ordemGrafo();
        bool ehTrivial();
        bool ehNulo();
        bool ehMultigrafo();
        bool ehCompleto();
        bool ehBipartido();
        void caminhoMinimo();
        void grauGrafo();
        void fechoTransDir();
        void fechoTransInd();
        void seqGraus();
        void subgrafoInd();
        void complementGrafo();
        void compFortConex();
        bool ehEuleriano();
        No* noArt();
        void arestaPonte();
        void infografo();
        void AGM(); //muda o nome se necess�rio
};

#endif // GRAFO_H
