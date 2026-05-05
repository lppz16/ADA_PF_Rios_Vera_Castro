#pragma once
#include <vector>
#include <string>

struct Arista {
    int u, v;
    double peso;
    bool operator<(const Arista& otra) const {
        return peso < otra.peso;
    }
};

struct Grafo {
    int numNodos;
    std::vector<Arista> aristas;
};

// Union-Find
struct UnionFind {
    std::vector<int> padre, rango;
    UnionFind(int n);
    int find(int x);
    bool unite(int x, int y);
};

Grafo construirGrafo(const std::vector<double>& promediosMensuales, int N);