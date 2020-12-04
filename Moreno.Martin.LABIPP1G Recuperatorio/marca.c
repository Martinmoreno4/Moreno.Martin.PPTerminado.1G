#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "marca.h"


/** \brief
 *
 * \param marca eMarca
 * \return void
 *
 */
void mostrarMarca(eMarca marca)
{
    printf("  %d    %s\n", marca.id, marca.descripcion);
}

int mostrarMarcas(eMarca marcas[], int tamM)
{
    int error = 1;
    if( marcas != NULL && tamM >0)
    {
        printf("       Listado de Marcas      \n");
        printf("------------------------------\n");
        printf("   id        Descripcion\n");
        for(int i =0; i < tamM; i++)
        {
            mostrarMarca(marcas[i]);
        }
        printf("\n\n");
        error = 0;
    }
    return error;
}


/** \brief
 *
 * \param marcas[] eMarca
 * \param tamM int
 * \param id int
 * \return int
 *
 */
int validarIdMarca(eMarca marcas[], int tamM, int id)
{
    int esValido = 0;

    if( marcas != NULL && tamM >0 && id >= 1000)
    {
        for(int i=0; i<tamM; i++)
        {
            if(marcas[i].id == id)
            {
                esValido = 1;
                break;
            }
        }

    }

    return esValido;
}
