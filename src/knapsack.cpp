#include "knapsack.hpp"
#include <cmath>
#include <algorithm>

static const double ESCALA = 20.0;

ResultadoMochila mochila01(const std::vector<Solicitud>& items, int W) {
    int n = (int)items.size();

    std::vector<int> pesos(n), valores(n);
    for (int i = 0; i < n; i++) {
        int p = (int)std::round(items[i].totalCharges / ESCALA);
        pesos[i]   = std::max(1, std::min(p, W)); // entre 1 y W, nunca fuera
        valores[i] = (int)std::round(items[i].monthlyCharges * 10.0);
    }

    // Tabla dp[i][w] — dimensiones (n+1) x (W+1)
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i-1][w]; // no incluir item i
            if (pesos[i-1] <= w) {
                dp[i][w] = std::max(dp[i][w],
                    dp[i-1][w - pesos[i-1]] + valores[i-1]);
            }
        }
    }

    // Backtracking para recuperar la solución exacta
    ResultadoMochila resultado;
    resultado.valorOptimo = dp[n][W];

    int w = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            resultado.seleccionadas.push_back(items[i-1]);
            w -= pesos[i-1];
        }
    }

    return resultado;
}