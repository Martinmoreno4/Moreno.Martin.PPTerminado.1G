#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "servicio.h"
#include "biblioteca.h"

/** \brief
 *
 * \param servicio eServicio
 * \return void
 *
 */
void mostrarServicio(eServicio servicio)
{
    printf("  %d    %12s        %d $\n", servicio.id, servicio.descripcion, servicio.precio);
}

/** \brief
 *
 * \param servicios[] eServicio
 * \param tamS int
 * \return int
 *
 */
int mostrarServicios(eServicio servicios[], int tamS)
{
    int error = 1;
    if( servicios != NULL && tamS >0)
    {
        printf("        Listado de Servicios        \n");
        printf("--------------------------------------\n");
        printf("   id        Descripcion:     precio\n");
        printf("--------------------------------------\n");
        for(int i =0; i < tamS; i++)
        {
            mostrarServicio(servicios[i]);
        }
        printf("\n\n");
        error = 0;
    }
    return error;
}

/** \brief
 *
 * \param servicios[] eServicio
 * \param tam int
 * \param id int
 * \param descripcion[] char
 * \return int
 *
 */
int obtenerDescripcionServicio(eServicio servicios[], int tam, int id, char descripcion[])
{
    int error = 1;
    if(servicios !=NULL && tam > 0 && id >= 1000 && descripcion!=NULL)
    {
        for(int i=0; i < tam; i++)
        {
            if(servicios[i].id == id)
            {
                strcpy(descripcion, servicios[i].descripcion);
                error=0;
                break;
            }
        }
    }
    return error;
}

/** \brief
 *
 * \param servicios[] eServicio
 * \param tam int
 * \param id int
 * \return int
 *
 */
int validarIdServicio(eServicio servicios[], int tam, int id)
{
    int esValido = 0;

    if( servicios != NULL && tam >0 && id >= 1000)
    {
        for(int i=0; i<tam; i++)
        {
            if(servicios[i].id == id)
            {
                esValido = 1;
                break;
            }
        }

    }

    return esValido;
}

/** \brief recibe un id y devuelve el precio del servicio correspondiente
 *
 * \param servicios[] eServicio
 * \param tam int
 * \param id int
 * \return int
 *
 */
int obtenerPrecioServicio(eServicio servicios[], int tam, int id)
{
    int precio = 0;
    if(servicios !=NULL && tam > 0 && id >= 1000 )
    {
        for(int i=0; i < tam; i++)
        {
            if(servicios[i].id == id)
            {
                precio=servicios[i].precio;
                break;
            }
        }
    }
    return precio;
}

