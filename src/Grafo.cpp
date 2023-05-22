#include "Grafo.h"
#include <iostream>

using namespace std;

Grafo::Grafo(bool ehDigraf, bool ehPondNo, bool ehPondArco)
{
    //constr�i grafo vazio
    n = 0;
    primeiro = NULL;
    ehDigrafo = ehDigraf;
    ehPonderadoNo = ehPondNo;
    ehPonderadoArco = ehPondArco;
}

Grafo::Grafo(int num, bool ehDigraf, bool ehPondNo, bool ehPondArco)
{
    //constr�i grafo com o n�mero de n�s informado
    n = 0;
    primeiro = NULL;
    ehDigrafo = ehDigraf;
    ehPonderadoNo = ehPondNo;
    ehPonderadoArco = ehPondArco;

    if(!ehPondNo)
    {
        for(int i=0; i<num; i++){
            addNo(i+1, 0);
        }
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
}

void Grafo::addNo(int id, float peso)
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
        no = new No(id, peso); //inicializa um objeto do tipo n� para grafos ponderados no n�
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

    //verifica se o n� orig est� contido no grafo
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

/*
void Grafo::auxFechoTransDir(No* no, list<int> &fTransDireto)
{
    //n�o funciona se grafo n�o � GAD
    int* listaAdjacentes = no->getAdjacentes();

    if(listaAdjacentes==NULL)
        return;

    for(int i=0; listaAdjacentes[i]!=-1; i++){
        fTransDireto.push_back(listaAdjacentes[i]);
        No* aux;
        for(aux = primeiro; aux!=NULL && aux->getId()!=listaAdjacentes[i]; aux = aux->getProxNo());
        auxFechoTransDir(aux, list<int> &fTransDireto);
    }

    fTransDireto.sort();
    fTransDireto.unique();

    delete listaAdjacentes;
}

void Grafo::fechoTransDir(int idNo, list <int> &fTransDireto)
{
    if(n==0)
        return;
    if(ehMultigrafo())
        return;

    //precisa de fun��o que verifica se o grafo � GAD, pois esse algoritmo n�o funciona se h� ciclos

    No* aux;
    for(aux = primeiro; aux!=NULL && aux->getId()!= idNo; aux = aux->getProxNo());

    if(aux==NULL)
        return;

    auxFechoTransDir(aux, fTransDireto);
    return;
}*/


void Grafo::vizAberto(No* no,int nNos){

    int* vetAberta = new int[nNos-1];
    vetAberta = no->getAdjacentes(nNos);

    cout << vetAberta << endl;
}

void Grafo::vizFechado(No* no, int nNos){

    int* vetFechada = new int[nNos];
    vetFechada = no->getAdjacentes(nNos);
    int x = sizeof(vetFechada);
    vetFechada[x+1] = no->getId();

    cout << vetFechada << endl;
}

void Grafo::leituraArquivo(string database_name){
    
    this->arquivo_nome = database_name + ".txt";

    int* leitura_id = new int[100];
    int* leitura_adj = new int[100];
    int* leitura_peso =  new int[100];
    int x;

    FILE *arq;
    arq = fopen("arquivo_nome.txt","rt");

    if(arq == nullptr){
        cout << "problemas na abertura do arquivo" << endl;
    }

    fscanf(arq, "%d", &x);
    this-> n = x;

    while(!feof(arq)){
        for(int i=0;i<100;i++){
            fscanf(arq, "%d %d %d", &leitura_id[i], &leitura_adj[i], &leitura_peso[i]);
        }
    }
}

bool Grafo::auxBipartido(int nNos,No* no){

    no->setCor(1);
    int* adj = new int[nNos];
    
    while(no->getProxNo()!=nullptr){
        adj = no->getAdjacentes();
        for(int i=1;i<sizeof(adj);i++){
            if(no->getCor()==0)
                
        }
        if(no.getCor()==0){
            
        }else{
            for(int j=0;j<sizeof(adj);j++)
                adj[i].setCor(0);
        }
    }



}

bool Grafo::ehBipartido(int nNos, No* no){
    /* associamos cada cor a uma coloração
    SEM COR = -1;
    AZUL = 0;
    VERMELHO = 1;*/
    
    while(no->getProxNo()!=nullptr)
        no->setCor(-1);

    ehBipartido = auxBipartido(nNos,no);

    return ehBipartido;
}

int Grafo::grauNo(int id){

    No* auxNo;
    for(auxNo = primeiro; auxNo != NULL; auxNo = auxNo -> getProxNo())
    {
        if(auxNo->getId() == id)
        break;
    }
    
    if(auxNo == NULL)
    {
        cout << "Erro! Id de no invalido"<<endl;
        return -1;
    }
    
    if(ehDigrafo) // Se e digrafo imprime o grau de entrada e de saida
    {
        cout << "Grau de entrada do no " << auxNo -> getId() << ": " << auxNo -> grauEntrada()<< endl;
        cout << "Grau de saida do no ";
    }
    else
        cout << "Grau do no ";
        
    cout << auxNo -> getId() << ": " auxNo -> grauSaida() << endl;
    return auxNo -> grauSaida(); // Retorna o grau do no, e para digrafos retorna o grau de saida do no
}

bool Grafo::verificaK (int k){

    if (n == 0)
    {
        cout << "Grafo nulo" <<endl;
        return false;
    }

    for(No* aux = primeiro; aux != NULL; aux = aux -> getProxNo())
    {
        if(grauNo(aux->getId()) != k)
        {
            return false;
        }
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
            seq[t] = grauNo(auxNo -> getId());
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

