#include "binary_search.hpp"

// El arreglo está ordenado descendente por tenure.
// Buscamos el ÚLTIMO índice tal que arr[idx].tenure >= k
// (es decir, la primera posición desde la izquierda que cumple tenure >= k).
int busquedaBinaria(const std::vector<Solicitud>& arr, int izq, int der, int k) {
    if (izq > der) return -1;

    int mid = izq + (der - izq) / 2;

    if (arr[mid].tenure >= k) {
        // Puede haber más a la derecha que también cumplan
        int resultado = busquedaBinaria(arr, mid + 1, der, k);
        return (resultado == -1) ? mid : resultado;
    } else {
        // mid no cumple, buscar en la mitad izquierda
        return busquedaBinaria(arr, izq, mid - 1, k);
    }
}