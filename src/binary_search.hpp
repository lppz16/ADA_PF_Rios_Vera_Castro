#pragma once
#include "parser.hpp"
#include <vector>

// Retorna el índice de la primera solicitud con tenure >= k
// (arreglo ordenado descendente). Retorna -1 si no existe.
int busquedaBinaria(const std::vector<Solicitud>& arr, int izq, int der, int k);