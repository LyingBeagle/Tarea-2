#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "hashmap.h"

typedef struct Turista Turista;
typedef struct PuntoInteres PuntoInteres;

/*
    Menu para mostrar las opciones al usuario
*/

void menu();

/*
    Todo el proceso que se realizara despues que el usuario haya elegido una
   opcion
*/

void proceso(HashMap *, HashMap *, HashMap *, HashMap *, int);

/*
    Se registra a un punto de interes y se agrega a su mapa y a un mapa para el
   tipo que tiene
*/

void registrarPuntoInteres(HashMap *, HashMap *);

/*
    Se muestran los datos de un punto de interes, si no existe se manda un aviso
*/

void mostrarDatosPuntoInteres(HashMap *);

/*
    Se elimina un punto de interes
*/

void eliminarPuntoInteres(HashMap *,HashMap*);

/*
    Se piden los datos al usuario y se guardan en el punto de interes
*/

void pedirDatosPuntoInteres(PuntoInteres *);

/*
    Se registra a un turista
*/

void registrarTurista(HashMap *, HashMap *);

/*
    Se añade un lugar favorito al turista
*/

void agregarLugarFavoritoTurista(HashMap *);

/*
    Se muestran a los turistas del pais ingresado por el usuario
*/

void mostrarTuristasPorPais(HashMap *);

/*
    Se muestran los puntos de interes del tipo ingresado por el usuario
*/
void mostrarPuntosInteresTipo(HashMap *);

/*
    Se piden los datos del turista y se guardan
*/

void pedirDatosTurista(Turista *);

/*
    Se guarda al turista al mapa de pais
*/

void registrarTuristaPorPais(HashMap *, Turista *);

/*
    Se registra al punto de interes segun su tipo
*/

void registrarPuntoInteresTipo(HashMap *, PuntoInteres *);

/*
    Se muestran los lugares favoritos del turista
*/

void mostrarLugaresFavoristos(Turista *);

/*
    Se libera la memoria de los mapas
*/

void freeMap(HashMap *);

/*
    Se importa CSV a los mapas
*/

void importarCSV(HashMap *, HashMap *, HashMap *, HashMap *);

/*
    Se importan los puntos de interes
*/

void importarPuntosInteres(HashMap *, HashMap *);

/*
    Se importan los turistas
*/

void importarTuristas(HashMap *, HashMap *);

/*
    Se exporta los mapas a CSV
*/

void exportarCSV(HashMap *, HashMap *);

/*
    Se exporta los puntos turisticos
*/
void exportarPuntosInteres(HashMap *);

/*
    Se exportan los turistas
*/

void exportarTuristas(HashMap *);

#endif