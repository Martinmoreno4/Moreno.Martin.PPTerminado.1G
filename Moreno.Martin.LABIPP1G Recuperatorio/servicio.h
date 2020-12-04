#ifndef SERVICIO_H_INCLUDED
#define SERVICIO_H_INCLUDED

typedef struct
{
    int id;
    char descripcion[25];
    int precio;
}eServicio;

void mostrarServicio(eServicio servicio);
int mostrarServicios(eServicio servicios[], int tamS);
int obtenerDescripcionServicio(eServicio servicios[], int tam, int id, char descripcion[]);
int obtenerPrecioServicio(eServicio servicios[], int tam, int id);
int validarIdServicio(eServicio servicios[], int tam, int id);
#endif // SERVICIO_H_INCLUDED


