#ifndef GRAFO_H
#define GRAFO_H

#import <No.h>
#import <Aresta.h>
class Grafo
{
    public:
        Grafo();
        ~Grafo();

        void addNo(No* no);
        void removeNo(No* no);
        //aqui ainda precisa da fun��o de get e set do n�
        void addArco(Aresta* aresta);
        void removeArco(Aresta* aresta);
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
    private:
};

#endif // GRAFO_H
