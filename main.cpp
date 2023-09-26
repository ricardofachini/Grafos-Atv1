#include "grafo.h"


int main() {
    Grafo *grafo1 = new Grafo("cor3.net");
    std::cout << grafo1->peso(1, 3) << std::endl;
    std::cout << grafo1->qtdVertices() << std::endl;
    std::cout << grafo1->qtdArestas() << std::endl;
    auto viz = grafo1->vizinhos(4);
    delete grafo1;
    return 0;
}