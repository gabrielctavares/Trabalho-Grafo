#include "Arco.h"
#include <iostream>

using namespace std;

Arco::Arco(int dest, float p)
{
    //construtor
    idDestino = dest;
    pesoArco = p;
    proxArco = NULL;
}

Arco::~Arco()
{
    //destrutor
    //não tem muito o que fazer aqui
}

Arco* Arco::getProxArc()
{
    return proxArco;
}

void Arco::setProxArc(Arco* arco)
{
    proxArco = arco;
}

int Arco::getIdDest()
{
    return idDestino;
}

float Arco::getPesoArco()
{
    return pesoArco;
}
