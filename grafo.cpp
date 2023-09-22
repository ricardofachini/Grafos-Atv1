#include "grafo.h"

// construtor, lê o arquivo
Grafo::Grafo(std::string arquivo)
{
    std::cout << arquivo << "\n";
    std::cout << INFINITO << std::endl;
}

// destrutor
Grafo::~Grafo() {};

int Grafo::peso(int u, int v)
{
    return INFINITO;
}