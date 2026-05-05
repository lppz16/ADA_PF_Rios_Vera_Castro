#include "parser.hpp"
#include <fstream>
#include <iostream>

// Elimina espacios, \r, \t al inicio y al final
static std::string trim(const std::string& s) {
    const std::string ws = " \t\r\n";
    size_t ini = s.find_first_not_of(ws);
    if (ini == std::string::npos) return "";
    size_t fin = s.find_last_not_of(ws);
    return s.substr(ini, fin - ini + 1);
}

// Divide línea CSV respetando campos entre comillas
static std::vector<std::string> splitCSV(const std::string& linea) {
    std::vector<std::string> campos;
    std::string campo;
    bool enComillas = false;

    for (char c : linea) {
        if (c == '"') {
            enComillas = !enComillas;
        } else if (c == ',' && !enComillas) {
            campos.push_back(campo);
            campo.clear();
        } else {
            campo += c;
        }
    }
    campos.push_back(campo);
    return campos;
}

std::vector<Solicitud> parsearCSV(const std::string& filepath,
                                   int& totalRegistros,
                                   int& registrosNulos) {
    std::vector<Solicitud> solicitudes;
    totalRegistros = 0;
    registrosNulos = 0;

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir " << filepath << "\n";
        return solicitudes;
    }

    std::string linea;
    std::getline(file, linea); // saltar cabecera

    while (std::getline(file, linea)) {
        if (trim(linea).empty()) continue;

        std::vector<std::string> c = splitCSV(linea);
        if (c.size() < 21) continue;

        Solicitud s;

        // [0] customerID
        s.customerID = trim(c[0]);

        // [5] tenure
        try { s.tenure = std::stoi(trim(c[5])); }
        catch (...) { s.tenure = 0; }

        // [18] MonthlyCharges
        try { s.monthlyCharges = std::stod(trim(c[18])); }
        catch (...) { s.monthlyCharges = 0.0; }

        // [19] TotalCharges — espacio en blanco si tenure == 0
        std::string tc = trim(c[19]);
        if (tc.empty()) {
            s.totalCharges = 0.0;
            registrosNulos++;
        } else {
            try { s.totalCharges = std::stod(tc); }
            catch (...) { s.totalCharges = 0.0; registrosNulos++; }
        }

        // [20] Churn — trim() elimina el \r de Windows antes de comparar
        s.churn = (trim(c[20]) == "Yes");

        solicitudes.push_back(s);
        totalRegistros++;
    }

    return solicitudes;
}