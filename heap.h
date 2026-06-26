#ifndef HEAP_H  //include guard, Si HEAP_H no está definido, entra aquí.
#define HEAP_H  
//y ahora define HEAP_H.
//son protección para que el archivo heap.h no se copie más de una vez al compilar.

#include "paciente.h" //incluimos a paciente.h para declarar ahi estructuras y funciones.

#define MAX_HEAP 100
#define CATEGORIAS_ESI 5

typedef struct {
    RegistroAtencion datos[MAX_HEAP];
    int cantidad;
} Heap;

int calcularPrioridad(int factorRiesgo, int tiempoEspera, int edad);
void inicializarHeap(Heap *heap);
int heapVacio(Heap *heap);
int insertarHeap(Heap *heap, RegistroAtencion registro);
RegistroAtencion extraerMayorPrioridad(Heap *heap);
RegistroAtencion llamarSiguientePaciente(Heap urgencias[]);

int ingresarRegistroAtencion(Heap urgencias[], char rut[], int categoriaESI, int tiempoEspera, int factorRiesgo, int edad);
void mostrarEstadoUrgencias(Heap urgencias[]);
void mostrarRegistroAtencion(RegistroAtencion registro);

#endif