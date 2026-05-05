#include "kruskal.hpp"
#include <algorithm>

ResultadoMST kruskal(Grafo& g) {
    std::sort(g.aristas.begin(), g.aristas.end());

    UnionFind uf(g.numNodos);
    ResultadoMST resultado;
    resultado.pesoTotal = 0.0;

    for (auto& arista : g.aristas) {
        if (uf.unite(arista.u, arista.v)) {
            resultado.aristas.push_back(arista);
            resultado.pesoTotal += arista.peso;
            if ((int)resultado.aristas.size() == g.numNodos - 1) break;
        }
    }

    return resultado;
}