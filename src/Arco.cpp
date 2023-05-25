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

Arco::Arco(int dest)
{
    //construtor de arco não ponderado nas arestas
    idDestino = dest;
    pesoArco = 0;
    proxArco = NULL;
}

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
