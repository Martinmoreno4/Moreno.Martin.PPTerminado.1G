#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "color.h"
#include "marca.h"
#include "auto.h"


/** \brief muestra un color, su id y descripcion
 *
 * \param color eColor
 * \return void
 *
 */
void mostrarColor(eColor color)
{
    printf("  %d    %s\n", color.id, color.descripcion);
}


/** \brief muestra todos los colores en una estructura
 *
 * \param colores[] eColor
 * \param tamC int
 * \return int
 *
 */
int mostrarColores(eColor colores[], int tamC)
{
    int error = 1;
    if( colores != NULL && tamC >0)
    {
        printf("      Listado de Colores      \n");
        printf("------------------------------\n");
        printf("   id        Descripcion\n");
        for(int i =0; i < tamC; i++)
        {
            mostrarColor(colores[i]);
        }
        printf("\n\n");
        error = 0;
    }
    return error;
}


/** \brief valida el valor de id ingresado, si es que este se encuentra en la estructura ingresada
 *
 * \param colores[] eColor
 * \param tamC int
 * \param id int
 * \return int
 *
 */
int validarIdColor(eColor colores[], int tamC, int id)
{
    int esValido = 0;

    if( colores != NULL && tamC >0 && id >= 1000)
    {
        for(int i=0; i<tamC; i++)
        {
            if(colores[i].id == id)
            {
                esValido = 1;
                break;
            }
        }
    }
    return esValido;
}


/** \brief busca un color apartir de un id ingresado, y copia la descripcion indicada en un string
 *
 * \param colores[] eColor
 * \param tam int
 * \param id int
 * \param descripcion[] char
 * \return int
 *
 */
int obtenerDescripcionColor(eColor colores[], int tam, int id, char descripcion[])
{
    int error = 1;
    if(colores !=NULL && tam > 0 && id >= 1000 && descripcion!=NULL)
    {
        for(int i=0; i < tam; i++)
        {
            if(colores[i].id == id)
            {

                strcpy(descripcion, colores[i].descripcion);
                error=0;
                break;
            }
        }
    }
    return error;
}
