#pragma once
#include "graph.hpp"
#include <vector>

struct ResultadoMST {
    std::vector<Arista> aristas;
    double pesoTotal;
};

ResultadoMST kruskal(Grafo& g);