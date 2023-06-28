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
        cout << "Erro: n� n�o est� contido no grafo" << endl;
        return;
    }

    //verifica se o n� dest est� contido no grafo
    for(auxDest = primeiro; auxDest->getId()!=dest && auxDest!=NULL; auxDest = auxDest->getProxNo());

    if(auxDest==NULL){
        cout << "Erro: n� n�o est� contido no grafo" << endl;
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
        cout << "Erro: o grafo n�o possui esse n�" << endl;
        return;
    }

    auxOrig->removeArco(idDest);
    if(ehDigrafo)
        return;

    No* auxDest;
    for(auxDest = primeiro; auxDest!=NULL && auxDest->getId()!=idDest; auxDest=auxDest->getProxNo());

    if(auxDest==NULL)
    {
        cout << "Erro: o grafo n�o possui esse n�" << endl;
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

void Grafo::auxConexo(No* n){
    int x;

    if(n->getCor() != 0){
        n->setCor(0);
    }

    Arco* adj = n->getAdjacentes();
    while(adj != NULL){
        x = adj->getIdDest();
        if(GetNo(x)->getCor() == -1){
            auxConexo(GetNo(x));
        }
        adj = adj->getProxArc();
    }
}

bool Grafo::ehConexo(){

    No* no = primeiro;

    while(no->getProxNo()!= NULL){
        no->setCor(-1);
        no = no->getProxNo();
    }

    auxConexo(primeiro);

    while(no->getProxNo()!= NULL){
        if(no->getCor() == -1)
            return false;

        no = no->getProxNo();
    }
    return true;
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

void Grafo::ordenaCandidatos(list<int> &candidatos)
{
    for(No* aux=primeiro; aux!=NULL; aux = aux->getProxNo())
        candidatos.push_back(aux->getId());
    list<int>::iterator i;
    list<int>::iterator j;
    for(i=candidatos.begin(); i!=--candidatos.end(); ++i){
        for(j=--candidatos.end(); j!=i; ){
            list<int>::iterator it = j;
            No* aux1 = GetNo(*j);
            No* aux2 = GetNo(*(--j));
            float heur1 = aux1->getPeso()/aux1->grauSaida();
            float heur2 = aux2->getPeso()/aux2->grauSaida();
            if(heur1<heur2){
                swap(*(--it), *it);
            }
        }
    }
}

Arco* Grafo::auxCobertVertPond(){
    No* aux;
    Arco* arco_aux;
    Arco* lista_arcos = NULL;
    for(aux = primeiro; aux!=NULL; aux = aux->getProxNo()){
        for(Arco* arcos = aux->getAdjacentes(); arcos!=NULL; arcos = arcos->getProxArc()){
            if(arcos->getIdOrigem()>arcos->getIdDest()){
                arco_aux = new Arco(arcos->getIdOrigem(), arcos->getIdDest(), 0);
                arco_aux->setProxArc(lista_arcos);
                lista_arcos = arco_aux;
            }
        }
    }
    return lista_arcos;
}

void Grafo::cobertVertPondG(list<int> &solucao)
{
    No* no;
    solucao.clear();
    //lista de nós candidatos
    list<int> candidatos;
    ordenaCandidatos(candidatos);

    Arco* arcosNCobertos;
    arcosNCobertos = auxCobertVertPond();
    int custo = 0;


    while(!candidatos.empty() && arcosNCobertos!=NULL){
        //pega o melhor nó
        no = GetNo(*(candidatos.begin()));
        candidatos.pop_front();

        bool ehSolucao = false;
        Arco* arco;
        Arco* aux;
        arco = arcosNCobertos;
        for(aux = NULL; arco!=NULL;){
            if(arco->getIdOrigem()==no->getId() || arco->getIdDest()==no->getId()){
                if(aux==NULL){
                    arcosNCobertos = arco->getProxArc();
                    delete arco;
                    arco = arcosNCobertos;
                }
                else{
                    aux->setProxArc(arco->getProxArc());
                    delete arco;
                    arco = aux;
                }
                ehSolucao = true;
            }
            else{
                aux = arco;
                arco = arco->getProxArc();
            }
        }
        if(ehSolucao){
            solucao.push_back(no->getId());
            custo = custo+no->getPeso();
        }
    }
    cout << "Custo da solução: " << custo << endl;
}

int Grafo::getRandIndex(float alpha, int tam){
    unsigned seed = time(0);
    srand(seed);
    if((int)(alpha*tam) != 0)
        return rand()%(int)(alpha*tam);
    else
        return 0;
}

void Grafo::cobertVertPondGR(list<int> &best, int nIteracoes, float alpha)
{
    list<int> solucao;
    int cont = 0;
    int custoBest = 0;

    while(cont<nIteracoes){
        No* no;
        solucao.clear();
        //lista de nós candidatos
        list<int> candidatos;
        ordenaCandidatos(candidatos);

        Arco* arcosNCobertos;
        arcosNCobertos = auxCobertVertPond();
        int custo = 0;


        while(!candidatos.empty() && arcosNCobertos!=NULL){

            int index = getRandIndex(alpha, candidatos.size());
            list<int>::iterator i = candidatos.begin();
            advance(i, index);
            no = GetNo(*i);
            candidatos.remove(*i);

            bool ehSolucao = false;
            Arco* arco;
            Arco* aux;
            arco = arcosNCobertos;
            for(aux = NULL; arco!=NULL;){
                if(arco->getIdOrigem()==no->getId() || arco->getIdDest()==no->getId()){
                    if(aux==NULL){
                        arcosNCobertos = arco->getProxArc();
                        delete arco;
                        arco = arcosNCobertos;
                    }
                    else{
                        aux->setProxArc(arco->getProxArc());
                        delete arco;
                        arco = aux;
                    }
                    ehSolucao = true;
                }
                else{
                    aux = arco;
                    arco = arco->getProxArc();
                }
            }
            if(ehSolucao){
                solucao.push_back(no->getId());
                custo = custo+no->getPeso();
            }
        }

        if(custoBest==0 || custo<custoBest){
            best.assign(solucao.begin(), solucao.end());
            custoBest = custo;
        }

        cout << "Custo da solução da iteração " << cont <<": " << custo << endl;
        cont++;
    }
    cout << "Custo da melhor solução: " << custoBest << endl;
}

void Grafo::recalculaAlphas(float* alpha, float* p, float* medias, int custoBest, int tam){

    float* q = new float[tam];
    float soma = 0;

    for(int i=0; i<tam; i++){
        q[i] = custoBest/medias[i];
        soma+=q[i];
    }

    for(int i=0; i<tam; i++){
        p[i] = q[i]/soma;
    }
    delete [] q;
}

float Grafo::escolheAlpha(float* alphas, float* p, int tam){
    float* vet = new float[50*tam];
    for(int i=0; i<tam; i++)
        for(int j=i*p[i]*50*tam; j<(i+1)*p[i]*50*tam && j<50*tam; j++)
            vet[j] = alphas[i];

    int index = getRandIndex(1, tam*50);
    float alpha = vet[index];
    cout << alpha << endl;
    delete [] vet;
    return alpha;
}

void Grafo::atualizaMedias(float* medias, int* nVezes, int custo, int indexAlpha){
    float soma = (medias[indexAlpha]*nVezes[indexAlpha])+custo;
    nVezes[indexAlpha] = nVezes[indexAlpha] + 1;
    medias[indexAlpha] = soma/nVezes[indexAlpha];

}

void Grafo::cobertVertPondGRR(list<int> &best, int nIteracoes, float* alphas, int nAlphas)
{
    list<int> solucao;
    int cont = 0;
    int custoBest = 0;
    float* medias = new float[nAlphas];
    float* probabilidades = new float[nAlphas];
    int* nVezes = new int[nAlphas];

    float bestAlpha = 0;


    for(int i=0; i<nAlphas; i++){
        probabilidades[i] = 1/nAlphas;
        medias[i] = 0;
        nVezes[i] = 0;
    }

    while(cont<nIteracoes){
        if((cont+1)%(int)(nIteracoes*0.1)==0)
            recalculaAlphas(alphas, probabilidades, medias, custoBest, nAlphas);

        solucao.clear();

        list<int> candidatos;
        ordenaCandidatos(candidatos);

        float alpha = escolheAlpha(alphas, probabilidades, nAlphas);
        Arco* arcosNCobertos;
        arcosNCobertos = auxCobertVertPond();
        int custo = 0;

        while(!candidatos.empty() && arcosNCobertos!=NULL){

            int index = getRandIndex(alpha, candidatos.size());
            list<int>::iterator i = candidatos.begin();
            advance(i, index);
            No* no = GetNo(*i);
            candidatos.remove(*i);

            bool ehSolucao = false;
            Arco* arco;
            Arco* aux;
            arco = arcosNCobertos;
            for(aux = NULL; arco!=NULL;){
                if(arco->getIdOrigem()==no->getId() || arco->getIdDest()==no->getId()){
                    if(aux==NULL){
                        arcosNCobertos = arco->getProxArc();
                        delete arco;
                        arco = arcosNCobertos;
                    }
                    else{
                        aux->setProxArc(arco->getProxArc());
                        delete arco;
                        arco = aux;
                    }
                    ehSolucao = true;
                }
                else{
                    aux = arco;
                    arco = arco->getProxArc();
                }
            }
        }
        if(custoBest==0 || custo<custoBest){
            best.assign(solucao.begin(), solucao.end());
            custoBest = custo;
            bestAlpha = alpha;
        }

        for(int i = 0; i<nAlphas; i++){
            if(alpha == alphas[i]){
                atualizaMedias(medias, nVezes, custo, i);
                break;
            }
        }

        cout << "Custo da solução da iteração " << cont <<": " << custo << endl;
        cout << "Alpha da iteração " << cont <<": " << alpha << endl;
        cont++;
    }
    cout << "Custo da melhor solução: " << custoBest << endl;
    cout << "Melhor alpha: " << bestAlpha << endl;
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
