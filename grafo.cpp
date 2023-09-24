#include "grafo.h"
#include <fstream>
#include <algorithm>


// construtor, lê o arquivo
Grafo::Grafo(char *nome_arquivo)
{
    std::ifstream arquivo; // c++ stream para leitura de arquivo
    arquivo.open(nome_arquivo);
    std::string linha;

    // le o arquivo
    if (arquivo.is_open()) {
        bool le_vertice = false;
        bool le_aresta = false;
        while (arquivo) {
            std::getline (arquivo, linha); // carrega uma linha do arquivo na variável linha

            if (le_vertice == true) {
                // adiciona vertice ao grafo
                std::pair<int, int> vertice( linha.front()-48, linha.back()-48 );  // subtrai 48 porque characteres em c++ tem indice '0' para 48, '1' para 49, etc.
                vertices.push_back(vertice);
            }

            if (le_aresta == true) {
                // adiciona aresta ao grafo
                std::pair<int, int> aresta( linha.substr(0, 3).front()-48, linha.substr(0, 3).back()-48 );
                int peso = linha.back() - 48;
                arestas[aresta] = peso;
            }

            if (linha.find("*vertices") != std::string::npos) {  // verifica se a linha atual dita os vertices
                le_vertice = true;
            }

            if (linha.find("*edges") != std::string::npos) { // verifica se a linha atual dita as arestas
                le_vertice = false;
                le_aresta = true;
            }
        }
    }
}

// destrutor
Grafo::~Grafo() {}

int Grafo::peso(int u, int v)
{
    int peso = arestas[{u, v}];
    if (peso == 0)  {
        return INFINITO;
    } else {
        return peso;
    }
}

int Grafo::qtdVertices()
{
    return vertices.size();
}

int Grafo::qtdArestas()
{
    return arestas.size();
}

int Grafo::rotulo(int v)
{
    for (auto vertice: vertices) {
        if (vertice.first == v) {
            return vertice.second;
        }
    }
}

int Grafo::grau(int vertice)
{
    int grau = 0;
    for (const auto& aresta : arestas) {
        if (aresta.first.first == vertice || aresta.first.second == vertice) {
            grau++;
        }
    }
    return grau;
}

bool Grafo::haAresta(int u, int v)
{
    for (auto& aresta: arestas) {
        if (aresta.first.first == u && aresta.first.second == v || aresta.first.first == v && aresta.first.second == u) {
            return true;
        }
    }
    return false;
}
