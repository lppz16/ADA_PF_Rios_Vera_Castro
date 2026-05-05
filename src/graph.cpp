#include "graph.hpp"
#include <cmath>

UnionFind::UnionFind(int n) : padre(n), rango(n, 0) {
    for (int i = 0; i < n; i++) padre[i] = i;
}

int UnionFind::find(int x) {
    if (padre[x] != x)
        padre[x] = find(padre[x]); // compresión de caminos
    return padre[x];
}

bool UnionFind::unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return false;
    // Unión por rango
    if (rango[px] < rango[py]) std::swap(px, py);
    padre[py] = px;
    if (rango[px] == rango[py]) rango[px]++;
    return true;
}

Grafo construirGrafo(const std::vector<double>& promediosMensuales, int N) {
    Grafo g;
    g.numNodos = N;

    for (int u = 0; u < N; u++) {
        for (int v = u + 1; v < N; v++) {
            // Redondear cada promedio a 2 decimales antes de sumar
            double mu = std::round(promediosMensuales[u] * 100.0) / 100.0;
            double mv = std::round(promediosMensuales[v] * 100.0) / 100.0;
            double costo = std::floor(mu + mv);
            g.aristas.push_back({u, v, costo});
        }
    }

    return g;
}