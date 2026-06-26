#ifndef MENU_H
#define MENU_H

#include "hashmap.h"
#include "heap.h"
#include "paciente.h"
#include "csv.h"

// Función principal que arranca el bucle del menú
void mostrarMenuPrincipal();

// Funciones para cada opción del flujo de usuario
void flujoCargarPacientes();
void flujoBuscarPacientePorRUT();
void flujoIngresarUrgencia();
void flujoLlamarSiguientePaciente();

#endif 