#ifndef HASHMAP_H
#define HASHMAP_H

// Cantidad de posiciones de la tabla hash
#define TABLE_SIZE 101

// Nodo que almacena un paciente dentro de la tabla hash
typedef struct Nodo
{
    char rut[20];      // Clave única del paciente
    void *dato;        // Puntero al paciente
    struct Nodo *sig;  // Siguiente nodo (para manejar colisiones)
} Nodo;

// Estructura principal del HashMap
typedef struct
{
    Nodo *tabla[TABLE_SIZE];
} HashMap;

// Crea e inicializa un HashMap vacío
HashMap *crearHashMap();

// Inserta un paciente usando el RUT como clave
void insertar(HashMap *map, char *rut, void *dato);

// Busca un paciente según su RUT
void *buscar(HashMap *map, char *rut);

// Libera la memoria utilizada por el HashMap
void liberarHashMap(HashMap *map);

#endif