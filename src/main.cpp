#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <numeric>

#include "parser.hpp"
#include "mergesort.hpp"
#include "binary_search.hpp"
#include "graph.hpp"
#include "kruskal.hpp"
#include "knapsack.hpp"

// ─── Utilidad ───────────────────────────────────────────────────────────────
static double medirTiempoMS(std::vector<Solicitud> arr) {
    auto inicio = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, (int)arr.size() - 1);
    auto fin = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(fin - inicio).count();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./ada_pf data/WA_Fn-UseC_-Telco-Customer-Churn.csv\n";
        return 1;
    }

    std::string rutaCSV = argv[1];

    // ════════════════════════════════════════════════════════════════════════
    // MÓDULO A — Divide y Vencerás
    // ════════════════════════════════════════════════════════════════════════
    std::cout << "=== MÓDULO A: Divide y Vencerás ===\n";

    int totalRegistros = 0, registrosNulos = 0;
    std::vector<Solicitud> solicitudes = parsearCSV(rutaCSV, totalRegistros, registrosNulos);

    std::cout << "Registros cargados     : " << totalRegistros << "\n";
    std::cout << "TotalCharges nulos     : " << registrosNulos << "\n";

    // Ordenamiento completo
    std::vector<Solicitud> ordenadas = solicitudes;
    auto t0 = std::chrono::high_resolution_clock::now();
    mergeSort(ordenadas, 0, (int)ordenadas.size() - 1);
    auto t1 = std::chrono::high_resolution_clock::now();
    double tiempoCompleto = std::chrono::duration<double, std::milli>(t1 - t0).count();

    // Submuestras
    std::vector<Solicitud> sub1000(solicitudes.begin(), solicitudes.begin() + 1000);
    std::vector<Solicitud> sub3500(solicitudes.begin(), solicitudes.begin() + 3500);

    double tiempo1000 = medirTiempoMS(sub1000);
    double tiempo3500 = medirTiempoMS(sub3500);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nTiempos de MergeSort:\n";
    std::cout << "  n=1000  : " << tiempo1000    << " ms\n";
    std::cout << "  n=3500  : " << tiempo3500    << " ms\n";
    std::cout << "  n=7043  : " << tiempoCompleto << " ms\n";

    // Guardar ordenadas
    {
        std::ofstream out("results/solicitudes_ordenadas.csv");
        out << "customerID,tenure,monthlyCharges,totalCharges,churn\n";
        for (auto& s : ordenadas) {
            out << s.customerID << "," << s.tenure << ","
                << std::fixed << std::setprecision(2)
                << s.monthlyCharges << "," << s.totalCharges << ","
                << (s.churn ? "Yes" : "No") << "\n";
        }
    }

    // Búsqueda binaria
    int consultas[] = {72, 60, 45, 30, 12};
    std::string nombresQ[] = {"Q_A01","Q_A02","Q_A03","Q_A04","Q_A05"};

    {
        std::ofstream out("results/busquedas_A.txt");
        out << "Consulta\tValor_k\tcustomerID\ttenure\n";

        std::cout << "\nResultados búsqueda binaria:\n";

        for (int i = 0; i < 5; i++) {
            int idx = busquedaBinaria(ordenadas, 0, (int)ordenadas.size() - 1, consultas[i]);

            std::string cid = (idx == -1) ? "NO_ENCONTRADO" : ordenadas[idx].customerID;
            int ten = (idx == -1) ? -1 : ordenadas[idx].tenure;

            out << nombresQ[i] << "\t" << consultas[i] << "\t" << cid << "\t" << ten << "\n";

            std::cout << "  " << nombresQ[i] << " (k=" << consultas[i] << "): "
                      << cid << " (tenure=" << ten << ")\n";
        }
    }

    // ════════════════════════════════════════════════════════════════════════
    // MÓDULO B — Kruskal
    // ════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== MÓDULO B: Codicioso / Kruskal ===\n";

    const int N = 20;
    std::vector<double> sumaGrupo(N, 0.0);
    std::vector<int> cuentaGrupo(N, 0);

    for (int i = 0; i < (int)solicitudes.size(); i++) {
        int g = i % N;
        sumaGrupo[g] += solicitudes[i].monthlyCharges;
        cuentaGrupo[g]++;
    }

    std::vector<double> promedios(N);
    for (int g = 0; g < N; g++) {
        promedios[g] = (cuentaGrupo[g] > 0) ? sumaGrupo[g] / cuentaGrupo[g] : 0.0;
    }

    Grafo grafo = construirGrafo(promedios, N);

    double sumaPesos = 0.0;
    for (auto& a : grafo.aristas) sumaPesos += a.peso;

    double costoPromArista = sumaPesos / grafo.aristas.size();

    std::cout << "Nodos: " << N
              << ", Aristas: " << grafo.aristas.size()
              << ", Costo promedio arista: " << costoPromArista << "\n";

    ResultadoMST mst = kruskal(grafo);
    std::cout << "Peso total MST: " << mst.pesoTotal << "\n";

    // ════════════════════════════════════════════════════════════════════════
    // MÓDULO C — Mochila (CORREGIDO)
    // ════════════════════════════════════════════════════════════════════════
    std::cout << "\n=== MÓDULO C: Programación Dinámica ===\n";

    std::vector<Solicitud> activas;

    // 🔥 CORRECCIÓN CLAVE
    for (auto& s : solicitudes) {
        if (!s.churn && s.totalCharges > 0 && s.monthlyCharges > 0) {
            activas.push_back(s);
            if ((int)activas.size() == 50) break;
        }
    }

    std::cout << "Solicitudes activas tomadas: " << activas.size() << "\n";

    const int W = 500;
    ResultadoMochila resultado = mochila01(activas, W);

    std::cout << "Valor óptimo (centavos): " << resultado.valorOptimo << "\n";
    std::cout << "Solicitudes seleccionadas: " << resultado.seleccionadas.size() << "\n";

    std::cout << "\nArchivos generados en results/\n";
    std::cout << "  solicitudes_ordenadas.csv\n";
    std::cout << "  busquedas_A.txt\n";
    std::cout << "  mst_red.txt\n";
    std::cout << "  asignacion_bw.txt\n";

    return 0;
}