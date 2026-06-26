#include <stdio.h>
#include <string.h>
#include "heap.h" //incluimos a heap.h para declarar ahi estructuras y funciones que se usaran luego

// Se calcula la prioridad del paciente combinando factor de riesgo,
// tiempo de espera y un bono por edad avanzada.
int calcularPrioridad(int factorRiesgo, int tiempoEspera, int edad) {
    int bonoEdad = 0;

    if (edad >= 65) {
        bonoEdad = 10;
    }

    return factorRiesgo + tiempoEspera + bonoEdad;
}

// Inicializa el Heap dejando su cantidad de elementos en 0.
void inicializarHeap(Heap *heap) {
    heap->cantidad = 0;
}

// Verifica si el Heap no contiene registros de atencion.
int heapVacio(Heap *heap) {
    return heap->cantidad == 0;
}

// Intercambia dos registros de atencion dentro del arreglo del Heap.
void intercambiar(RegistroAtencion *a, RegistroAtencion *b) {
    RegistroAtencion temp = *a;
    *a = *b;
    *b = temp;
}

// Reordena hacia arriba un registro recien insertado,
// manteniendo arriba al paciente con mayor prioridad.
void subirHeap(Heap *heap, int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;

        if (heap->datos[indice].prioridad > heap->datos[padre].prioridad) {
            intercambiar(&heap->datos[indice], &heap->datos[padre]);
            indice = padre;
        } else {
            break;
        }
    }
}

// Reordena hacia abajo la raiz del Heap despues de extraer
// al paciente con mayor prioridad.
void bajarHeap(Heap *heap, int indice) {
    while (1) {
        int hijoIzq = 2 * indice + 1;
        int hijoDer = 2 * indice + 2;
        int mayor = indice;

        if (hijoIzq < heap->cantidad &&
            heap->datos[hijoIzq].prioridad > heap->datos[mayor].prioridad) {
            mayor = hijoIzq;
        }

        if (hijoDer < heap->cantidad &&
            heap->datos[hijoDer].prioridad > heap->datos[mayor].prioridad) {
            mayor = hijoDer;
        }

        if (mayor != indice) {
            intercambiar(&heap->datos[indice], &heap->datos[mayor]);
            indice = mayor;
        } else {
            break;
        }
    }
}

// Inserta un RegistroAtencion al final del Heap y luego
// lo sube hasta su posicion correcta segun prioridad.
int insertarHeap(Heap *heap, RegistroAtencion registro) {
    if (heap->cantidad >= MAX_HEAP) {
        return 0;
    }

    heap->datos[heap->cantidad] = registro;
    subirHeap(heap, heap->cantidad);
    heap->cantidad++;

    return 1;
}

// Extrae la raiz del Heap, que corresponde al paciente
// con mayor prioridad dentro de una categoria ESI.
RegistroAtencion extraerMayorPrioridad(Heap *heap) {
    RegistroAtencion mayor;

    strcpy(mayor.rut, "");
    mayor.categoriaESI = 0;
    mayor.tiempoEspera = 0;
    mayor.prioridad = -1;

    if (heapVacio(heap)) {
        return mayor;
    }

    mayor = heap->datos[0];

    heap->datos[0] = heap->datos[heap->cantidad - 1];
    heap->cantidad--;

    bajarHeap(heap, 0);

    return mayor;
}

// Revisa las categorias ESI desde la mas urgente hasta la menos urgente
// y extrae al paciente prioritario de la primera categoria no vacia.
RegistroAtencion llamarSiguientePaciente(Heap urgencias[]) {
    int i;

    for (i = 0; i < CATEGORIAS_ESI; i++) {
        if (!heapVacio(&urgencias[i])) {
            return extraerMayorPrioridad(&urgencias[i]);
        }
    }

    RegistroAtencion vacio;
    strcpy(vacio.rut, "");
    vacio.categoriaESI = 0;
    vacio.tiempoEspera = 0;
    vacio.prioridad = -1;

    return vacio;
}

// Se crea un RegistroAtencion y lo inserta en el Heap correspondiente
// segun la categoria ESI indicada.
int ingresarRegistroAtencion(Heap urgencias[], char rut[], int categoriaESI, int tiempoEspera, int factorRiesgo, int edad) {
    if (categoriaESI < 1 || categoriaESI > CATEGORIAS_ESI) {
        return 0;
    }

    if (tiempoEspera < 0) {
        return 0;
    }

    RegistroAtencion registro;

    strcpy(registro.rut, rut);
    registro.categoriaESI = categoriaESI;
    registro.tiempoEspera = tiempoEspera;
    registro.prioridad = calcularPrioridad(factorRiesgo, tiempoEspera, edad);

    return insertarHeap(&urgencias[categoriaESI - 1], registro);
}

void mostrarEstadoUrgencias(Heap urgencias[]) {
  int i;

  printf("\n--- ESTADO DE URGENCIAS ---\n");

  for (i = 0; i < CATEGORIAS_ESI; i++) {
      printf("ESI %d: %d paciente(s)\n", i + 1, urgencias[i].cantidad);
  }
}

void mostrarRegistroAtencion(RegistroAtencion registro) {
    printf("RUT: %s\n", registro.rut);
    printf("Categoria ESI: %d\n", registro.categoriaESI);
    printf("Tiempo de espera: %d\n", registro.tiempoEspera);
    printf("Prioridad: %d\n", registro.prioridad);
}