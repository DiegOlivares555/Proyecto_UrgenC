#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "hashmap.h"
#include "heap.h"
#include "paciente.h"
#include "csv.h"

#define LIMPIAR_PANTALLA() system("clear")

static HashMap *mapaPacientes = NULL;
static Heap urgencias[CATEGORIAS_ESI];

static void pausarYLimpiar() {
    printf("\nPresione ENTER para continuar...");
    getchar();
    LIMPIAR_PANTALLA();
}

void mostrarMenuPrincipal() {
    int opcion = 0;

    printf("Inicializando sistema UrgenC...\n");
    mapaPacientes = crearHashMap();
    for (int i = 0; i < CATEGORIAS_ESI; i++) {
        inicializarHeap(&urgencias[i]);
    }

    do {
        printf("\n===================================\n");
        printf("        SISTEMA URGEN-C            \n");
        printf("===================================\n");
        printf("1. Cargar pacientes desde CSV\n");
        printf("2. Buscar paciente por RUT (Ficha Medica)\n");
        printf("3. Ingresar paciente a Urgencias\n");
        printf("4. Llamar al siguiente paciente\n");
        printf("5. Salir\n");
        printf("===================================\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Error: Por favor, ingrese un numero valido.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }
        while (getchar() != '\n'); // Limpiar el buffer

        switch(opcion) {
            case 1:
                flujoCargarPacientes();
                pausarYLimpiar();
                break;
            case 2:
                flujoBuscarPacientePorRUT();
                pausarYLimpiar();
                break;
            case 3:
                flujoIngresarUrgencia();
                pausarYLimpiar();
                break;
            case 4:
                flujoLlamarSiguientePaciente();
                pausarYLimpiar();
                break;
            case 5:
                printf("Saliendo del sistema UrgenC. ¡Hasta luego!\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                pausarYLimpiar();    
        }
    } while(opcion != 5);
    liberarHashMap(mapaPacientes);
}

void flujoCargarPacientes() {
    printf("\n--- CARGAR PACIENTES DESDE CSV ---\n");
    cargarPacientes(mapaPacientes, "data/pacientes.csv");
    printf("Pacientes cargados exitosamente al HashMap.\n");
}

void flujoBuscarPacientePorRUT() {
    char rut[15];
    printf("\n--- BUSCAR PACIENTE POR RUT ---\n");
    printf("Ingrese el RUT del paciente (con guion y digito verificador): ");
    fgets(rut, sizeof(rut), stdin);
    rut[strcspn(rut, "\n")] = '\0'; // Eliminar el salto de línea
    
    Paciente *p = (Paciente *) buscar(mapaPacientes, rut);
    
    printf("\nBuscando RUT: %s...\n", rut);
    if (p != NULL) {
        printf("\n--- FICHA MEDICA ---\n");
        mostrarPaciente(*p);
    } else {
        printf("Paciente no encontrado. Verifique el RUT o cargue los pacientes (opcion 1).\n");
    }
}

void flujoIngresarUrgencia() {
    char rut[20];
    int categoriaESI = 0;
    int tiempoEspera = 0;

    printf("\n--- INGRESO A URGENCIAS ---\n");
    printf("Ingrese el RUT del paciente: ");
    fgets(rut, sizeof(rut), stdin);
    rut[strcspn(rut, "\n")] = '\0';

    // 1. Validar que el paciente exista en el sistema
    Paciente *p = (Paciente *) buscar(mapaPacientes, rut);
    if (p == NULL) {
        printf("El paciente con RUT %s no esta registrado. Cargue los pacientes primero (opcion 1).\n", rut);
        return;
    }

    printf("Ingrese Categoria ESI (1 - Mas urgente, 5 - Menos urgente): ");
    if (scanf("%d", &categoriaESI) != 1 || categoriaESI < 1 || categoriaESI > CATEGORIAS_ESI) {
        printf("Categoria ESI invalida. Debe ser entre 1 y %d.\n", CATEGORIAS_ESI);
        while (getchar() != '\n');
        return;
    }

    printf("Ingrese tiempo de espera acumulado (en minutos): ");
    if (scanf("%d", &tiempoEspera) != 1 || tiempoEspera < 0) {
        printf("Tiempo de espera invalido.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');


    // 2. Crear el RegistroAtencion 
    int exito = ingresarRegistroAtencion(urgencias, rut, categoriaESI, tiempoEspera, p->factorRiesgo, p->edad);
    
    if (exito) {
        printf("\n[Exito] Paciente %s ingresado correctamente a la cola de prioridad ESI %d.\n",
               p->nombre, categoriaESI);
    } else {
        printf("\n[Error] No se pudo ingresar al paciente (cola ESI %d llena).\n", categoriaESI);
    }
}

void flujoLlamarSiguientePaciente() {
    printf("\n--- LLAMAR SIGUIENTE PACIENTE ---\n");

    // Recorre internamente las categorias ESI de 1 a 5 y extrae al paciente
    // de mayor prioridad dentro de la primera categoria no vacia.
    RegistroAtencion siguiente = llamarSiguientePaciente(urgencias);

    if (siguiente.prioridad == -1) {
        printf("No hay pacientes en espera en ninguna de las colas de urgencia.\n");
        return;
    }

    Paciente *p = (Paciente *) buscar(mapaPacientes, siguiente.rut);

    printf(">> ATENCION << Se solicita al paciente %s (RUT %s) en el box de atencion.\n",
           (p != NULL) ? p->nombre : "Desconocido", siguiente.rut);
    printf("Categoria: ESI %d\n", siguiente.categoriaESI);
    mostrarRegistroAtencion(siguiente);
}