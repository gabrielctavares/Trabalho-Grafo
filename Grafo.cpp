#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <bits/stdc++.h>
#include <iterator>
#include <list>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;
using namespace chrono;

Grafo::Grafo(bool ehDigraf, bool ehPondArco, bool ehPondNo)
{
    //constr�i grafo vazio
    n = 0;
    primeiro = NULL;
    ehDigrafo = ehDigraf;
    ehPonderadoNo = ehPondNo;
    ehPonderadoArco = ehPondArco;
}

Grafo::Grafo(int num, bool ehDigraf, bool ehPondArco, bool ehPondNo)
{
    //constr�i grafo com o n�mero de n�s informado
    n = 0;
    primeiro = NULL;
    ehDigrafo = ehDigraf;
    ehPonderadoNo = ehPondNo;
    ehPonderadoArco = ehPondArco;
    for(int i=0; i<num; i++){
        addNo(i+1);
    }
}
Grafo::Grafo(int num, bool ehDigraf, bool ehPondArco, bool ehPondNo, string caminho_saida)
{
    //constr�i grafo com o n�mero de n�s informado
    n = 0;
    primeiro = NULL;
    ehDigrafo = ehDigraf;
    ehPonderadoNo = ehPondNo;
    ehPonderadoArco = ehPondArco;
    for(int i=0; i<num; i++){
        addNo(i+1);
    }
    arquivo_saida = caminho_saida;
}

Grafo::~Grafo()
{
    cout << "Destruindo grafo" << endl;
    No* aux;
    while(primeiro!=NULL){
        aux = primeiro;
        primeiro = aux->getProxNo();
        delete aux;
        //deleta cada n� da lista de n�s do grafo
    }
    primeiro = NULL;
}

void Grafo::addNo(int id)
{
    //confere se o id j� est� sendo usado por algum n� do grafo
    for(No* aux = primeiro; aux!=NULL; aux = aux->getProxNo())
        if(id == aux->getId())
        {
            cout << "Erro: id repetido!" << endl;
            return;
        }

    No* no;
    if(ehPonderadoNo)
        no = new No(id, (id%200)+1); //inicializa um objeto do tipo n� para grafos ponderados no n�
    else
        no = new No(id); //inicializa um objeto do tipo n� para grafos n�o ponderados no n�
    if(n==0)//se o grafo � vazio, o n� adicionado ser� o primeiro n� da lista
    {
        primeiro = no;
    }
    else
    {
        No* aux;
        for(aux = primeiro; aux->getProxNo()!=NULL; aux = aux->getProxNo());//encontra o �ltimo n� na lista de n�s do grafo
        aux->setProxNo(no);//adiciona o n� no final da lista
    }
    //acrescenta 1 na quantidade de n�s do grafo
    n++;
}

void Grafo::removeNo(int id)
{
    if(n==0)
        cout<<"ERRO: lista vazia!" << endl;
    else
    {
        No* aux = primeiro;
        for(No* aux2=NULL; aux!=NULL; aux2 = aux ,aux = aux->getProxNo())
        {
            if(id==aux->getId())
            {
                aux2->setProxNo(aux->getProxNo());
                delete aux;
                n--;
                return;
            }
        }
    }
}

void Grafo::addArco(int orig, int dest, float p)
{
    No* auxOrig;
    No* auxDest;

    for(auxOrig = primeiro; auxOrig->getId()!=orig && auxOrig!=NULL; auxOrig = auxOrig->getProxNo());

    if(auxOrig==NULL){
        cout << "Erro: no nao esta contido no grafo" << endl;
        return;
    }

    //verifica se o n� dest est� contido no grafo
    for(auxDest = primeiro; auxDest->getId()!=dest && auxDest!=NULL; auxDest = auxDest->getProxNo());

    if(auxDest==NULL){
        cout << "Erro: no nao esta contido no grafo" << endl;
        return;
    }

    auxOrig->addArco(dest, p, ehPonderadoArco);
    if(!ehDigrafo){
        //adiciona um arco saindo de dest e indo at� orig em grafos n�o direcionados
        auxDest->addArco(orig, p, ehPonderadoArco);
    }
}

void Grafo::removeArco(int idOrig, int idDest)
{
    if(n==0)
    {
        cout << "Erro: grafo vazio" << endl;
        return;
    }

    No* auxOrig;
    for(auxOrig = primeiro; auxOrig!=NULL && auxOrig->getId()!=idOrig; auxOrig=auxOrig->getProxNo());

    if(auxOrig==NULL)
    {
        cout << "Erro: o grafo nao possui esse no" << endl;
        return;
    }

    auxOrig->removeArco(idDest);
    if(ehDigrafo)
        return;

    No* auxDest;
    for(auxDest = primeiro; auxDest!=NULL && auxDest->getId()!=idDest; auxDest=auxDest->getProxNo());

    if(auxDest==NULL)
    {
        cout << "Erro: o grafo nao possui esse no" << endl;
        return;
    }

    auxDest->removeArco(idOrig);
}

bool Grafo::ehAdjacente(int id1, int id2)
{
    No* no1;
    for(no1 = primeiro; no1!=NULL && no1->getId()!= id1; no1 = no1->getProxNo());
    if(no1 == NULL)
        return false;

    No* no2;
    for(no2 = primeiro; no2!=NULL && no2->getId()!= id2; no2 = no2->getProxNo());
    if(no2 == NULL)
        return false;

    if(!ehDigrafo)
        return no1->ehAdjacente(id2);

    return (no1->ehAdjacente(id2) || no2->ehAdjacente(id1));
}

bool Grafo::ehMultigrafo()
{
    if(n==0)
        return false; //se grafo � vazio, n�o � multigrafo

    No* aux;
    int* v = new int [n*2]; //vetor que contar� o n�mero de arcos incidentes em cada n�

    for(int i=0; i<n*2; i++)
        v[i] = 0;

    for(aux = primeiro; aux!=NULL; aux=aux->getProxNo())
        if(aux->temMultiarco(v, n*2))//verifica se o n� tem multiarco
            return true;

    return false;
}

void Grafo::auxFechoTransDir(No* no, list<int> &fTransDireto, list<int> &lVisitado)
{
    lVisitado.push_back(no->getId());
    fTransDireto.push_back(no->getId());

    list<int> adj;
    no->getAdjacentes(adj);

    if(adj.empty())
        return;

    list<int>::iterator it;

    for(it = adj.begin(); it!=adj.end(); ++it)
    {
        bool visitado = (find(lVisitado.begin(), lVisitado.end(), *it) != lVisitado.end());
        if(!visitado){
            fTransDireto.push_back(*it);
            lVisitado.push_back(*it);
            No* aux;
            for(aux = primeiro; aux!=NULL && aux->getId()!=*it; aux = aux->getProxNo());
            auxFechoTransDir(aux, fTransDireto, lVisitado);
        }
    }

    fTransDireto.sort();
    fTransDireto.unique();
}

void Grafo::fechoTransDir(int idNo, list <int> &fTransDireto)
{
    if(n==0)
        return;
    if(!ehDigrafo){
        cout << "Erro: grafo nao eh direcionado!" << endl;
        return;
    }

    No* aux;
    for(aux = primeiro; aux!=NULL && aux->getId()!= idNo; aux = aux->getProxNo());

    if(aux==NULL)
        return;

    list<int> visitado;
    auxFechoTransDir(aux, fTransDireto, visitado);

    list<int>::iterator it;
    for(it = fTransDireto.begin(); it!=fTransDireto.end(); ++it){
        cout << *it << ", ";
    }
    cout << endl;
    return;
}


Grafo* Grafo::auxFechoTransInd()
{
    Grafo* invertido = new Grafo(n, ehDigrafo, ehPonderadoNo, ehPonderadoArco);
    No* aux;
    for(aux = primeiro; aux!=NULL; aux = aux->getProxNo()){
        list<int> adjacentes;
        aux->getAdjacentes(adjacentes);
        list<int>::iterator i;
        for(i=adjacentes.begin(); i!=adjacentes.end(); ++i)
            invertido->addArco(*i, aux->getId(), 0);
    }
    return invertido;
}

void Grafo::fechoTransInd(int idNo, list <int> &fTransIndireto)
{
    Grafo* invertido = auxFechoTransInd();
    invertido->fechoTransDir(idNo, fTransIndireto);
    delete invertido;
}

void Grafo::vizAberto(int idNo, list <int> &lista){

    No* aux;

    for(aux = primeiro; aux!=NULL && aux->getId()!= idNo; aux = aux->getProxNo());

    if(aux==NULL)
        return;

    list<int> adj;
    aux->getAdjacentes(adj);
}

void Grafo::vizFechado(int idNo, list <int> &lista){

    No* aux;

    for(aux = primeiro; aux!=NULL && aux->getId()!= idNo; aux = aux->getProxNo());

    if(aux==NULL)
        return;

    list<int> adj;
    adj.push_back(idNo);
    aux->getAdjacentes(adj);
}


bool Grafo::auxBipartido(int n_passo, No* no){
    bool coloriuCerto = false;
    int corPreenchida = -1;
    Arco* adj;

    if(n_passo%2 == 0)
        corPreenchida = 0;
        else
            corPreenchida = 1;

    if(no->getCor() == -1){
        no->setCor(corPreenchida);

        adj = no->getAdjacentes();

        while(adj != NULL){
            coloriuCerto = auxBipartido(n_passo+1, GetNo(adj->getIdDest())->getProxNo());
            if(!coloriuCerto){
                break;
            }
            adj = adj->getProxArc();
        }
    } else if(no->getCor() != corPreenchida){
            return false;
    }
    return true;
}

bool Grafo::ehBipartido(){

    //SEM COR = -1,    //vértice não visitado
    //AZUL = 0,
    //VERDE = 1,
    //AMARELO = 2,
    //VERMELHO = 3

    No* no = primeiro;

    while(no->getProxNo() != NULL){
        no->setCor(-1);
        no = no->getProxNo();
    }

    return auxBipartido(0,primeiro);
}


int* Grafo::grauNo(int id){

    No* auxNo;
    int grau;
    for(auxNo = primeiro; auxNo != NULL; auxNo = auxNo -> getProxNo())
    {
        if(auxNo->getId() == id)
        break;
    }

    if(auxNo == NULL)
    {
        cout << "Erro! Id de no invalido"<<endl;
        return NULL;
    }

    grau = auxNo->grauSaida();

    if(ehDigrafo) // Se e digrafo imprime o grau de entrada e de saida
    {
        int *vet = new int[2];
        vet[0] = grau;
        vet[1] = auxNo -> grauEntrada(primeiro);
        return vet;
    }
    int *vet = new int[1];
    vet[0] = grau;
    return vet;
    //return auxNo -> grauSaida(); // Retorna o grau do no, e para digrafos retorna o grau de saida do no
}

bool Grafo::verificaK (int k){

    if (n == 0)
    {
        cout << "Grafo nulo" <<endl;
        return false;
    }

    for(No* aux = primeiro; aux != NULL; aux = aux -> getProxNo())
    {
        if(grauNo(aux->getId())[0] != k)
        {
            return false;
        }
    }
    return true;
}

int Grafo::ordemGrafo()
{
    return this->n;
}

bool Grafo::ehTrivial()
{
    return (this->n == 1);// && (primeiro->getAdjacentes(1) == NULL);
}

bool Grafo::ehNulo()
{
    if(n == 0)
        return true;

    No* atual = primeiro;
    while(atual != NULL){
        if(atual->temArestas())
            return false;

        atual = atual->getProxNo();
    }

    return true;
}

bool Grafo::ehCompleto()
{
    if (n == 0)
    {
        cout << "Grafo nulo" <<endl;
        return false;
    }
    else
        return verificaK(n-1);
}

void Grafo::seqGraus()
{
    if (n == 0)
    {
        cout << "Grafo nulo" <<endl;
        return;
    }

    int seq[n], t = 0, aux;

    for(No* auxNo = primeiro; auxNo!= NULL; auxNo = auxNo -> getProxNo())
    {
            seq[t] = grauNo(auxNo -> getId())[0];
            t++;
    }

    cout << "<";

    for(int i=0; i<n; i++)
    {
        for (int j = i+1; j<n; j++)
        {
            if(seq[j] < seq[i])
            {
                aux = seq[i];
                seq[i] = seq[j];
                seq[j] = aux;
            }
        }
        if(i != n-1)
            cout << seq[i] << ", ";
        else
            cout << seq[i] << ">" << endl;
    }
}

int Grafo::grauGrafo()
{
    int maior = 0;
    for(No* auxNo = primeiro; auxNo!= NULL; auxNo = auxNo -> getProxNo())
    {
        if(grauNo(auxNo -> getId())[0] > maior)
            maior = grauNo(auxNo -> getId())[0];
    }
    return maior;
}
Grafo* Grafo::complementarGrafo()
{
    Grafo* complementar = new Grafo(this->n, this->ehDigrafo, this->ehPonderadoArco, this->ehPonderadoNo);

    for (No* origem = primeiro; origem != NULL; origem = origem->getProxNo())
    {
        if(ehDigrafo){
            for (No* destino = primeiro; destino != NULL; destino = destino->getProxNo())
            {
                if(origem->getId() == destino->getId())
                    continue;

                if(!origem->ehEntrada(destino->getId())){
                    complementar->addArco(origem->getId(), destino->getId(), 0);
                }
            }
        }
        else{
            for (No* destino = origem->getProxNo(); destino != NULL; destino = destino->getProxNo())
            {
                if(!origem->ehEntrada(destino->getId())){
                    complementar->addArco(origem->getId(), destino->getId(), 0);
                }
            }
        }

    }

    return complementar;
}

bool Grafo::ehEuleriano()
{
    if(ehDigrafo)
        return false;

    No* aux;
    for(aux = primeiro; aux!=NULL; aux = aux->getProxNo()){
        if(aux->grauSaida()%2!=0)
            return false;
    }
    return true;
}



vector<vector<No*>> Grafo::compFortConex() {
    vector<vector<No*>> result;
    //if(!this->ehDigrafo)
    //    return result;

    int *low = new int[n];
    bool *stackMember = new bool[n];
    stack<No*> *st = new stack<No*>();

    for (int i = 0; i < n; i++) {
        low[i] = -1;
        stackMember[i] = false;
    }

    for(No* aux = primeiro; aux!=NULL; aux = aux->getProxNo()){
        if (aux->getComponente() == -1)
            auxCompFortConex(aux, low, st, stackMember, result);
    }

    delete[] low;
    delete[] stackMember;
    delete st;

    return result;
}

void Grafo::auxCompFortConex(No* u, int low[], stack<No*> *st, bool stackMember[], vector<vector<No*>>& result) {
    int idxOrig = u->getId() - 1;
    static int component = 0; // estático para não ficar criando como 0 dnv, considera a criação anterior e soma na linha de baixo
    low[idxOrig] = ++component;
    u->setComponente(low[idxOrig]);

    st->push(u);
    stackMember[idxOrig] = true;


    // para cada adjacencia de u
    for(Arco * aux = u->getAdjacentes(); aux != NULL; aux = aux->getProxArc()){
        int idxDest = aux->getIdDest() - 1;
        No* NoDest = GetNo(aux->getIdDest());

        if (NoDest->getComponente() == -1) {
            auxCompFortConex(NoDest, low, st, stackMember, result);
            low[idxOrig] = min(low[idxOrig], low[idxDest]);
        }
        else if (stackMember[idxDest] == true)
            low[idxOrig] = min(low[idxOrig], NoDest->getComponente());
    }


    if (low[idxOrig] == u->getComponente()) {
        No* aux;
        vector<No*> component;
        while (st->top() != u) {
            aux = st->top();
            component.push_back(aux);
            stackMember[aux->getId() - 1] = false;
            st->pop();
        }
        aux = st->top();
        component.push_back(aux);
        stackMember[aux->getId() - 1] = false;
        st->pop();
        result.push_back(component);
    }
}


Grafo* Grafo::transpostoGrafo(){
    if(!this->ehDigrafo)
        return NULL;

    Grafo*  transposto = new Grafo(this->n, this->ehDigrafo, this->ehPonderadoNo, this->ehPonderadoArco);

    for (No* no = primeiro; no != NULL; no = no->getProxNo())
    {
        for(Arco* arco = no->getAdjacentes(); arco != NULL; arco = arco->getProxArc())
        {
            transposto->addArco(arco->getIdDest(), no->getId(), 0);
        }
    }
    return transposto;
}
void Grafo::imprimeGrafo()
{
    if(primeiro==NULL)
        return;
    else
    {
        No* aux;
        for(aux=primeiro; aux!=NULL; aux = aux->getProxNo()){
            cout << aux->getId();
            if(ehPonderadoNo)
                cout << " (" << aux->getPeso() << ")";
            cout << " - ";
            aux->imprimeNo(ehPonderadoArco);
            cout << endl;
        }
    }
}


bool Grafo::ehConexo(){
   int x;
   x = compCon();

   if(x == 1){
       return true;
   }else{
       return false;
   }
}


No *Grafo::GetNo(int id)
{
    if((id > n + 1) || id < 0)
        return NULL;

    for(No* aux = primeiro; aux != NULL; aux = aux->getProxNo()){
        if(aux->getId() == id)
            return aux;
    }

    return NULL;
}

Arco* Grafo::arestaPonte(){
    No* n = primeiro;
    Arco* aux; //armazena temporariamente um arco para adicionar na lista de pontes
    Arco* pontes; //retorna a lista de arcos pontes encontrados
    Arco* adj; //lista de arcos para obter os adjacentes do no
    float p; //peso da aresta

    while(n->getProxNo() != NULL){

        adj = n->getAdjacentes();

        while(adj != NULL){

            p = adj->getPesoArco();
            n->removeArco(adj->getIdDest());;

            if(ehConexo()){
                No* x = GetNo(adj->getIdDest());

                if(ehPonderadoArco){
                    aux = new Arco(n->getId(),x->getId(),p);
                    pontes->setProxArc(aux);
                }else{
                    aux = new Arco(n->getId(),x->getId());
                    pontes->setProxArc(aux);
                }
            }

            n->addArco(GetNo(adj->getIdDest())->getId(), p, true);
            adj = adj->getProxArc();
        }

        n = n->getProxNo();
    }

    return pontes;
}

int Grafo::compCon ()
{
    int visit[n] = {};
    int comp = 0;
    int i; //indica sobre qual nó estamos: i=0 é o primeiro no da lista i=n-1, o ultimo

    for(i=0; i<n; i++)
    {
        if(visit[i]==0)
        {
            comp++;
            prof(visit,i,comp);
        }
    }
    return comp;
}

void Grafo::prof(int visitados[], int no, int marca)
{
    visitados[no] = marca;
    int i = 0;
    No* auxNo;
    for(auxNo = primeiro; auxNo!=NULL; auxNo = auxNo -> getProxNo())
    {
        if(i == no)
            break;
        i++;
    }
    int j = 0;
    for(No* auxNo2 = primeiro; auxNo2 != NULL; auxNo2 = auxNo2 -> getProxNo())
    {
        if(auxNo -> ehAdjacente(auxNo2->getId()))
        {
            if(visitados[j] == 0)
            {
                prof(visitados,j,marca);
            }
        }
        j++;
    }
}

int Grafo::compConSemNo(int id) //calcula quantas componentes conexas o grafo teria sem o no passado
{
    int visit[n-1] = {};
    int comp = 0;
    int i; //indica sobre qual nó estamos: i=0 é o primeiro no da lista i=n-2, o ultimo

    for(i=0; i<n-1; i++)
    {
        if(visit[i]==0)
        {
            comp++;
            profSemNo(visit,i,comp,id);
        }
    }
    return comp;
}

void Grafo::profSemNo(int visitados[], int no, int marca, int id)
{
    visitados[no] = marca;
    int i = 0;
    No* auxNo;
    for(auxNo = primeiro; auxNo!=NULL; auxNo = auxNo -> getProxNo())
    {
        if(auxNo -> getId() == id)
            continue;
        if(i == no)
            break;
        i++;
    }

    int j = 0;

    for(No* auxNo2 = primeiro; auxNo2 != NULL; auxNo2 = auxNo2->getProxNo())
    {
        if (auxNo2 -> getId() == id)
            continue;
        if(auxNo -> ehAdjacente(auxNo2->getId()))
            if(visitados[j] == 0)
                profSemNo(visitados,j,marca,id);
        j++;
    }
}

bool Grafo::ehNoArt (int id)
{
    if(compCon() < compConSemNo(id))
    {
        return true;
    }
    return false;
}

void Grafo::imprimeIdNoArt()
{
    int i = 0; // vai indicar quantos nos de articulacao tem
    for(No* auxNo = primeiro; auxNo != NULL; auxNo = auxNo -> getProxNo())
    {
        if(ehNoArt(auxNo -> getId()))
        {
            if(i == 0)
            {
                cout << "Id dos nos de articulacao: ";
                cout << auxNo -> getId();
            }
            else
                cout << ", " << auxNo -> getId();
            i++;
        }
    }
    if(i == 0)
        cout << "O grafo nao possui nos de articulacao";
    cout << "."<<endl;

}

void Grafo::ordenaCandidatos(int* candidatos, int* pesos, int* graus)
{
    for(int i =0; i<n-1; i++){
        for(int j=n-1; j>i; j--){
            if(candidatos[j]!=-1 && pesos[j]/(float)graus[j]<pesos[j-1]/(float)graus[j-1]){
                int auxI = candidatos[j];
                int auxP = pesos[j];
                int auxG = graus[j];
                candidatos[j] = candidatos[j-1];
                pesos[j] = pesos[j-1];
                graus[j] = graus[j-1];
                candidatos[j-1] = auxI;
                pesos[j-1] = auxP;
                graus[j-1] = auxG;
            }
        }
    }
}

void Grafo::auxCobertVertPond(int* orig, int* dest){
    No* aux;
    for(int i=0; i<n*(n-1)/2; i++){
        orig[i] = -1;
        dest[i] = -1;
    }
    int i=0;
    for(aux = primeiro; aux!=NULL; aux = aux->getProxNo()){
        for(Arco* arcos = aux->getAdjacentes(); arcos!=NULL; arcos = arcos->getProxArc()){
            if(arcos->getIdOrigem()>arcos->getIdDest()){
                orig[i] = arcos->getIdOrigem();
                dest[i] = arcos->getIdDest();
                i++;
            }
        }
    }
}

void Grafo::cobertVertPondG(list<int> &solucao)
{
    if(!ehPonderadoNo){
        cout << "Erro: Grafo deve ser ponderado" << endl;
        return;
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();
    double time = 0;

    No* no;
    solucao.clear();
    //lista de nós candidatos
    int* candidatos = new int[n];
    int* pesos = new int[n];
    int* graus = new int[n];
    No* aux = primeiro;
    for(int i=0; aux!=NULL; aux = aux->getProxNo()){
        candidatos[i] = aux->getId();
        pesos[i] = aux->getPeso();
        graus[i] = aux->grauSaida();
        i++;
    }
    ordenaCandidatos(candidatos, pesos, graus);

    //lista de arcos não cobertos
    int* orig = new int[n*(n-1)/2];
    int* dest = new int[n*(n-1)/2];
    auxCobertVertPond(orig, dest);
    int custo = 0;

    while(candidatos[0]!=-1){
        //pega sempre o melhor nó
        int id = candidatos[0];

        bool ehSolucao = false;

        for(int i=0; i<n*(n-1)/2; i++){
            if(orig[i]!=-1 && (orig[i]==id || dest[i]==id)){
                //arco é tirado da lista de arcos não cobertos
                orig[i] = -1;
                dest[i] = -1;
                //nó é marcado como parte da solução
                ehSolucao = true;
            }
        }
        if(ehSolucao){
            //adiciona o nó à solução
            solucao.push_back(id);
            custo = custo+pesos[0];
        }
        candidatos[0] = -1;
        pesos[0] = -1;
        graus[0] = -1;
        for(int i=0; candidatos[i+1]!=-1  && i<n; i++){
            candidatos[i]=candidatos[i+1];
            pesos[i] = pesos[i+1];
            graus[i] = graus[i+1];
            candidatos[i+1] = -1;
            pesos[i+1] = -1;
            graus[i+1] = -1;
        }
        //ordenaCandidatos(candidatos, pesos, graus);
    }

    delete [] candidatos;
    delete [] pesos;
    delete [] graus;
    delete [] orig;
    delete [] dest;

    high_resolution_clock::time_point stop = high_resolution_clock::now();
    time = duration_cast<duration<double>>(stop-start).count();

    ofstream arq;
    arq.open(arquivo_saida, ios::app);
    if(arq.is_open()){
        arq << "=====Algoritmo Guloso=====" << endl;
        arq << "--------Info-------" << endl;
        arq << "Custo da solucao: " << custo << endl;
        arq << "Tamanho da solucao final: " << solucao.size() << endl;
        arq << "CPU time: " << time << endl << endl;
        arq.close();
    }
    else{
        cout << "Erro: nao foi possivel abrir arquivo de saida" << endl;
        cout << "=====Algoritmo Guloso=====" << endl;
        cout << "--------Info-------" << endl;
        cout << "Custo da solucao: " << custo << endl;
        cout << "Tamanho da solucao final: " << solucao.size() << endl << endl;
    }
    cout << "CPU time: " << time << endl << endl;
}

int Grafo::getRandIndex(float alpha, int tam){
    if((int)(alpha*tam) != 0)
        return rand()%(int)(alpha*tam);
    else
        return 0;
}

void Grafo::cobertVertPondGR(list<int> &best, int nIteracoes, float alpha)
{
    if(!ehPonderadoNo){
        cout << "Erro: Grafo deve ser ponderado" << endl;
        return;
    }

    unsigned seed = time(0);
    srand(seed);

    high_resolution_clock::time_point start = high_resolution_clock::now();
    double time = 0;

    list<int> solucao;
    int cont = 0;
    int custoBest = 0;
    int soma = 0;

    No* aux = primeiro;

    int* candidatosFixo = new int[n];
    int* pesosFixo = new int[n];
    int* grausFixo = new int[n];

    for(int i=0; aux!=NULL; aux = aux->getProxNo()){
        candidatosFixo[i] = aux->getId();
        pesosFixo[i] = aux->getPeso();
        grausFixo[i] = aux->grauSaida();
        i++;
    }

    int* candidatos = new int[n];
    int* pesos = new int[n];
    int* graus = new int[n];

    int* origFixo = new int[n*(n-1)/2];
    int* destFixo = new int[n*(n-1)/2];
    auxCobertVertPond(origFixo, destFixo);

    int* orig = new int[n*(n-1)/2];
    int* dest = new int[n*(n-1)/2];

    while(cont<nIteracoes){
        solucao.clear();
        //lista de nós candidatos
        for(int i=0; i<n; i++){
            candidatos[i] = candidatosFixo[i];
            pesos[i] = pesosFixo[i];
            graus[i] = grausFixo[i];
        }
        ordenaCandidatos(candidatos, pesos, graus);

        //lista de arcos não cobertos
        for(int i=0; i<n*(n-1)/2; i++){
            orig[i] = origFixo[i];
            dest[i] = destFixo[i];
        }
        int custo = 0;

        int tam = n;
        while(candidatos[0]!=-1){
            //pega um nó aleatório dentro da faixa determinada pelo valor de alpha e o remove da lista
            int index = getRandIndex(alpha, tam);
            No* no = GetNo(candidatos[index]);
            int id = candidatos[index];

            bool ehSolucao = false;

            for(int i=0; i<n*(n-1)/2; i++){
                if(orig[i]!=-1 && (orig[i]==id || dest[i]==id)){
                    //arco é tirado da lista de arcos não cobertos
                    orig[i] = -1;
                    dest[i] = -1;
                    //nó é marcado como parte da solução
                    ehSolucao = true;
                }
            }
            if(ehSolucao && id!=-1){
                //adiciona o nó à solução
                solucao.push_back(id);
                custo = custo+no->getPeso();
            }
            candidatos[index] = -1;
            pesos[index] = -1;
            graus[index] = -1;
            tam--;
            for(int i=index; candidatos[i+1]!=-1  && i<n; i++){
                candidatos[i]=candidatos[i+1];
                pesos[i] = pesos[i+1];
                graus[i] = graus[i+1];
                candidatos[i+1] = -1;
                pesos[i+1] = -1;
                graus[i+1] = -1;
            }
            //ordenaCandidatos(candidatos, pesos, graus);
        }

        if(custoBest==0 || custo<custoBest){
            //se a solução encontrada for melhor que melhor encontrada até então, ela passa a ser a melhor
            best.assign(solucao.begin(), solucao.end());
            custoBest = custo;
        }
        soma = soma+custo;
        cont++;
    }

    delete [] candidatos;
    delete [] pesos;
    delete [] graus;
    delete [] candidatosFixo;
    delete [] pesosFixo;
    delete [] grausFixo;
    delete [] origFixo;
    delete [] destFixo;
    delete [] orig;
    delete [] dest;

    high_resolution_clock::time_point stop = high_resolution_clock::now();
    time = duration_cast<duration<double>>(stop-start).count();

    ofstream arq;
    arq.open(arquivo_saida, ios::app);
    if(arq.is_open()){
        arq << "=====Algoritmo Guloso Randomizado=====" << endl;
        arq << "--------Info-------" << endl;
        arq << "Alpha: " << alpha << endl;
        arq << "Custo da melhor solucao: " << custoBest << endl;
        arq << "Media do custo das solucoes: " << soma/(float)cont << endl;
        arq << "Tamanho da solucao final: " << best.size() << endl;
        arq << "CPU time: " << time << endl << endl;
        arq.close();
    }
    else{
        cout << "Erro: nao foi possivel abrir arquivo de saida" << endl;
        cout << "=====Algoritmo Guloso Randomizado=====" << endl;
        cout << "--------Info-------" << endl;
        cout << "Alpha: " << alpha << endl;
        cout << "Custo da melhor solucao: " << custoBest << endl;
        cout << "Media do custo das solucoes: " << soma/(float)cont << endl;
        cout << "Tamanho da solucao final: " << best.size() << endl;
    }
    cout << "CPU time: " << time << endl << endl;
}

void Grafo::recalculaAlphas(float* alpha, float* p, double* medias, int custoBest, int tam){

    float* q = new float[tam];
    float soma = 0;

    if(custoBest==0)
        return;

    for(int i=0; i<tam; i++){
        q[i] = custoBest/medias[i];
        soma = soma + q[i];
    }

    float rest = 1;
    int cont = 0;
    for(int i=0; i<tam; i++){
        p[i] = q[i]/soma;
    }
    delete [] q;
}

float Grafo::escolheAlpha(float* alphas, float* p, int tam){
    int soma = 0;
    int aleatorio;
    float alpha = alphas[0];

    for(int i=0; i<5; i++){
        aleatorio = rand();
    }

    for(int i =0; i<tam; i++)
    {
        soma += (int)(p[i]*10000);
        if(aleatorio%10000 < soma){
            alpha = alphas[i];
            break;
        }
    }
    return alpha;
}

void Grafo::atualizaMedias(double* medias, int* nVezes, int custo, int* custoBestAlpha, int indexAlpha){
    float soma = (medias[indexAlpha]*nVezes[indexAlpha])+custo;
    nVezes[indexAlpha] = nVezes[indexAlpha] + 1;
    medias[indexAlpha] = soma/nVezes[indexAlpha];
    if(custo < custoBestAlpha[indexAlpha] || custoBestAlpha[indexAlpha]==0)
        custoBestAlpha[indexAlpha] = custo;
}

void Grafo::cobertVertPondGRR(list<int> &best, int nIteracoes, float* alphas, int nAlphas)
{
    if(!ehPonderadoNo){
        cout << "Erro: Grafo deve ser ponderado" << endl;
        return;
    }

    unsigned seed = time(0);
    srand(seed);

    high_resolution_clock::time_point start = high_resolution_clock::now();
    double time = 0;

    list<int> solucao;
    int cont = 0;
    int custoBest = 0;
    double* medias = new double[nAlphas];
    float* probabilidades = new float[nAlphas];
    int* nVezes = new int[nAlphas];
    int* custoBestAlpha =  new int[nAlphas];

    float bestAlpha = 0;

    for(int i=0; i<nAlphas; i++){
        probabilidades[i] = 1/(float)nAlphas;
        medias[i] = 0;
        nVezes[i] = 0;
        custoBestAlpha[i] = 0;
    }

    No* aux = primeiro;

    int* candidatosFixo = new int[n];
    int* pesosFixo = new int[n];
    int* grausFixo = new int[n];

    for(int i=0; aux!=NULL; aux = aux->getProxNo()){
        candidatosFixo[i] = aux->getId();
        pesosFixo[i] = aux->getPeso();
        grausFixo[i] = aux->grauSaida();
        i++;
    }

    int* candidatos = new int[n];
    int* pesos = new int[n];
    int* graus = new int[n];

    int* origFixo = new int[n*(n-1)/2];
    int* destFixo = new int[n*(n-1)/2];
    auxCobertVertPond(origFixo, destFixo);

    int* orig = new int[n*(n-1)/2];
    int* dest = new int[n*(n-1)/2];

    while(cont<nIteracoes){
        solucao.clear();

        for(int i=0; i<n; i++){
            candidatos[i] = candidatosFixo[i];
            pesos[i] = pesosFixo[i];
            graus[i] = grausFixo[i];
        }
        ordenaCandidatos(candidatos, pesos, graus);

        float alpha;

        if(cont<nAlphas){
            //garante que todos os alphas sejam usados pelo menos uma vez
            alpha = alphas[cont];
        }
        else{
            //recalcula as probabilidades caso tenha completado um dado número de iterações
            if((cont+1)%(int)(nIteracoes*0.1)==0)
                recalculaAlphas(alphas, probabilidades, medias, custoBest, nAlphas);
            alpha = escolheAlpha(alphas, probabilidades, nAlphas);
        }

        //lista de arcos não cobertos
        for(int i=0; i<n*(n-1)/2; i++){
            orig[i] = origFixo[i];
            dest[i] = destFixo[i];
        }
        int custo = 0;

        int tam = n;
        while(candidatos[0]!=-1){
            //pega um nó aleatório dentro da faixa determinada pelo valor de alpha e o remove da lista
            int index = getRandIndex(alpha, tam);
            No* no = GetNo(candidatos[index]);
            int id = candidatos[index];

            bool ehSolucao = false;

            for(int i=0; i<n*(n-1)/2; i++){
                if(orig[i]!=-1 && (orig[i]==id || dest[i]==id)){
                    //arco é tirado da lista de arcos não cobertos
                    orig[i] = -1;
                    dest[i] = -1;
                    //nó é marcado como parte da solução
                    ehSolucao = true;
                }
            }
            if(ehSolucao && id!=-1){
                //adiciona o nó à solução
                solucao.push_back(id);
                custo = custo+no->getPeso();
            }
            candidatos[index] = -1;
            pesos[index] = -1;
            graus[index] = -1;
            tam--;
            for(int i=index; candidatos[i+1]!=-1 && i<n; i++){
                candidatos[i]=candidatos[i+1];
                pesos[i] = pesos[i+1];
                graus[i] = graus[i+1];
                candidatos[i+1] = -1;
                pesos[i+1] = -1;
                graus[i+1] = -1;
            }
            //ordenaCandidatos(candidatos, pesos, graus);
        }
        if(custoBest==0 || custo<custoBest){
            //se a solução encontrada for melhor que melhor encontrada até então, ela passa a ser a melhor
            best.assign(solucao.begin(), solucao.end());
            custoBest = custo;
            bestAlpha = alpha;
        }

        for(int i = 0; i<nAlphas; i++){
            //atualiza a media de custos do alpha atual
            if(alpha == alphas[i]){
                atualizaMedias(medias, nVezes, custo, custoBestAlpha, i);
                break;
            }
        }
        cont++;
    }

    delete [] candidatos;
    delete [] pesos;
    delete [] graus;
    delete [] candidatosFixo;
    delete [] pesosFixo;
    delete [] grausFixo;
    delete [] origFixo;
    delete [] destFixo;
    delete [] orig;
    delete [] dest;

    high_resolution_clock::time_point stop = high_resolution_clock::now();
    time = duration_cast<duration<double>>(stop-start).count();

    ofstream arq;
    arq.open(arquivo_saida, ios::app);
    if(arq.is_open()){
        arq << "=====Algoritmo Guloso Randomizado Reativo=====" << endl;
        arq << "--------Info-------" << endl << endl;
        for(int i=0; i<nAlphas; i++){
            arq << "Alpha[" << i << "] = " << alphas[i] << endl;
            arq << "Melhor solucao do alpha = " << custoBestAlpha[i] << endl;
            arq << "Media = " << medias[i] << endl;
            arq << "Numero de aparicoes = " << nVezes[i] << endl;
            arq << "Probabilidade de aparicao = " << probabilidades[i] << endl << endl;
        }

        arq << "------Melhor solucao------" << endl;
        arq << "Custo da melhor solucao: " << custoBest << endl;
        arq << "Alpha da melhor solucao: " << bestAlpha << endl;
        arq << "Tamanho da solucao final: " << best.size() << endl;
        arq << "CPU time: " << time << endl << endl;
        arq.close();
    }
    else{
        cout << "Erro: nao foi possivel abrir arquivo de saida" << endl;
        cout << "=====Algoritmo Guloso Randomizado Reativo=====" << endl;
        cout << "--------Info-------" << endl << endl;
        for(int i=0; i<nAlphas; i++){
            cout << "Alpha[" << i << "] = " << alphas[i] << endl;
            cout << "Melhor solucao do alpha = " << custoBestAlpha[i] << endl;
            cout << "Media = " << medias[i] << endl;
            cout << "Numero de aparicoes = " << nVezes[i] << endl;
            cout << "Probabilidade de aparicao = " << probabilidades[i] << endl << endl;
        }

        cout << "------Melhor solucao------" << endl;
        cout << "Custo da melhor solucao: " << custoBest << endl;
        cout << "Alpha da melhor solucao: " << bestAlpha << endl;
        cout << "Tamanho da solucao final: " << best.size() << endl << endl;
    }
    cout << "CPU time: " << time << endl << endl;
}

/*void Grafo::auxSubGrafo(Arco* adj, int x, int* id_n)
{
    if(id_n[i]==aux->getId()){
        adj = aux->getAdjacentes();
        n->No(id_n[i]);
        i++;
            while(adj != NULL){
              if(GetNo(adj->getIdDest())->getId() == id_n[i_aux]){
                  n->addArco(adj->getIdDest())->getId(), , true);
              }
              adj = adj->getProxArc();
            }
            aux = aux->getProxNo();

    }
}

No* Grafo::subgrafoInd(int *id_n)
{
    int i = 0, i_aux = 1;

    No* n;
    No* aux = primeiro;
    Arco* adj;

    while(aux != NULL){
        if(id_n[i]==aux->getId()){
            adj = aux->getAdjacentes();
            n->No(id_n[i]);
            i++;
            while(adj != NULL){
              if(GetNo(adj->getIdDest())->getId() == id_n[i_aux]){
                  n->addArco(adj->getIdDest())->getId(), , true);
              }
              adj = adj->getProxArc();
            }
            aux = aux->getProxNo();
            i_aux++;
        }
    }

    return n;

}*/
