#ifndef VUELOS_H
#define VUELOS_H

#define MAX_VUELOS 100

typedef struct Vuelo {
    int nroVuelo;
    char origen[50];
    char destino[50];
    char matricula[20];
    char piloto[50];
    char hora[6];     // HH:MM
    char fecha[11];   // DD/MM/YYYY
    int estado;       // 0: programado, 1: realizado
} Vuelo;

void cargarVuelos(Vuelo *vuelos, int *cantidad);
void guardarVuelos(Vuelo *vuelos, int cantidad);
void adicionarVuelo(Vuelo *vuelos, int *cantidad);
void listarVuelosProgramados(Vuelo *vuelos, int cantidad);
void listarVuelosRealizados(Vuelo *vuelos, int cantidad);
int buscarVuelo(Vuelo *vuelos, int cantidad, int nroVuelo);
void marcarVueloRealizado(Vuelo *vuelos, int cantidad);

#endif
