#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cliente.h"
#include "color.h"
#include "marca.h"
#include "auto.h"

void mostrarCliente(eCliente clientes)
{
    printf("  %d    %s   %c\n", clientes.id, clientes.nombre, clientes.sexo);
}

/** \brief
 *
 * \param clientes[] eCliente
 * \param tamCL int
 * \return int
 *
 */
int mostrarClientes(eCliente clientes[], int tamCL)
{
    int error = 1;
    if( clientes != NULL && tamCL >0)
    {
        printf("      Listado de Clientes      \n");
        printf("------------------------------\n");
        printf("   id        Nombre    Sexo\n");
        for(int i =0; i < tamCL; i++)
        {
            mostrarCliente(clientes[i]);
        }
        printf("\n\n");
        error = 0;
    }
    return error;
}


/** \brief
 *
 * \param clientes[] eCliente
 * \param tamCL int
 * \param id int
 * \return int
 *
 */
int validarIdClientes(eCliente clientes[], int tamCL, int id)
{
    int esValido = 0;

    if( clientes != NULL && tamCL >0 && id >= 3000)
    {
        for(int i=0; i<tamCL; i++)
        {
            if(clientes[i].id == id)
            {
                esValido = 1;
                break;
            }
        }
    }
    return esValido;
}


/** \brief
 *
 * \param clientes[] eCliente
 * \param tamCL int
 * \param id int
 * \param descricpion[] char
 * \return int
 *
 */
int obtenerNombreCliente(eCliente clientes[], int tamCL, int id, char nombre[])
{
    int error = 1;
    if(clientes !=NULL && tamCL > 0 && id >= 3000 && nombre!=NULL)
    {
        for(int i=0; i < tamCL; i++)
        {
            if(clientes[i].id == id)
            {

                strcpy(nombre, clientes[i].nombre);
                error=0;
                break;
            }
        }
    }
    return error;
}
