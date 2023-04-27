#ifndef ARCO_H
#define ARCO_H


class Arco
{
    private:
        int idDestino; //armazena o id do n� destino
        float pesoArco; //armazena o peso do arco
        Arco *proxArco; //ponteiro para o pr�ximo arco na lista de adjac�ncia

    public:
        Arco(int dest, float p);
        ~Arco();
        Arco* getProxArc(); //get do pr�ximo arco da lista de adjac�ncia
        void setProxArc(Arco* arco); //set do pr�ximo arco da lista de adjac�ncia
        int getIdDest(); //get do id do n� destino do arco
        float getPesoArco(); //get do peso do arco
};

#endif // ARCO_H
