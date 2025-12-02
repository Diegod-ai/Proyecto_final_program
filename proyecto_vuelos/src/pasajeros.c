#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "pasajeros.h" 
#include "vuelos.h" 

void cargarPasajeros(Pasajero *lista, int *cant) {
    FILE *file = NULL;
    
    // Intentar primero en data/
    file = fopen("../data/pasajeros.txt", "r");
    
    // Si no existe, intentar en el directorio actual
    if (!file) {
        file = fopen("pasajeros.txt", "r");
    }
    
    if (!file) { 
        printf("Nota: No se encontro archivo de pasajeros. Iniciando con lista vacia.\n");
        *cant = 0; 
        return;
    }
    
    char linea[256];
    int idx = 0;    

    while (fgets(linea, sizeof(linea), file) && idx < MAX_PASAJEROS) { 
        linea[strcspn(linea, "\r\n")] = 0;

        int leidos = sscanf(linea, "%d,%49[^,],%19[^,],%d,%d", 
                           &lista[idx].cedula, 
                           lista[idx].nombre, 
                           lista[idx].telefono, 
                           &lista[idx].estado, 
                           &lista[idx].nroVuelo);

        if (leidos < 5) {
            printf("Advertencia: linea de pasajero malformada ignorada.\n");
            continue;
        }   

        idx++;
    }
    
    fclose(file);
    *cant = idx;
    printf("Pasajeros cargados exitosamente: %d\n", idx);
} 

void guardarPasajeros(Pasajero *lista, int cant) {
    FILE *file = NULL;
    
    // Intentar primero en data/
    file = fopen("../data/pasajeros.txt", "w");
    
    // Si no se puede, intentar en el directorio actual
    if (!file) {
        file = fopen("pasajeros.txt", "w");
    }
    
    if (!file) { 
        printf("ERROR: No se pudo guardar el archivo de pasajeros.\n");
        printf("Verifique permisos de escritura en el directorio.\n");
        return;
    }   

    for (int i = 0; i < cant; i++) {
        fprintf(file, "%d,%s,%s,%d,%d\n", 
                lista[i].cedula, 
                lista[i].nombre, 
                lista[i].telefono, 
                lista[i].estado, 
                lista[i].nroVuelo); 
    }

    fclose(file);
    printf("Pasajeros guardados exitosamente: %d registros.\n", cant);
}

void adicionarPasajero(Pasajero *lista, int *cant, Vuelo *vuelos, int cantVuelos) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    printf("--- ADICIONAR PASAJERO ---\n");
    
    if (*cant >= MAX_PASAJEROS) {
        printf("No se pueden agregar mas pasajeros. Limite alcanzado.\n");
        return;
    }

    Pasajero nuevo;
    printf("Ingrese cedula (numero): ");
    scanf("%d", &nuevo.cedula);
    
    if (buscarPasajeroPorCedula(lista, *cant, nuevo.cedula) != -1) {
        printf("Ya existe un pasajero con cedula %d. No se agrega.\n", nuevo.cedula);
        return;
    }
    
    printf("Ingrese nombre: ");
    scanf(" %49[^\n]", nuevo.nombre); 
    printf("Ingrese telefono: ");
    scanf(" %19[^\n]", nuevo.telefono);
    printf("Ingrese numero de vuelo: ");
    scanf("%d", &nuevo.nroVuelo);

    // Validar existencia del vuelo
    int idxVuelo = -1;
    for (int i = 0; i < cantVuelos; i++) {
        if (vuelos[i].nroVuelo == nuevo.nroVuelo) {
            idxVuelo = i;
            break;
        }
    }

    if (idxVuelo == -1) {
        printf("El numero de vuelo %d no existe. Pasajero no agregado.\n", nuevo.nroVuelo);
        return;
    }

    // Validar que el vuelo no esté realizado
    if (vuelos[idxVuelo].estado == 1) {
        printf("El vuelo %d ya fue realizado. No se pueden agregar pasajeros.\n", nuevo.nroVuelo);
        return;
    }

    nuevo.estado = 1; // reservado
    lista[*cant] = nuevo;
    (*cant)++;
    printf("Pasajero agregado exitosamente.\n");
}

void listarPasajerosDeVuelo(Pasajero *lista, int cant, int nroVuelo) {
    printf("--- PASAJEROS DEL VUELO %d ---\n", nroVuelo);
    int encontrados = 0;
    for (int i = 0; i < cant; i++) {
        if (lista[i].nroVuelo == nroVuelo) {
            printf("Cedula: %d, Nombre: %s, Telefono: %s, Estado: %s\n", 
                   lista[i].cedula, 
                   lista[i].nombre, 
                   lista[i].telefono, 
                   (lista[i].estado == 1) ? "Reservado" : "A bordo");
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("No hay pasajeros registrados para este vuelo.\n");
    }
}

int buscarPasajeroPorCedula(Pasajero *lista, int cant, int cedula) {
    for (int i = 0; i < cant; i++) {
        if (lista[i].cedula == cedula) {
            return i;
        }
    }
    return -1;
}

void registrarPasajeroABordo(Pasajero *lista, int cant, int cedula) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    printf("--- REGISTRAR PASAJERO A BORDO ---\n");
    
    for (int i = 0; i < cant; i++) {
        if (lista[i].cedula == cedula) {
            if (lista[i].estado == 2) {
                printf("El pasajero ya esta registrado como 'a bordo'.\n");
                return;
            }
            lista[i].estado = 2; // a bordo
            printf("Pasajero %s registrado como 'a bordo'.\n", lista[i].nombre);
            return;
        }
    }
    printf("No se encontro pasajero con cedula %d.\n", cedula);
}