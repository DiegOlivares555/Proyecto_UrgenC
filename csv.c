#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"

// Carga los pacientes desde un archivo CSV e
// inserta cada uno en el HashMap utilizando el RUT como clave.
void cargarPacientes(HashMap *map, char *archivo)
{
    // Abre el archivo en modo lectura
    FILE *fp = fopen(archivo, "r");

    // Verifica que el archivo exista
    if (fp == NULL)
    {
        printf("No se pudo abrir el archivo %s.\n", archivo);
        return;
    }

    char linea[256];

    // Lee y descarta la primera línea (encabezados)
    fgets(linea, sizeof(linea), fp);

    // Lee cada registro del archivo
    while (fgets(linea, sizeof(linea), fp))
    {
        // Ignora líneas vacías
        if (linea[0] == '\n' || linea[0] == '\0') {
            continue;
        }

        // Reserva memoria para un nuevo paciente
        Paciente *p = malloc(sizeof(Paciente));

        // Obtiene el RUT
        char *token = strtok(linea, ",");
        if (token == NULL) {
            free(p);
            continue;
        }
        strcpy(p->rut, token);

        // Obtiene el nombre
        token = strtok(NULL, ",");
        if (token == NULL) {
            free(p);
            continue;
        }
        strcpy(p->nombre, token);

        // Obtiene la edad
        token = strtok(NULL, ",");
        if (token == NULL) {
            free(p);
            continue;
        }
        p->edad = atoi(token);

        // Obtiene el factor de riesgo.
        // Si no existe el dato, se asigna 0 por defecto.
        token = strtok(NULL, ",\n");
        p->factorRiesgo = (token != NULL) ? atoi(token) : 0;

        // Inserta el paciente en el HashMap usando el RUT como clave
        insertar(map, p->rut, p);
    }

    // Cierra el archivo
    fclose(fp);
}

// Guarda todos los pacientes almacenados en el HashMap
// dentro de un archivo CSV.
void guardarPacientes(HashMap *map, char *archivo)
{
    // Abre el archivo en modo escritura
    FILE *fp = fopen(archivo, "w");

    if (fp == NULL)
        return;

    // Escribe la fila de encabezados
    fprintf(fp, "rut,nombre,edad,factorRiesgo\n");

    // Recorre todas las posiciones de la tabla hash
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Nodo *aux = map->tabla[i];

        // Recorre la lista enlazada de cada posición
        while (aux)
        {
            Paciente *p = (Paciente *)aux->dato;

            // Escribe los datos del paciente en el archivo CSV
            fprintf(fp, "%s,%s,%d,%d\n",
                p->rut,
                p->nombre,
                p->edad,
                p->factorRiesgo);

            aux = aux->sig;
        }
    }

    // Cierra el archivo
    fclose(fp);
}