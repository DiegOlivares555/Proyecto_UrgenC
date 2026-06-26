#ifndef CSV_H
#define CSV_H

#include "hashmap.h"
#include "paciente.h"

// Lee el archivo CSV e inserta todos los pacientes
// dentro del HashMap.
void cargarPacientes(HashMap *map, char *archivo);

// Guarda todos los pacientes del HashMap
// nuevamente en un archivo CSV.
void guardarPacientes(HashMap *map, char *archivo);

#endif