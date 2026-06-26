#include <stdio.h>
#include "heap.h"

int main() {
    Heap urgencias[CATEGORIAS_ESI];
    int i;

    for (i = 0; i < CATEGORIAS_ESI; i++) {
        inicializarHeap(&urgencias[i]);
    }

    ingresarRegistroAtencion(urgencias, "11111111-1", 3, 20, 10, 70);
    ingresarRegistroAtencion(urgencias, "22222222-2", 3, 40, 5, 45);
    ingresarRegistroAtencion(urgencias, "33333333-3", 2, 15, 8, 30);

    mostrarEstadoUrgencias(urgencias);

    RegistroAtencion siguiente = llamarSiguientePaciente(urgencias);

    printf("\nPaciente llamado:\n");
    mostrarRegistroAtencion(siguiente);

    mostrarEstadoUrgencias(urgencias);

    return 0;
}