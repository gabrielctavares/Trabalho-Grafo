#ifndef NO_H
#define NO_H

#include <list>
#include <Aresta.h>
class No
{
    public:
        No();
        ~No();
        int peso;
        std::list<Aresta> arestas;

    private:
};

#endif // NO_H
