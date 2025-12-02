#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vuelos.h"

void cargarVuelos(Vuelo *vuelos, int *cantidad) {
    FILE *file = NULL;
    
    // Intentar primero en data/
    file = fopen("data/vuelos.txt", "r");
    
    // Si no existe, intentar en el directorio actual
    if (!file) {
        file = fopen("vuelos.txt", "r");
    }
    
    if (!file) { 
        printf("Nota: No se encontro archivo de vuelos. Iniciando con lista vacia.\n");
        *cantidad = 0; 
        return;
    }
    
    char linea[256];
    int idx = 0;    

    while (fgets(linea, sizeof(linea), file) && idx < MAX_VUELOS) {
        int r = sscanf(linea,
                       "%d,%49[^,],%49[^,],%19[^,],%49[^,],%5[^,],%10[^,],%d",
                       &vuelos[idx].nroVuelo,
                       vuelos[idx].origen,
                       vuelos[idx].destino,
                       vuelos[idx].matricula,
                       vuelos[idx].piloto,
                       vuelos[idx].hora,
                       vuelos[idx].fecha,
                       &vuelos[idx].estado);

        if (r == 8) {
            idx++;
        } else {
            printf("Advertencia: linea ignorada por formato invalido:\n%s\n", linea);
        }
    }

    fclose(file);
    *cantidad = idx;
    printf("Vuelos cargados exitosamente: %d\n", idx);
}

void guardarVuelos(Vuelo *vuelos, int cantidad) {
    FILE *file = NULL;
    
    // Intentar primero en data/
    file = fopen("data/vuelos.txt", "w");
    
    // Si no se puede, intentar en el directorio actual
    if (!file) {
        file = fopen("vuelos.txt", "w");
    }
    
    if (!file) { 
        printf("ERROR: No se pudo guardar el archivo de vuelos.\n");
        printf("Verifique permisos de escritura en el directorio.\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%d\n", 
                vuelos[i].nroVuelo, 
                vuelos[i].origen, 
                vuelos[i].destino, 
                vuelos[i].matricula, 
                vuelos[i].piloto, 
                vuelos[i].hora, 
                vuelos[i].fecha, 
                vuelos[i].estado);
    }

    fclose(file);
    printf("Vuelos guardados exitosamente: %d registros.\n", cantidad);
}

void adicionarVuelo(Vuelo *vuelos, int *cantidad) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("--- ADICIONAR VUELO ---\n");
    
    if (*cantidad >= MAX_VUELOS) {
        printf("No se pueden agregar mas vuelos. Limite alcanzado.\n");
        return;
    }

    Vuelo nuevo;

    printf("Ingrese numero de vuelo: ");
    scanf("%d", &nuevo.nroVuelo);

    if (buscarVuelo(vuelos, *cantidad, nuevo.nroVuelo) != -1) {
        printf("Error: el numero de vuelo ya existe. No se puede duplicar.\n");
        return;
    }

    printf("Ingrese origen: ");
    scanf(" %49[^\n]", nuevo.origen);
    printf("Ingrese destino: ");
    scanf(" %49[^\n]", nuevo.destino);
    printf("Ingrese matricula: ");
    scanf(" %19[^\n]", nuevo.matricula);
    printf("Ingrese piloto: ");
    scanf(" %49[^\n]", nuevo.piloto);
    printf("Ingrese hora (HH:MM): ");
    scanf(" %5[^\n]", nuevo.hora);
    printf("Ingrese fecha (DD/MM/YYYY): ");
    scanf(" %10[^\n]", nuevo.fecha);

    nuevo.estado = 0;

    vuelos[*cantidad] = nuevo;
    (*cantidad)++;

    printf("Vuelo agregado exitosamente.\n");
}

void listarVuelosProgramados(Vuelo *vuelos, int cantidad) {
    printf("--- VUELOS PROGRAMADOS ---\n");
    int encontrados = 0;
    for (int i = 0; i < cantidad; i++) {
        if (vuelos[i].estado == 0) {
            printf("Nro: %d, Origen: %s, Destino: %s, Fecha: %s, Hora: %s\n",
                   vuelos[i].nroVuelo,
                   vuelos[i].origen,
                   vuelos[i].destino,
                   vuelos[i].fecha,
                   vuelos[i].hora);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("No hay vuelos programados.\n");
    }
}

void listarVuelosRealizados(Vuelo *vuelos, int cantidad) {
    printf("--- VUELOS REALIZADOS ---\n");
    int encontrados = 0;
    for (int i = 0; i < cantidad; i++) {
        if (vuelos[i].estado == 1) {
            printf("Nro: %d, Origen: %s, Destino: %s, Fecha: %s, Hora: %s\n",
                   vuelos[i].nroVuelo,
                   vuelos[i].origen,
                   vuelos[i].destino,
                   vuelos[i].fecha,
                   vuelos[i].hora);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("No hay vuelos realizados.\n");
    }
}

int buscarVuelo(Vuelo *vuelos, int cantidad, int nroVuelo) {
    for (int i = 0; i < cantidad; i++) {
        if (vuelos[i].nroVuelo == nroVuelo) {
            return i;
        }
    }
    return -1; 
}

void marcarVueloRealizado(Vuelo *vuelos, int cantidad) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("--- MARCAR VUELO COMO REALIZADO ---\n");
    
    int nroVuelo;
    printf("Ingrese numero de vuelo a marcar como realizado: ");
    scanf("%d", &nroVuelo);

    int idx = buscarVuelo(vuelos, cantidad, nroVuelo);
    if (idx == -1) {
        printf("Vuelo %d no encontrado.\n", nroVuelo);
        return;
    }

    if (vuelos[idx].estado == 1) {
        printf("El vuelo %d ya estaba marcado como realizado.\n", nroVuelo);
        return;
    }

    vuelos[idx].estado = 1;
    printf("Vuelo %d marcado como realizado exitosamente.\n", nroVuelo);
}