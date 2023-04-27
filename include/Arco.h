#ifndef ARCO_H
#define ARCO_H


class Arco
{
    private:
        int idDestino; //armazena o id do nó destino
        float pesoArco; //armazena o peso do arco
        Arco *proxArco; //ponteiro para o próximo arco na lista de adjacência

    public:
        Arco(int dest, float p);
        ~Arco();
        Arco* getProxArc(); //get do próximo arco da lista de adjacência
        void setProxArc(Arco* arco); //set do próximo arco da lista de adjacência
        int getIdDest(); //get do id do nó destino do arco
        float getPesoArco(); //get do peso do arco
};

#endif // ARCO_H
