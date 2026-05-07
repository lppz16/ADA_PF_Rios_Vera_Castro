#include "binary_search.hpp"

// El arreglo está ordenado DESCENDENTEMENTE por tenure.
// Busca un registro con tenure EXACTAMENTE igual a k.
// Si existe, retorna su índice.
// Si no existe, retorna -1.

int busquedaBinaria(const std::vector<Solicitud>& arr, int izq, int der, int k) {
    if (izq > der) return -1;

    int mid = izq + (der - izq) / 2;

    if (arr[mid].tenure == k) {
        return mid;
    }

    // Como está ordenado DESCENDENTE:
    // valores mayores están a la izquierda
    if (arr[mid].tenure < k) {
        return busquedaBinaria(arr, izq, mid - 1, k);
    } else {
        return busquedaBinaria(arr, mid + 1, der, k);
    }
}