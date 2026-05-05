#pragma once
#include "parser.hpp"
#include <vector>

struct ResultadoMochila {
    int valorOptimo;
    std::vector<Solicitud> seleccionadas;
};

ResultadoMochila mochila01(const std::vector<Solicitud>& items, int W);