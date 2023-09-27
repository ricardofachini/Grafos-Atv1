#include "grafo.h"


int main() {
    Grafo *grafo1 = new Grafo("cor3.net");
    //std::cout << grafo1->peso(3, 4) << std::endl;
    // std::cout << grafo1->qtdVertices() << std::endl;
    // std::cout << grafo1->qtdArestas() << std::endl;
    // auto viz = grafo1->vizinhos(1);
    //grafo1->buscaLargura(4);
    grafo1->dijkstra(2);
    delete grafo1;
    return 0;
}