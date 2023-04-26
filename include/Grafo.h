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
        //aqui ainda precisa da função de get e set do nó
        void addArco(Aresta* aresta);
        void removeArco(Aresta* aresta);
        //aqui ainda precisa da função de get e set da aresta

        bool ehAdjacente(No* x, No* y); // TODO: verificar se é isso mesmo

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
        void AGM(); //muda o nome se necessário
    private:
};

#endif // GRAFO_H
