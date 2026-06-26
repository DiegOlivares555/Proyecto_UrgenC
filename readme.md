# UrgenC

Sistema de gestión de urgencias hospitalarias en C. Permite cargar pacientes desde un archivo CSV, buscar su ficha médica por RUT, ingresarlos a una cola de prioridad según su categoría ESI (Escala de Severidad de Urgencias) y llamar al siguiente paciente respetando el orden de gravedad (ESI 1 = más urgente, ESI 5 = menos urgente).

## Integrantes

- Tomás — Estructuras y Heap (`paciente.h/.c`, `heap.h/.c`)
- Calde — HashMap y CSV (`hashmap.h/.c`, `csv.h/.c`)
- Diego Olivares — Menú y flujo de usuario (`main.c`, `menu.h/.c`)
- Fernando Hernandez — Integración, GitHub, Git

## Estructura del proyecto

```
.
├── main.c          # Punto de entrada
├── menu.h / menu.c # Menú interactivo por consola
├── paciente.h/.c   # Struct Paciente, RegistroAtencion y funciones auxiliares
├── heap.h / heap.c # Heap binario por prioridad + arreglo de 5 Heaps ESI
├── hashmap.h/.c    # HashMap para fichas médicas, indexado por RUT
├── csv.h / csv.c   # Carga y guardado de pacientes desde/hacia CSV
├── data/
│   └── pacientes.csv
├── Makefile
└── README.md
```

## Compilación

Se requiere `gcc` y `make`.

```bash
make
```

Esto genera el ejecutable `urgenc` en la raíz del proyecto.

Para limpiar los archivos generados:

```bash
make clean
```

## Ejecución

```bash
./urgenc
```

El programa muestra un menú con las siguientes opciones:

1. **Cargar pacientes desde CSV**: carga `data/pacientes.csv` al HashMap de fichas médicas.
2. **Buscar paciente por RUT**: busca y muestra la ficha médica de un paciente.
3. **Ingresar paciente a Urgencias**: valida que el paciente exista, pide categoría ESI (1-5) y tiempo de espera, calcula su prioridad y lo inserta en el Heap correspondiente.
4. **Llamar al siguiente paciente**: extrae al paciente con mayor prioridad respetando el orden de categorías ESI 1 → 5.
5. **Ver estado de las urgencias**: muestra cuántos pacientes hay esperando en cada categoría ESI.
6. **Salir**: libera la memoria utilizada y termina el programa.

- El sistema no crea pacientes manualmente desde consola. Carga fichas médicas desde CSV, las guarda en el HashMap y luego permite buscarlas por RUT para ingresarlas a urgencias.

## Formato del CSV

El archivo `data/pacientes.csv` debe tener la siguiente cabecera y formato:

```
rut,nombre,edad,factorRiesgo
11111111-1,Juan Perez,30,5
```

## Cálculo de prioridad

La prioridad de un paciente se calcula dentro de su categoría ESI. Es decir, el sistema primero respeta la gravedad clínica según ESI y luego ordena a los pacientes de una misma categoría usando una prioridad numérica. La fórmula utilizada es:

```
prioridad = factorRiesgo + tiempoEspera + bonoEdad
```

Donde:

`factorRiesgo`: valor clínico entre 1 y 10, asignado por personal autorizado al crear o actualizar la ficha médica del paciente. No es un dato ingresado por el paciente.

`tiempoEspera`: valor registrado al momento de ingresar al paciente a urgencias. En esta versión del sistema se maneja como dato de entrada y no se actualiza automáticamente con el paso del tiempo.

`bonoEdad`: valor adicional de 10 puntos si el paciente tiene 65 años o más; en caso contrario, es 0.

## Notas de diseño

- Las categorías ESI van de 1 (más urgente, ej. riesgo vital) a 5 (menos urgente). El sistema siempre llama primero a pacientes de categorías más urgentes, sin importar cuánto tiempo lleve esperando alguien de una categoría menos urgente.
- Dentro de una misma categoría ESI, se prioriza según el valor de `prioridad` calculado (mayor prioridad = se atiende primero).

## Limitaciones y mejoras futuras

- En esta versión, el tiempo de espera se registra como dato de entrada al ingresar al paciente a urgencias. Una mejora futura sería almacenar la hora exacta de ingreso y recalcular automáticamente el tiempo de espera antes de llamar al siguiente paciente.
- Si un paciente abandona la sala de espera antes de ser llamado, una solución futura sería marcarlo como inactivo o retirado. Luego, cuando ese registro aparezca en la raíz del Heap, el sistema podría omitirlo y extraer el siguiente paciente disponible. Esta estrategia evita eliminar elementos desde posiciones intermedias del Heap.
- El factor de riesgo se considera un dato clínico validado por personal autorizado. El sistema lo utiliza para calcular prioridad, pero no lo infiere automáticamente desde diagnósticos o antecedentes médicos detallados.
