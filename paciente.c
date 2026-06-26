#include <stdio.h>
#include <string.h>
#include "paciente.h"

// Crea un Paciente nuevo con los datos de su ficha medica.
Paciente crearPaciente(char rut[], char nombre[], int edad, int factorRiesgo) {
    Paciente p;
    strcpy(p.rut, rut);
    strcpy(p.nombre, nombre);
    p.edad = edad;

    if (factorRiesgo < 1) {
        factorRiesgo = 1;
    } else if (factorRiesgo > 10) {
        factorRiesgo = 10;
    }

    p.factorRiesgo = factorRiesgo;
    return p;
}

// Muestra por consola la ficha medica de un paciente.
void mostrarPaciente(Paciente p) {
    printf("RUT: %s\n", p.rut);
    printf("Nombre: %s\n", p.nombre);
    printf("Edad: %d\n", p.edad);
    printf("Factor de riesgo: %d\n", p.factorRiesgo);
}
