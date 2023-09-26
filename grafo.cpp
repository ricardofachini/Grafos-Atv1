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

            if (linha.find("*vertices") != std::string::npos) {  // verifica se a linha atual dita os vertices
                le_vertice = true;
                continue;
            }

            if (linha.find("*edges") != std::string::npos) { // verifica se a linha atual dita as arestas
                le_vertice = false;
                le_aresta = true;
                continue;
            }
            if (linha == "") {
                break;
            }

            if (le_vertice == true) {
                // adiciona vertice ao grafo
                std::pair<int, int> vertice( linha.front()-48, linha.back()-48 );  // subtrai 48 porque characteres em c++ tem indice '0' para 48, '1' para 49, etc.
                vertices.push_back(vertice);
            }

            if (le_aresta == true) {
                // adiciona aresta ao grafo
                //std::pair<int, int> aresta( linha.substr(0, 3).front()-48, linha.substr(0, 3).back()-48 );
                Aresta *aresta = new Aresta();
                aresta->vertice1 = linha.substr(0, 3).front()-48;
                aresta->vertice2 = linha.substr(0, 3).back()-48;
                aresta->peso = linha.back() - 48;
                arestas.push_back(aresta);
            }
        }
    }
}

// destrutor
Grafo::~Grafo() {
    // desaloca memória das arestas
    for (auto& aresta: arestas) {
        delete aresta;
    }
}

int Grafo::peso(int u, int v)
{
    int peso = 0;
    for (const Aresta *aresta: arestas)
        if ((aresta->vertice1 == u && aresta->vertice2 == v) ||
                (aresta->vertice1 == v && aresta->vertice2 == u)) {
                    peso = aresta->peso;
                    break;
        }
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
    for (auto& vertice: vertices) {
        if (vertice.first == v) {
            return vertice.second;
        }
    }
    return 0;
}

int Grafo::grau(int vertice)
{
    int grau = 0;
    for (const auto& aresta : arestas) {
        if (aresta->vertice1 == vertice || aresta->vertice2 == vertice) {
            grau++;
        }
    }
    return grau;
}

bool Grafo::haAresta(int u, int v)
{
    for (auto& aresta: arestas) {
        if ((aresta->vertice1 == u && aresta->vertice2 == v) || (aresta->vertice1 == v && aresta->vertice2 == u)) {
            return true;
        }
    }
    return false;
}

// retorna um vetor de indices dos vertices vizinhos ao v
std::vector<int> Grafo::vizinhos(int v)
{
    std::vector<int> vizinhos;
    for (auto& aresta: arestas) {
        if (aresta->vertice1 == v) {
            vizinhos.push_back(aresta->vertice2);
        }
        if (aresta->vertice2 == v) {
            vizinhos.push_back(aresta->vertice1);
        }
    }
    return vizinhos;
}

void Grafo::buscaLargura(int s)
{
    std::deque<int> *fila;
    std::vector<int> *visitados;
    int nivel = 0;
    visitados->push_back(s);
    fila->push_back(s);
    std::cout << nivel << ": " << s << "\n";
    while (fila->size() != 0) {
        nivel++;
        int v = fila->front();
        fila->pop_front();
        auto vizinhos_de_v = vizinhos(v);
        for (auto& vizinho: vizinhos_de_v) {
            if ( std::find(vizinhos_de_v.begin(), vizinhos_de_v.end(), vizinho) != vizinhos_de_v.end() ) {
                visitados->push_back(vizinho);
            } else {
                visitados->push_back(vizinho);
                fila->push_back(vizinho);
            }
        }
        std::cout << nivel << ": " << v << "\n";
    }

}

// std::tuple<bool, std::vector<int>> Grafo::hierholzer()
// {
//     for (auto& aresta: arestas) {
//         aresta = false; // corrigir
//     }
//     int v = vertices(2);
//     bool r;
//     std::vector<int> ciclo;
//     std::tuple<bool, std::vector<int>> subciclo = buscaSubciclo();
//     r = std::get<0>(subciclo);
//     ciclo = std::get<1>(subciclo);
//     if (r == false) {
//         return false;
//     } else {
//         if 
//     }

// }

// std::tuple<bool, std::vector<int>> buscaSubciclo()
// {

// }
