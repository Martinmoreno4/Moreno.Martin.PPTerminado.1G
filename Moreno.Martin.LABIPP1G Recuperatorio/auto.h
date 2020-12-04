#ifndef AUTO_H_INCLUDED
#define AUTO_H_INCLUDED
#include "color.h"
#include "marca.h"
#include "cliente.h"


#define ASC 1
#define DESC 0

typedef struct
{
    int id;
    char patente[8];
    int idMarca;
    int idColor;
    int modelo;
    int isEmpty;
    int idCliente;
}eAuto;

#endif // AUTO_H_INCLUDED

int inicializarAuto(eAuto autos[], int tam);

void mostrarAuto(eAuto unAuto, eMarca marcas[], eColor colores[], eCliente clientes[], int tamM, int tamC, int tamCL);
int mostrarAutos(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL);
int modificarAuto(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[],int tamCL);
int altaAuto(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL, int id);
int bajaAuto(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL);
int buscarAuto(eAuto autos[], int tam, char patente[]);
int ordenarAutosXMarcaPatente(eAuto autos[], int tam, int criterioM, int criterioP);

int mostrarAutosSeparadosXMarca(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL);

int verSiExistePatente(eAuto autos[], int tam, char patente[]);
int validarPatente(char patente[]);

int obtenerPatenteAuto(eAuto autos[], int tam, int id, char patente[]);
int obtenerDescripcionMarca(eMarca marcas[], int tam, int id, char descripcion[]);

int hardcodearAutos(eAuto autos[], int tam, int cantidad);
int mostrarColorSeleccionado(eColor colores[], int tamC, eAuto autos[], int tamA, eMarca marcas[],int tamM, eCliente clientes[], int tamCL);
int mostrarMarcaSeleccionada(eColor colores[], int tamC, eAuto autos[], int tamA, eMarca marcas[], int tamM, eCliente clientes[], int tamCL);

int autosMasViejo(eAuto autos[], int tam);
int mostrarAutosMasViejos(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL);

int marcaMasUsada(eAuto autos[], int tam, eMarca marcas[], int tamM);
int contarColoresYMarcas(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL);
/*int listaDeAutosXMarca(eAuto autos[], int tam, eMarca marcas[], int tamM);*/
