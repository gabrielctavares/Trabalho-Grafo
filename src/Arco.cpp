#include "Arco.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <bits/stdc++.h>
#include <iterator>
#include <list>

using namespace std;

Arco::Arco(int origemId, int destinoId)
{
    //construtor de arco n�o ponderado nas arestas
    idOrigem = origemId;
    idDestino = destinoId;
    pesoArco = 0;
    proxArco = NULL;
}

Arco::Arco(int origemId, int destinoId, float peso)
{
    //construtor
    idOrigem = origemId;
    idDestino = destinoId;
    pesoArco = peso;
    proxArco = NULL;
}

Arco::~Arco()
{
    //destrutor
    //n�o tem muito o que fazer aqui
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

int Arco::getIdOrigem()
{
    return idOrigem;
}

float Arco::getPesoArco()
{
    return pesoArco;
}
