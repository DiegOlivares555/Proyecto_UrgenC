#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

// Función hash.
// Convierte el RUT en un índice dentro de la tabla hash.
unsigned int hash(char *key)
{
    unsigned int h = 0;

    // Recorre cada carácter del RUT para calcular el hash
    while (*key)
    {
        h = h * 31 + *key;
        key++;
    }

    // Devuelve un índice válido dentro de la tabla
    return h % TABLE_SIZE;
}

// Crea un nuevo HashMap e inicializa todas sus posiciones en NULL.
HashMap *crearHashMap()
{
    HashMap *map = malloc(sizeof(HashMap));

    // Inicializa cada posición de la tabla vacía
    for (int i = 0; i < TABLE_SIZE; i++)
        map->tabla[i] = NULL;

    return map;
}

// Inserta un paciente en el HashMap utilizando el RUT como clave.
void insertar(HashMap *map, char *rut, void *dato)
{
    // Calcula la posición donde se almacenará el paciente
    unsigned int indice = hash(rut);

    // Crea un nuevo nodo
    Nodo *nuevo = malloc(sizeof(Nodo));

    // Guarda la clave y el dato asociado
    strcpy(nuevo->rut, rut);
    nuevo->dato = dato;

    // Inserta el nodo al inicio de la lista enlazada
    // para manejar posibles colisiones.
    nuevo->sig = map->tabla[indice];
    map->tabla[indice] = nuevo;
}

// Busca un paciente utilizando su RUT.
void *buscar(HashMap *map, char *rut)
{
    // Calcula la posición correspondiente al RUT
    unsigned int indice = hash(rut);

    Nodo *aux = map->tabla[indice];

    // Recorre la lista enlazada buscando la clave
    while (aux != NULL)
    {
        if (strcmp(aux->rut, rut) == 0)
            return aux->dato;

        aux = aux->sig;
    }

    // Si no encuentra el RUT, devuelve NULL
    return NULL;
}

// Libera toda la memoria utilizada por el HashMap.
void liberarHashMap(HashMap *map)
{
    // Recorre todas las posiciones de la tabla
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Nodo *aux = map->tabla[i];

        // Libera cada nodo de la lista enlazada
        while (aux)
        {
            Nodo *temp = aux;
            aux = aux->sig;
            free(temp);
        }
    }

    // Libera la estructura principal del HashMap
    free(map);
}