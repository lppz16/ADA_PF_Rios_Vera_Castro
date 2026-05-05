#pragma once
#include <string>
#include <vector>

struct Solicitud {
    std::string customerID;
    int tenure;
    double monthlyCharges;
    double totalCharges;
    bool churn; // true = Yes (en riesgo), false = No (activa)
};

std::vector<Solicitud> parsearCSV(const std::string& filepath,
                                   int& totalRegistros,
                                   int& registrosNulos);