#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"
#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

class Grafo
{
    private:
        No *primeiro; //ponteiro para o primeiro n� da lista de n�s do grafo
        int n; //armazena a quantidade de n�s que tem no grafo
        bool ehDigrafo;
        bool ehPonderadoNo;
        bool ehPonderadoArco;

        void auxFechoTransDir(No* no, list<int> &fTransDireto, list<int> &lVisitado); //fun��o auxiliar de fechoTransDir
        Grafo* auxFechoTransInd(); //funcao auxiliar de fechoTransInd
        bool auxBipartido(int n_passo,No* no); //Lana: implementado (auxiliar do bipartido)
        void auxConexo(No *n);
        No* GetNo(int id);
    public:
        Grafo(bool ehDigraf, bool ehPondArco, bool ehPondNo);
        Grafo(int num, bool ehDigrafo, bool ehPondArco, bool ehPondNo);
        ~Grafo();

        void addNo(int id, float peso); //adiciona n� com o id informado
        void removeNo(int id); //remove o n� com o id informado

        void addArco(int orig, int dest, float p); //adiciona um arco do n� com id orig indo no n� com id dest
        void removeArco(int idOrig, int idDest); //remove um arco do n� com id idNo indo no n� com id idDest

        bool ehAdjacente(int id1, int id2);

        void vizAberto(int idNo, list <int> &lista); //implementado
        void vizFechado(int idNo, list <int> &lista); //implementado
        int* grauNo(int id); // Davi: implementado
        bool verificaK(int k); // Davi: implementado
        int ordemGrafo(); // Gabriel: implementado;
        bool ehTrivial(); // Gabriel: implementado;
        bool ehNulo(); // Gabriel: implementado;
        bool ehMultigrafo(); //Gabi: implementado
        bool ehCompleto(); // Davi: implementado
        bool ehBipartido(No* no); //Lana: implementado
        void caminhoMinimo();
        void grauGrafo();
        int compCon (); //calcula quantas componentes conexas possui o grafo
        void prof(int visitados[], int no, int marca); //percorrendo por profundidade, auxilia a calcular as componentes conexas
        int compConSemNo(int id); // calcula quantas comp con sem o no passado
        void profSemNo(int visitados[], int no, int marca, int id);
        bool ehNoArt (int id); // verifica se determinado no e de articulacao
        void imprimeIdNoArt(); //imprime o id de todos os nos de articulacao

        void fechoTransDir(int idNo, list <int> &fTransDireto); //n�s que podem ser "alcan�ados" a partir do n� com id idNo(incompleto)
        void fechoTransInd(int idNo, list <int> &fTransIndireto); //retorna conjunto de n�s que podem "alcan�ar" o n� com id idNo (a ser implementado)
        void seqGraus(); // Davi: implementado
        void subgrafoInd();
        Grafo* complementarGrafo();
        vector<vector<No*>> compFortConex();
        void auxCompFortConex(No *u, int low[], stack<No *> *st, bool stackMember[], vector<vector<No *>> &result);
        Grafo *transpostoGrafo();
        bool ehEuleriano();
        No* getVertice(Arco x, No* n);
        bool ehConexo(No *no);
        void arestaPonte();
        void infografo();
        void AGM(); //muda o nome se necess�rio

        void imprimeGrafo();
};

#endif // GRAFO_H
