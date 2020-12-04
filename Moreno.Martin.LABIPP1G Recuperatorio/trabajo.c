#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "trabajo.h"
#include "fecha.h"
#include "auto.h"
#include "servicio.h"
#include "datastoreTrabajo.h"
#include "biblioteca.h"


/** \brief
 *
 * \param trabajos[] eTrabajo
 * \param tam int
 * \return int
 *
 */
int inicializarTrabajo(eTrabajo trabajos[], int tam)
{
    int error = 1;

    if( trabajos != NULL && tam > 0)
    {
        for(int i=0; i < tam; i++)
        {
            trabajos[i].isEmpty = 1;
        }
        error=0;
    }

    return error;
}


/** \brief
 *
 * \param trabajo eTrabajo
 * \param autos[] eAuto
 * \param tamA int
 * \param servicios[] eServicio
 * \param tamS int
 * \return void
 *
 */
void mostrarTrabajo(eTrabajo trabajo, eAuto autos[], int tamA, eServicio servicios[], int tamS)
{
    char descServicio[20];

    if(!obtenerDescripcionServicio(servicios, tamS, trabajo.idServicio, descServicio)
       && validarPatente(trabajo.patenteAuto) && verSiExistePatente(autos, tamA, trabajo.patenteAuto))
    {
        printf(" %4d  %10s   %10s    %2d/%2d/%4d\n",
           trabajo.id,
           trabajo.patenteAuto,
           descServicio,
           trabajo.fecha.dia,
           trabajo.fecha.mes,
           trabajo.fecha.anio
           );
    }
    else
    {
        printf("problema al obtener datos\n\n");
    }
}


/** \brief
 *
 * \param trabajos[] eTrabajo
 * \param tamT int
 * \param autos[] eAuto
 * \param tamA int
 * \param servicios[] eServicio
 * \param tamS int
 * \return int
 *
 */
int mostrarTrabajos(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eServicio servicios[], int tamS)
{
    int flag = 0;
    int error = 1;

    if(autos != NULL && tamA >0 && trabajos != NULL && tamT >0 && servicios != NULL && tamS >0)
    {
        system("cls");
        printf(" id      Patente     Servicio     Fecha\n");
        printf("---------------------------------------\n");

        for(int i= 0; i < tamT; i++)
        {
            if(trabajos[i].isEmpty == 0)
            {
                mostrarTrabajo(trabajos[i], autos, tamA, servicios, tamS);
                flag = 1;
            }
        }
        if( flag == 0)
        {
            printf("       No hay trabajos en la lista\n");
        }
        printf("\n\n");

        error = 0;
    }

    return error;
}


/** \brief
 *
 * \param trabajos[] eTrabajo
 * \param tam int
 * \return int
 *
 */
int buscarLibreTrabajo(eTrabajo trabajos[], int tam)
{
    int indice = -1;

    for(int i=0; i < tam; i++)
    {
        if(trabajos[i].isEmpty == 1)
        {
            indice = i;
            break;
        }
    }
    return indice;
}


/** \brief
 *
 * \param trabajos[] eTrabajo
 * \param tamT int
 * \param autos[] eAuto
 * \param tamA int
 * \param servicios[] eServicio
 * \param tamS int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \param id int
 * \return int
 *
 */
int altaTrabajo(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eServicio servicios[], int tamS, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL, int id)
{
    int error = 1;
    int indice;
    int auxIdServicio;
    char auxPatente[7];
    eTrabajo nuevoTrabajo;

    if( trabajos != NULL && tamT > 0 && autos != NULL && tamA > 0 && servicios != NULL && tamS > 0 && id > 0 )
    {
        system("cls");
        printf("***Alta Trbajo***\n\n");

        indice = buscarLibreTrabajo(trabajos, tamT);

        if( indice == -1)
        {
            printf("No hay lugar libre para otro trabajo\n");
        }
        else
        {
            nuevoTrabajo.id=id;
            nuevoTrabajo.isEmpty = 0;

            mostrarAutos(autos, tamA, marcas, tamM, colores, tamC, clientes, tamCL);
            printf("ingrese patente del auto: ");
            fflush(stdin);
            scanf("%s", auxPatente);
            while( verSiExistePatente(autos, tamA, auxPatente)==0)
            {
                printf("no existe la patente. reingrese patente: ");
                scanf("%s", auxPatente);
            }
            strcpy(nuevoTrabajo.patenteAuto, auxPatente);

            mostrarServicios(servicios, tamS);
            printf("ingrese id servicio: ");
            fflush(stdin);
            scanf("%d", &auxIdServicio);
            while( validarIdServicio(servicios, tamS, auxIdServicio)==0)
            {
                printf("id invalido. reingrese id: ");
                scanf("%d", &auxIdServicio);
            }
            nuevoTrabajo.idServicio = auxIdServicio;

            printf("ingrese fecha dd/mm/aaaa: ");
            scanf("%d/%d/%d", &nuevoTrabajo.fecha.dia, &nuevoTrabajo.fecha.mes, &nuevoTrabajo.fecha.anio);

            trabajos[indice] = nuevoTrabajo;
            error = 0;
        }
    }

    return error;
}

/** \brief hardcodea datos preestablecidos en una estructura trabajo
 *
 * \param eTrabajo[]
 * \param tamT int
 * \param cantidad int
 * \return int
 *
 */
int hardcodearTrabajos(eTrabajo trabajo[], int tamT, int cantidad)
{
    int error = -1;
    if( trabajo != NULL && tamT > 0 && cantidad >= 0 && cantidad <= tamT)
    {
        error = 0;
        for(int i=0; i < cantidad; i++)
        {
            trabajo[i].id = idDataTrabajo[i];
            strcpy(trabajo[i].patenteAuto, patentesDataTrabajo[i]);
            trabajo[i].idServicio = idServicioDataTrabajo[i];
            trabajo[i].fecha.dia=diasTrabajo[i];
            trabajo[i].fecha.mes=mesesTrabajo[i];
            trabajo[i].fecha.anio=aniosTrabajo[i];
            trabajo[i].isEmpty = 0;
            error++;
        }
    }
    return error;
}


/** \brief Pide un auto y muestra todos los trabajos que se le hicieron al mismo.
 *
 * \param trabajos[] eTrabajo
 * \param tamT int
 * \param autos[] eAuto
 * \param tamA int
 * \param servicios[] eServicio
 * \param tamS int
 * \return int
 *
 */
int mostrarTrabajosPorAuto(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL,  eServicio servicios[], int tamS)
{
    char patente[8];
    int indice=0;
    int error=0;
    int auxPatenteValido=0;
    int flag=0;
    if(autos!=NULL && tamA>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0 && clientes!=NULL && tamCL>0)
    {
        system("cls");
        printf("  *** mostrar trabajo por Auto ***  \n\n");
        mostrarAutos(autos, tamA, marcas, tamM, colores, tamC, clientes, tamCL);

        getStringAlfaNumerico("ingrese la patente: ",patente);
        auxPatenteValido = validarPatente(patente);
        while(!auxPatenteValido)
        {
            getStringAlfaNumerico("la patente debe ser alfa numeria y contener solo 7 caracteres\n por favor intente ingresar otra vez: ",patente);
            auxPatenteValido = validarPatente(patente);
        }

        indice = buscarAuto(autos, tamA, patente);

        if( indice == -1)
        {
            printf("no existe un auto con esa patente\n\n");
        }
        else
        {
            for(int i=0; i<tamT; i++)
            {
                if(strcmp(trabajos[i].patenteAuto,patente)==0)
                {
                    mostrarTrabajo(trabajos[i],autos,tamA,servicios,tamS);
                    flag=1;
                }
            }
            error=1;
            if(flag==0)
            {
                printf("no recibio ningun trabajo este auto\n\n");
                error=0;
            }

        }
    }
    return error;
}

/** \brief muestra el importe total pagado en servicios en un auto seleccionado
 *
 * \param trabajos[] eTrabajo
 * \param tamT int
 * \param autos[] eAuto
 * \param tamA int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \param clientes[] eCliente
 * \param tamCL int
 * \param servicios[] eServicio
 * \param tamS int
 * \return int
 *
 */
int mostrarImportePorAuto(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL,  eServicio servicios[], int tamS)
{
    char patente[8];
    int indice=0;
    int auxPatenteValido=0;
    int flag=0;
    int acumuladorPrecio=0;
    if(autos!=NULL && tamA>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0 && clientes!=NULL && tamCL>0)
    {
        system("cls");
        printf("  *** mostrar trabajo por Auto ***  \n\n");
        mostrarAutos(autos, tamA, marcas, tamM, colores, tamC, clientes, tamCL);

        getStringAlfaNumerico("ingrese la patente: ",patente);
        auxPatenteValido = validarPatente(patente);
        while(!auxPatenteValido)
        {
            getStringAlfaNumerico("la patente debe ser alfa numeria y contener solo 7 caracteres\n por favor intente ingresar otra vez: ",patente);
            auxPatenteValido = validarPatente(patente);
        }

        indice = buscarAuto(autos, tamA, patente);

        if( indice == -1)
        {
            printf("no existe un auto con esa patente\n\n");
        }
        else
        {
            for(int i=0; i<tamT; i++)
            {
                if(strcmp(trabajos[i].patenteAuto,patente)==0)
                {
                    acumuladorPrecio += obtenerPrecioServicio(servicios, tamS, trabajos[i].idServicio);
                    flag=1;
                }
            }
            if(flag==0)
            {
                printf("no recibio ningun trabajo este auto\n\n");
            }

        }
    }
    return acumuladorPrecio;
}

/** \brief se muestran los autos que recibieron un serficio especificado y la fecha en la que se hicieron los mismos
 *
 * \param trabajos[] eTrabajo
 * \param tamT int
 * \param autos[] eAuto
 * \param tamA int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \param clientes[] eCliente
 * \param tamCL int
 * \param servicios[] eServicio
 * \param tamS int
 * \return int
 *
 */
int mostrarAutoPorServicio(eTrabajo trabajos[], int tamT, eAuto autos[], int tamA, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL,  eServicio servicios[], int tamS)
{
    int error=0;
    int idServicioAux=0;
    int indiceAutoAux=0;

    mostrarServicios(servicios, tamS);
    idServicioAux=getInt("ingrese id de servicio");
    if(autos!=NULL && tamA>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0 && clientes!=NULL && tamCL>0)
    {
        while(!validarIdServicio(servicios, tamS, idServicioAux))
        {
            idServicioAux=getInt("id invalido, ingrese id de servicio");
        }

        for(int i=0; i<tamT;i++)
        {
            if(trabajos[i].idServicio==idServicioAux)
            {
                indiceAutoAux=buscarAuto(autos, tamA, trabajos[i].patenteAuto);
                mostrarAuto(autos[indiceAutoAux], marcas, colores, clientes, tamM, tamC, tamCL);
                mostrarFecha(trabajos[i].fecha);
            }
        }
        error=1;
    }
    return error;
}

int mostrarServicioPorFecha(eTrabajo trabajos[], int tamT, eServicio servicios[], int tamS)
{
    int error=0;
    int diaAux=0;
    int mesAux=0;
    int anioAux=0;
    char descripcionServicioAux[20];

    if(trabajos!=NULL && tamT>0 && servicios!=NULL && tamS>0)
    {
        diaAux=getInt("ingrese el dia: ");
        mesAux=getInt("ingrese el mes: ");
        anioAux=getInt("ingrese el anio: ");
        for(int i=0; i<tamT;i++)
        {
            if(trabajos[i].fecha.dia==diaAux && trabajos[i].fecha.mes==mesAux && trabajos[i].fecha.anio==anioAux)
            {
                if(!obtenerDescripcionServicio(servicios, tamS, trabajos[i].idServicio, descripcionServicioAux))
                {
                    printf("%s",descripcionServicioAux);
                    error=1;
                }

            }
        }
    }

    return error;
}
