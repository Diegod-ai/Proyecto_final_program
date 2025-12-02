#ifndef PASAJEROS_H
#define PASAJEROS_H
#define MAX_PASAJEROS 200

typedef struct Vuelo Vuelo;

typedef struct {
    int cedula;
    char nombre[50];
    char telefono[20];
    int estado;    // 1: reservado, 2: a bordo
    int nroVuelo;
} Pasajero;

void cargarPasajeros(Pasajero *lista, int *cant);
void guardarPasajeros(Pasajero *lista, int cant);

void adicionarPasajero(Pasajero *lista, int *cant, Vuelo *vuelos, int cantVuelos);

void listarPasajerosDeVuelo(Pasajero *lista, int cant, int nroVuelo);

// CORREGIDO: cambiado int *cedula a int cedula
int buscarPasajeroPorCedula(Pasajero *lista, int cant, int cedula);

// CORREGIDO: cambiado int *cedula a int cedula
void registrarPasajeroABordo(Pasajero *lista, int cant, int cedula);

#endif