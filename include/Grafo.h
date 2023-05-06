#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"

class Grafo
{
    private:
        No *primeiro; //ponteiro para o primeiro nó da lista de nós do grafo
        int n; //armazena a quantidade de nós que tem no grafo

        void auxFechoTransDir(No* no, list<int> &fTransDireto); //função auxiliar de fechoTransDir

    public:
        Grafo();
        Grafo(int num);
        ~Grafo();

        void addNo(int id); //adiciona nó com o id informado
        void removeNo(int id); //remove o nó com o id informado

        void addArco(int orig, int dest, float p); //adiciona um arco do nó com id orig indo no nó com id dest
        void removeArco(int idNo, int idDest); //remove um arco do nó com id idNo indo no nó com id idDest

        bool ehAdjacente(No* x, No* y); // TODO: verificar se é isso mesmo
        //Gabi: acho melhor usar o id do nó, pois a main não deve ter acesso a endereço de nó
        //bool ehAdjacente(int id1, int id2);

        void vizAberto(); //TODO: colocar os parametros/retorno da função
        void vizFechado(); //TODO: colocar os parametros/retorno da função
        int grauNo(No* no);
        void leituraArquivo(); //TODO: colocar os parametros/retorno da função
        void kRegular();
        void ordemGrafo();
        bool ehTrivial();
        bool ehNulo();
        bool ehMultigrafo();
        bool ehCompleto();
        bool ehBipartido();
        void caminhoMinimo();
        void grauGrafo();

        void fechoTransDir(int idNo, list <int> &fTransDireto); //preenche subconjunto de nós que podem ser "alcançados" a partir do nó com id idNo (a ser implementado)
        void fechoTransInd(int idNo); //retorna conjunto de nós que podem "alcançar" o nó com id idNo (a ser implementado)
        void seqGraus();
        void subgrafoInd();
        void complementGrafo();
        void compFortConex();
        bool ehEuleriano();
        No* noArt();
        void arestaPonte();
        void infografo();
        void AGM(); //muda o nome se necessário
};

#endif // GRAFO_H
