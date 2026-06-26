#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
    char rut[20];
    char nombre[50];
    int edad;
    int factorRiesgo;
} Paciente;

typedef struct {
    char rut[20];
    int categoriaESI;
    int tiempoEspera;
    int prioridad;
} RegistroAtencion;

Paciente crearPaciente(char rut[], char nombre[], int edad, int factorRiesgo);
void mostrarPaciente(Paciente p);

#endif