#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"

class Grafo
{
    private:
        No *primeiro; //ponteiro para o primeiro n� da lista de n�s do grafo
        int n; //armazena a quantidade de n�s que tem no grafo

        void auxFechoTransDir(No* no, list<int> &fTransDireto); //fun��o auxiliar de fechoTransDir

    public:
        Grafo();
        Grafo(int num);
        ~Grafo();

        void addNo(int id); //adiciona n� com o id informado
        void removeNo(int id); //remove o n� com o id informado

        void addArco(int orig, int dest, float p); //adiciona um arco do n� com id orig indo no n� com id dest
        void removeArco(int idNo, int idDest); //remove um arco do n� com id idNo indo no n� com id idDest

        bool ehAdjacente(No* x, No* y); // TODO: verificar se � isso mesmo
        //Gabi: acho melhor usar o id do n�, pois a main n�o deve ter acesso a endere�o de n�
        //bool ehAdjacente(int id1, int id2);

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

        void fechoTransDir(int idNo, list <int> &fTransDireto); //preenche subconjunto de n�s que podem ser "alcan�ados" a partir do n� com id idNo (a ser implementado)
        void fechoTransInd(int idNo); //retorna conjunto de n�s que podem "alcan�ar" o n� com id idNo (a ser implementado)
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
