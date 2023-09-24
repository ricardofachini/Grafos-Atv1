#include "grafo.h"


int main() {
    Grafo *instance = new Grafo("cor3.net");
    std::cout << instance->peso(5, 6) << std::endl;
}