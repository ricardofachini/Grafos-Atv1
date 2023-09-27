#include "grafo.h"
#include <fstream>
#include <algorithm>
#include <limits>


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
                aresta->peso = std::stoi(linha.substr(4));
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

// retorna o peso da aresta entre (int: u) e (int: v)
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
    std::deque<int> fila;
    std::vector<int> visitados;
    int nivel = 0;
    visitados.push_back(s);
    fila.push_back(s);
    std::cout << nivel << ": " << s << "\n";
    while (fila.size() != 0) {
        std::vector<int> encontrados_no_nivel;
        int v = fila.front();
        fila.pop_front();
        auto vizinhos_de_v = vizinhos(v);
        for (auto& vizinho: vizinhos_de_v) {
            if ( std::find(visitados.begin(), visitados.end(), vizinho) == visitados.end() ) {
                visitados.push_back(vizinho);
                fila.push_back(vizinho);
                encontrados_no_nivel.push_back(vizinho);
            }
        }
        if (encontrados_no_nivel.size() != 0) {
            nivel++;
            std::cout << nivel << ": ";
        }
        for (auto& visitado: encontrados_no_nivel) {
            std::cout << visitado << ",";
        }
        if (encontrados_no_nivel.size() != 0) {
            std::cout << "\n";
        }
        encontrados_no_nivel.clear();
    }
}

// std::tuple<bool, std::vector<int>> Grafo::hierholzer()
// {
//     std::vector<int> empty; // vetor vazio (representa null)
//     for (auto& aresta: arestas) {
//         aresta->visitada = false;
//     }
//     int v = vertices.at(2).first;
//     bool r;
//     std::vector<int> ciclo;
//     std::tuple<bool, std::vector<int>> subciclo = buscaSubciclo(v);
//     r = std::get<0>(subciclo);
//     ciclo = std::get<1>(subciclo);
//     if (r == false) {
//         return std::make_tuple(false, empty);
//     } else {
//         for (auto& aresta: arestas)  {
//             if (aresta->visitada == false) {
//                 return std::make_tuple(false, empty);
//             }
//         }
//         return std::make_tuple(true, ciclo);
//     }
// }

// std::tuple<bool, std::vector<int>> Grafo::buscaSubciclo(int v)
// {
//     int t = v;
//     std::vector<int> vizinhos_v = vizinhos(v);
//     std::vector<int> ciclo = {v};
//     do
//     {
//         for (auto& vizinho: vizinhos_v) {
//             if (vizinho) {

//             } else {
//                 for (auto& aresta: arestas) {
//                     if (aresta->visitada == false) {
//                         aresta->visitada = true;
//                         v = aresta->vertice2;
//                         ciclo.push_back(v);
//                         break;
//                     }
//                 }
//             }
//         }
//     } while (v != t);
    
// }


void Grafo::dijkstra(int s)
{
    std::vector<int> visitados(vertices.size(), -1);
    std::vector<int> distancia(vertices.size(), INFINITO);
    //std::deque<int> empty;
    std::vector<int> predecessores(vertices.size(), 0);
    //predecessores[s-1] = -1;
    distancia[s-1] = 0;

    for (auto& vertice: vertices) {
        // vertice nao foi visitado
        int u = encontrarDistanciaMinima(distancia, visitados) + 1;
        visitados[u-1] = 1;
        std::vector<int> vizinhos_de_u = vizinhos(u);

        // pega um vizinho de u
        for (auto& v: vizinhos_de_u) {
            if (visitados[v-1] == -1 && haAresta(u, v)) {
                int peso_de_u_ate_v = peso(u, v);
                if (distancia[u-1] != INFINITO && distancia[u-1] + peso_de_u_ate_v < distancia[v-1]) {
                    distancia[v-1] = distancia[u-1] + peso_de_u_ate_v;
                    predecessores[v-1] = u;
                }
            }
        }
    }

    std::map<int, std::vector<int>> caminhos;
    for (int dest = 0; dest < vertices.size(); dest++) {
        std::deque<int> caminho; // caminho ate o destino atual da iteração
        int atual = dest;
        while (atual != -1)
        {
            caminho.push_front(atual+1);
            int& front = (predecessores[atual]);
            atual = front-1;
        }

        std::cout << (dest+1) << ": ";
        for (int v: caminho) {
            std::cout << v << ",";
        }
        std::cout << " d: " << distancia[dest] << "\n";
    }
    std::cout << std::endl;
}

int Grafo::encontrarDistanciaMinima(std::vector<int>& distancia, std::vector<int>& visitados)
{
    int minimo = INFINITO;
    int indice_minimo = -1;

    for (int i = 0; i < vertices.size(); i++) {
        if (visitados[i] == -1 && distancia[i] <= minimo) {
            minimo = distancia[i];
            indice_minimo = i;
        }
    }
    return indice_minimo;
}
