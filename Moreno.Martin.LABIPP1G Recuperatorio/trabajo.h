#ifndef TRABAJO_H_INCLUDED
#define TRABAJO_H_INCLUDED
#include "fecha.h"
#include "auto.h"
#include "marca.h"
#include "color.h"
#include "servicio.h"

typedef struct
{
    int id;
    char patenteAuto[8];
    int idServicio;
    int isEmpty;
    eFecha fecha;
}eTrabajo;

#endif // TRABAJO_H_INCLUDED

int inicializarTrabajo(eTrabajo trabajos[], int tam);
void mostrarTrabajo(eTrabajo trabajo, eAuto autos[], int tamA, eServicio servicios[], int tamS);
int mostrarTrabajos(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eServicio servicios[], int tamS);
int buscarLibreTrabajo(eTrabajo trabajos[], int tam);
int altaTrabajo(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eServicio servicios[], int tamS, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL, int id);
int hardcodearTrabajos(eTrabajo trabajo[], int tamT, int cantidad);

int mostrarTrabajosPorAuto(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL,  eServicio servicios[], int tamS);
int mostrarImportePorAuto(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL,  eServicio servicios[], int tamS);
int mostrarAutoPorServicio(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL,  eServicio servicios[], int tamS);
int mostrarServicioPorFecha(eTrabajo trabajos[], int tamT, eServicio servicios[], int tamS);
//int hardcodearAutos(eAuto autos[], int tam, int cantidad);
