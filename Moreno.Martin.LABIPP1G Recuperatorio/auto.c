#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "auto.h"
#include "datastore.h"
#include "marca.h"
#include "color.h"
#include "biblioteca.h"


/** \brief inicializa una estructura cambiando los valores de isEmpty de los arrays a 1
 *
 * \param autos[] eAuto
 * \param tam int
 * \return int devuelve 1 si los parametros ingresados no eran correctos, 0 si todo funciono
 *
 */
int inicializarAuto(eAuto autos[], int tam)
{
    int error = 1;

    if( autos != NULL && tam > 0)
    {
        for(int i=0; i < tam; i++)
        {
            autos[i].isEmpty = 1;
        }
        error=0;
    }

    return error;
}


/** \brief imprime todos los valores de un array de la estructura, necesita validar los datos de marca y color para mostrarlos
 *
 * \param unAuto eAuto
 * \param marcas[] eMarca
 * \param colores[] eColor
 * \param tamM int
 * \param tamC int
 * \return void
 *
 */
void mostrarAuto(eAuto unAuto, eMarca marcas[], eColor colores[], eCliente clientes[], int tamM, int tamC, int tamCL)
{
    char descMarca[20];
    char descColor[20];
    char auxNombre[20];
    if(obtenerDescripcionMarca(marcas, tamM, unAuto.idMarca, descMarca)==0 &&
       obtenerDescripcionColor(colores, tamC, unAuto.idColor, descColor)==0 &&
       obtenerNombreCliente(clientes, tamCL, unAuto.idCliente, auxNombre)==0 &&
       validarPatente(unAuto.patente)==1)
    {
        printf(" %8d  %6s   %10s   %6s   %10s  %4d\n",
           unAuto.id,
           unAuto.patente,
           descMarca,
           descColor,
           auxNombre,
           unAuto.modelo
           );
    }else
    {
        printf("problema al obtener descripcion de la marca, el nombre del cliente y/o el color del auto\n\n");
    }
}


/** \brief muestra todos los arrays dentro de la estructura
 *
 * \param autos[] eAuto
 * \param tam int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \return int
 *
 */
int mostrarAutos(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL)
{
    int flag = 0;
    int error = 1;

    if(autos!=NULL && tam>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0 && clientes!=NULL && tamCL>0)
    {

        printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
        printf("---------------------------------------------------------------\n");

        for(int i= 0; i < tam; i++)
        {
            if(autos[i].isEmpty == 0)
            {
                mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                flag = 1;
            }
        }
        if( flag == 0)
        {
            printf("No hay autos que mostrar\n");
        }
        printf("\n\n");

        error = 0;
    }


    return error;
}


/** \brief busca el primer lugar libre en la lista
 *
 * \param autos[] eAuto
 * \param tam int
 * \return int devuelve el primer indice libre en la lista
 *
 */
int buscarLibre(eAuto autos[], int tam)
{
    int indice = -1;
    for(int i=0; i < tam; i++)
    {
        if(autos[i].isEmpty == 1)
        {
            indice = i;
            break;
        }
    }
    return indice;
}

/** \brief la funcion logra el alta de un auto
 *
 * \param autos[] eAuto
 * \param tam int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \param id int
 * \return int 0 si funcion, o 1 si no funciono
 *
 */
int altaAuto(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL, int id)
{
    int error = 1;
    int indice;
    int auxIdMarca=0;
    int auxIdColor=0;
    int auxModelo=0;
    int validoPatente=0;
    eAuto nuevaAuto;

    if(autos!=NULL && tam>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0 && clientes!=NULL && tamCL>0 && id>0)
    {
        system("cls");
        printf("***Alta de Auto***\n\n");
        indice = buscarLibre(autos, tam);

        if( indice == -1)
        {
            printf("el sistema esta completo\n");
        }
        else
        {
            nuevaAuto.id=id;
            nuevaAuto.isEmpty = 0;
            getStringAlfaNumerico("ingrese patente: ", nuevaAuto.patente);
            validoPatente=validarPatente(nuevaAuto.patente);
            while(!validoPatente)
            {
                getStringAlfaNumerico("La patente debe ser alfanumerica y tener 7 caracteres,\nlos primeros 3 deben ser letras, y los ultimos 4 deben ser numeros\n ingrese patente: ", nuevaAuto.patente);
                validoPatente=validarPatente(nuevaAuto.patente);
            }

            mostrarColores(colores, tamC);
            printf("ingrese id de color: ");
            scanf("%d", &auxIdColor);

            while( validarIdColor(colores, tamC, auxIdColor)==0)
            {
                printf("id invalido. reingrese id color: \n");
                fflush(stdin);
                scanf("%d", &auxIdColor);
            }
            nuevaAuto.idColor = auxIdColor;

            mostrarMarcas(marcas, tamM);
            printf("ingrese id de marca: ");
            fflush(stdin);
            scanf("%d", &auxIdMarca);

            while( validarIdMarca(marcas, tamM, auxIdMarca)==0)
            {
                printf("id invalido. reingrese id marca: ");
                fflush(stdin);
                scanf("%d", &auxIdMarca);
            }
            nuevaAuto.idMarca = auxIdMarca;

            auxModelo=getInt("ingese nuevo anio de modelo\n");
            while( auxModelo<=1950 || auxModelo>=2020)
            {
                auxModelo=getInt("Modelo invalido, debe ser mayor 1949 y menor a 2021. reingrese modelo: \n");
            }
            nuevaAuto.modelo=auxModelo;

            autos[indice] = nuevaAuto;
            error = 0;
        }
    }

    return error;
}


/** \brief encuentra un auto en la lista si alguno tiene la patente ingresada
 *
 * \param autos[] eAuto
 * \param tam int
 * \param patente[] char
 * \return int devuele el indice del auto con la patente ingresada, o NULL si la patente no esta en la lista
 *
 */
int buscarAuto(eAuto autos[], int tam, char patente[])
{
    int indice = -1;

    for(int i=0; i < tam; i++)
    {
        if(strcmp(autos[i].patente,patente)==0 && autos[i].isEmpty == 0)
        {
            indice = i;
            break;
        }
    }

    return indice;
}


/** \brief da de baja uno de los autos en la lista, el cual se debe indicar a partir de su patente
 *
 * \param autos[] eAuto
 * \param tam int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \return int 1 si funciono la baja, 0 si no funciono, y 2 si se elijio cancelar la baja
 *
 */
int bajaAuto(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL)
{
    int error = 1;
    char patente[8];
    int auxPatenteValido;
    int indice;
    char confirma;

    if(autos!=NULL && tam>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0 && clientes!=NULL && tamCL>0)
    {
        system("cls");
        printf("      Baja de auto     \n\n");
        mostrarAutos(autos, tam, marcas, tamM, colores, tamC, clientes, tamCL);
        getStringAlfaNumerico("ingrese la patente: ",patente);
        auxPatenteValido = validarPatente(patente);
        while(!auxPatenteValido)
        {
            getStringAlfaNumerico("la patente debe ser alfa numeria y contener solo 7 caracteres\n por favor intente ingresar otra vez: ",patente);
            auxPatenteValido = validarPatente(patente);
        }

        indice = buscarAuto(autos, tam, patente);

        if( indice == -1)
        {
            printf("no existe un auto con ese patente\n\n");
        }
        else
        {
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");
            mostrarAuto(autos[indice], marcas, colores, clientes, tamM, tamC, tamCL);
            printf("Confirma borrado: ");
            fflush(stdin);
            scanf("%c", &confirma);
            if(confirma == 's')
            {
                autos[indice].isEmpty = 1;
                error = 0;
            }
            else
            {
                error = 2;
            }
        }
    }
    return error;
}


/** \brief apartir de la id ingresada, guarda el valor "descripcion" correspondiente en la descripcion ingresada
 *
 * \param marcas[] eMarca
 * \param tam int
 * \param id int
 * \param descripcion[] char
 * \return int
 *
 */
int obtenerDescripcionMarca(eMarca marcas[], int tam, int id, char descripcion[])
{
    int error = 1;
    if(marcas !=NULL && tam > 0 && id >= 1000 && descripcion!=NULL)
    {
        for(int i=0; i < tam; i++)
        {
            if(marcas[i].id == id)
            {
                strcpy(descripcion, marcas[i].descripcion);
                error=0;
                break;
            }
        }
    }
    return error;
}


/** \brief ordena los autos por marca, y en caso de tener la misma marca los ordena por patente
 *
 * \param autos[] eAuto
 * \param tam int
 * \param criterioM int
 * \param criterioP int
 * \return int
 *
 */
int ordenarAutosXMarcaPatente(eAuto autos[], int tam, int criterioM, int criterioP)
{
    int error = 1;
    eAuto auxAuto;

    if(autos != NULL && tam > 0 && criterioM >= 0 && criterioM <= 1 && criterioP >= 0 && criterioP <= 1)
    {
        for(int i=0; i < tam -1; i++)
        {
            for(int j=i +1; j<tam; j++)
            {
                if( autos[i].idMarca > autos[j].idMarca && criterioM)
                {
                    auxAuto = autos[i];
                    autos[i] = autos[j];
                    autos[j] = auxAuto;
                }
                else if ( autos[i].idMarca < autos[j].idMarca && !criterioM)
                {
                    auxAuto = autos[i];
                    autos[i] = autos[j];
                    autos[j] = auxAuto;
                }
                else if(autos[i].idMarca == autos[j].idMarca && strcmp(autos[i].patente,autos[j].patente)>0 && criterioP)
                {
                    auxAuto = autos[i];
                    autos[i] = autos[j];
                    autos[j] = auxAuto;
                }
                else if(autos[i].idMarca == autos[j].idMarca && strcmp(autos[i].patente,autos[j].patente)<0 && !criterioP)
                {
                    auxAuto = autos[i];
                    autos[i] = autos[j];
                    autos[j] = auxAuto;
                }
            }
        }
    error = 0;
    }
    return error;
}


/** \brief permite modificar el color y el modelo del auto, requiere el ingreso de patente para encontrarlo en la lista
 *
 * \param autos[] eAuto
 * \param tam int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \return int
 *
 */
int modificarAuto(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[],int tamCL)
{
    int error = 1;
    char patente[8];
    int indice=0;
    char confirma;
    int auxIdColor=0;
    int auxModelo=0;
    int auxPatenteValido=0;


    if(autos!=NULL && tam>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0 && clientes!=NULL && tamCL>0)
    {
        system("cls");
        printf("  *** Modificar Auto ***  \n\n");
        mostrarAutos(autos, tam, marcas, tamM, colores, tamC, clientes, tamCL);

        getStringAlfaNumerico("ingrese la patente: ",patente);
        auxPatenteValido = validarPatente(patente);
        while(!auxPatenteValido)
        {
            getStringAlfaNumerico("la patente debe ser alfa numeria y contener solo 7 caracteres\n por favor intente ingresar otra vez: ",patente);
            auxPatenteValido = validarPatente(patente);
        }

        indice = buscarAuto(autos, tam, patente);

        if( indice == -1)
        {
            printf("no existe un auto con esa patente\n\n");
        }
        else
        {
            mostrarColores(colores, tamC);

            auxIdColor=getInt("ingese nuevo id de color\n");
            while( validarIdColor(colores, tamC, auxIdColor)==0)
            {
                printf("id invalida. reingrese id: ");
                scanf("%d", &auxIdColor);
            }

            mostrarAutos(autos, tam, marcas, tamM, colores, tamC, clientes, tamCL);

            auxModelo=getInt("ingese nuevo año de modelo\n");
            while( auxModelo<=1950 || auxModelo>=2020)
            {
                printf("Modelo invalido. reingrese modelo: ");
                scanf("%d", &auxModelo);
            }


            printf("Confirme cambio: ");
            fflush(stdin);
            scanf("%c", &confirma);
            if(confirma == 's')
            {
                autos[indice].idColor = auxIdColor;
                autos[indice].modelo = auxModelo;
                error = 0;
            }
            else
            {
                error = 2;
            }
        }
    }
    return error;
}


/** \brief se fija si existe la patente en la lista
 *
 * \param autos[] eAuto
 * \param tam int
 * \param patente[] char
 * \return int 0 si la patente no se encuentra, y 1 si existe
 *
 */
int verSiExistePatente(eAuto autos[], int tam, char patente[])
{
    int existeEnLista = 0;

    if( autos != NULL && tam >0 )
    {
        for(int i=0; i<tam; i++)
        {
            if(strcmp(autos[i].patente,patente)==0)
            {
                existeEnLista = 1;
                break;
            }
        }
    }
    return existeEnLista;
}

/** \brief valida si la patente tiene 8 digitos
 *
 * \param autos[] eAuto
 * \return int
 *
 */
int validarPatente(char patente[])
{
    int esValido = 0;
    int len = strlen(patente);
    if( patente != NULL && len ==7)
    {
        esValido = 1;
        for(int i=0; i<7;i++)
        {
            if(i<3)
            {
                if((patente[i] < 'a' || patente[i] > 'z') && (patente[i] < 'A' || patente[i] > 'Z'))
                {
                    esValido = 0;
                    break;
                }
            }
            else if(i>2 && i<7)
            {
                if(patente[i] < '0' || patente[i] > '9')
                {
                    esValido = 0;
                    break;
                }
            }
        }
    }

    return esValido;
}

/** \brief a partir del id ingresado ingresa los datos del patente correspondiente a un string vacio
 *
 * \param autos[] eAuto
 * \param tam int
 * \param id int
 * \param patente[] char
 * \return int 1 si no se logro, 0 si se pudo obtener
 *
 */
int obtenerPatenteAuto(eAuto autos[], int tam, int id, char patente[])
{
    int error = 1;
    if(autos !=NULL && tam > 0 && patente!=NULL)
    {
        for(int i=0; i < tam; i++)
        {
            if(autos[i].id == id && autos[i].isEmpty == 0)
            {
                strcpy(patente, autos[i].patente);
                error=0;
                break;
            }
        }
    }
    return error;
}


/** \brief harcodea una serie de datos ya escritos en la estructura ingresada
 *
 * \param autos[] eAuto
 * \param tam int
 * \param cantidad int
 * \return int devuelve -1 si no funciono, y la cantidad de autos harcodeados si funciono
 *
 */
int hardcodearAutos(eAuto autos[], int tam, int cantidad)
{
    int error = -1;
    if( autos != NULL && tam > 0 && cantidad >= 0 && cantidad <= tam)
    {
        error = 0;
        for(int i=0; i < cantidad; i++)
        {
            autos[i].id = idAutosData[i];
            strcpy(autos[i].patente, patentesData[i]);
            autos[i].idMarca = idMarcasData[i];
            autos[i].idColor = idColoresData[i];
            autos[i].idCliente = idClientesData[i];
            autos[i].modelo = modelosData[i];
            autos[i].isEmpty = 0;
            error++;
        }
    }
    return error;
}


/** \brief
 *
 * \param colores[] eColor
 * \param tamC int
 * \param autos[] eAuto
 * \param tamA int
 * \param marcas[] eMarca
 * \param tamM int
 * \return int
 *
 */
int mostrarColorSeleccionado(eColor colores[], int tamC, eAuto autos[], int tamA, eMarca marcas[], int tamM, eCliente clientes[], int tamCL)
{
    int error = 1;
    int flag = 0;
    char seguir = 's';
    int idSeleccion=0;
    int idColorNegro = 5000;
    int idColorBlanco = 5001;
    int idColorGris = 5002;
    int idColorRojo = 5003;
    int idColorAzul = 5004;

    mostrarColores(colores, tamC);

    while(seguir == 's')
    {
        printf("ingrese id de color que desea buscar\n\n");
        scanf("%d", &idSeleccion);

        switch(idSeleccion)
        {
        case 5000:
            system("cls");
            printf("Autos de color Negro \n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idColor == idColorNegro)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de color Negro\n\n");
            }
            break;

        case 5001:
            system("cls");
            printf("Autos de color Blanco \n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idColor == idColorBlanco)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de color Blanco\n\n");
            }
            break;

        case 5002:
            system("cls");
            printf("Autos de color Gris \n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idColor == idColorGris)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de color Gris\n\n");
            }
            break;

        case 5003:
            system("cls");
            printf("Autos de color Rojo \n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idColor == idColorRojo)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de color Rojo\n\n");
            }
            break;

        case 5004:
            system("cls");
            printf("Autos de color Azul\n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idColor == idColorAzul)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de color Azul\n\n");
            }
            break;

        default:
            printf("id invalido\n\n");
            break;
        }

        printf("desea continuar?\n\n");
        scanf("%c", &seguir);
    }


    return error;
}


/** \brief
 *
 * \param colores[] eColor
 * \param tamC int
 * \param autos[] eAuto
 * \param tamA int
 * \param marcas[] eMarca
 * \param tamM int
 * \return int
 *
 */
int mostrarMarcaSeleccionada(eColor colores[], int tamC, eAuto autos[], int tamA, eMarca marcas[], int tamM, eCliente clientes[], int tamCL)
{
    int error = 1;
    int flag = 0;
    char seguir = 's';
    int idSeleccion=0;
    int idRenault = 1000;
    int idFiat = 1001;
    int idFord = 1002;
    int idChebrolet = 1003;
    int idPeugeot = 1004;

    mostrarMarcas(marcas, tamM);

    while(seguir == 's')
    {
        printf("ingrese id de marca que desea buscar\n\n");
        scanf("%d", &idSeleccion);

        switch(idSeleccion)
        {
        case 1000:
            system("cls");
            printf("Autos marca Renault \n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idMarca == idRenault)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de marca Renault\n\n");
            }
            break;

        case 1001:
            system("cls");
            printf("Autos de marca Fiat \n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idMarca == idFiat)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de marca Fiat\n\n");
            }
            break;

        case 1002:
            system("cls");
            printf("Autos de marca Ford \n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idMarca == idFord)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de marca Ford\n\n");
            }
            break;

        case 1003:
            system("cls");
            printf("Autos de marca Chevrolet \n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idMarca == idChebrolet)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de marca Chevrolet\n\n");
            }
            break;

        case 1004:
            system("cls");
            printf("Autos de marca Peugeot\n\n");
            printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
            printf("---------------------------------------------------------------\n");

            for(int i=0; i<tamA; i++)
            {
                if( autos[i].isEmpty == 0 && autos[i].idMarca == idPeugeot)
                {
                    mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    flag = 1;
                }
            }
            if( flag == 0)
            {
                printf("no hay autos de marca Peugeot\n\n");
            }
            break;

        default:
            printf("id invalido\n\n");
            break;
        }

        printf("desea continuar? (presione 's' para continuar)\n\n");
        scanf("%c", &seguir);
    }


    return error;
}


/** \brief encuentra el modelo mas viejo entre los que estan en la lista
 *
 * \param autos[] eAuto
 * \param tam int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \param clientes[] eCliente
 * \param tamCL int
 * \return int
 *
 */
int autosMasViejo(eAuto autos[], int tam)
{
    int flagPrimerValor=0;
    int modeloMasViejo=0;

    if(autos!=NULL && tam>0)
    {
        for(int i=0; i<tam; i++)
        {
            if(flagPrimerValor==0)
            {
                modeloMasViejo=autos[i].modelo;
                flagPrimerValor=1;
            }
            else if(autos[i].modelo<modeloMasViejo)
            {
                modeloMasViejo=autos[i].modelo;
            }
        }
    }

    return modeloMasViejo;
}

/** \brief muestra el, o los autos mas viejos
 *
 * \param autos[] eAuto
 * \param tam int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \param clientes[] eCliente
 * \param tamCL int
 * \return int
 *
 */
int mostrarAutosMasViejos(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL)
{
    int error=1;
    int modeloAux=0;
    if(autos!=NULL && tam>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0 && clientes!=NULL && tamCL>0)
    {
        modeloAux=autosMasViejo(autos, tam);
        system("cls");
        printf("Autos mas viejo/s\n\n");
        printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
        printf("---------------------------------------------------------------\n");
        for(int i=0;i<tam;i++)
        {
            if(autos[i].modelo==modeloAux)
            {
                mostrarAuto(autos[i], marcas, colores, clientes, tamM,  tamC,  tamCL);
            }
        }
        error=0;
    }

    return error;
}

/** \brief indica cual marca o marcas son las mas usadas en la estructura
 *
 * \param autos[] eAuto
 * \param tam int
 * \param marcas[] eMarca
 * \param tamM int
 * \return int
 *
 */
int marcaMasUsada(eAuto autos[], int tam, eMarca marcas[], int tamM)
{
    int error = 1;
    int mayor;
    int contadores[tamM];
    int flag = 0;

    for(int i =0; i < tamM; i++)
    {
        contadores[i] = 0;
    }

    if( autos != NULL && marcas != NULL && tam >0 && tamM > 0)
    {
        system("cls");
        printf("  *** Marca Mas comun ***  \n");

        for(int d=0; d < tamM; d++)
        {
            for(int i=0; i < tam; i++)
            {
                if(autos[i].isEmpty == 0 && autos[i].idMarca == marcas[d].id)
                {
                    contadores[d]++;
                }
            }
        }

        for(int i=0; i < tamM; i++)
        {
            if(contadores[i] > mayor || flag == 0)
            {
                mayor = contadores[i];
                flag=1;
            }
        }
        printf("La o las Marcas mas usadas son: \n\n");

        for(int d=0; d < tamM; d++)
        {
            if(contadores[d] == mayor)
            {
                printf("%s\n", marcas[d].descripcion );
            }
        }
        printf("\n\n");
        error = 0;
    }
    return error;
}

/** \brief se introduce un color y una marac, y luego se ceuntan cuantos autos hay que contengan ambos valores
 *
 * \param autos[] eAuto
 * \param tam int
 * \param marcas[] eMarca
 * \param tamM int
 * \param colores[] eColor
 * \param tamC int
 * \return int
 *
 */
int contarColoresYMarcas(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL)
{
    int error=0;
    int auxIdColor=0;
    int auxIdMarcas=0;
    int contador=0;

    if(autos!=NULL && tam>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0)
    {
        mostrarColores(colores, tamC);
        printf("ingrese id de color: ");
        scanf("%d", &auxIdColor);

        while( validarIdColor(colores, tamC, auxIdColor)==0)
        {
            printf("id invalido. reingrese id color: \n");
            fflush(stdin);
            scanf("%d", &auxIdColor);
        }

        mostrarMarcas(marcas, tamM);
        printf("ingrese id de color: ");
        scanf("%d", &auxIdMarcas);

        while( validarIdMarca(marcas, tamM, auxIdMarcas)==0)
        {
            printf("id invalido. reingrese id marca: \n");
            fflush(stdin);
            scanf("%d", &auxIdMarcas);
        }

        for(int i=0;i<tam;i++)
        {
            if(autos[i].idMarca==auxIdMarcas && autos[i].idColor==auxIdColor)
            {
                printf("\n\n");
                printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
                printf("---------------------------------------------------------------\n");
                mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                contador++;
            }
        }

        if(contador==0)
        {
            printf("no hay autos con esa combinacion de color y marca\n");
        }
        else
        {
            printf("\n hay %d auto/s con esa combinacion de color y marca\n", contador);
        }
    }
    return error;
}

int mostrarAutosSeparadosXMarca(eAuto autos[], int tam, eMarca marcas[], int tamM, eColor colores[], int tamC, eCliente clientes[], int tamCL)
{
    int flag = 0;
    int error = 1;

    if(autos!=NULL && tam>0 && marcas!=NULL && tamM>0 && colores!=NULL && tamC>0 && clientes!=NULL && tamCL>0)
    {

        printf("      Id   Patente       Marca     Color       Nombre  Modelo\n");
        printf("---------------------------------------------------------------\n");
        for(int m=0; m<tamM; m++)
        {
            if(marcas[m].id==1000)
            {
                printf("autos marca Renault:\n");
                for(int i=0;i<tam;i++)
                {
                    if(autos[i].idMarca==marcas[m].id)
                    {
                        mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    }
                }
            }
            else if(marcas[m].id==1001)
            {
                printf("autos marca Fiat:\n");
                for(int i=0;i<tam;i++)
                {
                    if(autos[i].idMarca==marcas[m].id)
                    {
                        mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    }
                }
            }
            else if(marcas[m].id==1002)
            {
                printf("autos marca Ford:\n");
                for(int i=0;i<tam;i++)
                {
                    if(autos[i].idMarca==marcas[m].id)
                    {
                        mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    }
                }
            }
            else if(marcas[m].id==1003)
            {
                printf("autos marca Chevrolet:\n");
                for(int i=0;i<tam;i++)
                {

                }
            }
            else if(marcas[m].id==1004)
            {
                printf("autos marca Peugeot:\n");
                for(int i=0;i<tam;i++)
                {
                    if(autos[i].idMarca==marcas[m].id)
                    {
                        mostrarAuto(autos[i], marcas, colores, clientes, tamM, tamC, tamCL);
                    }
                }
            }
            flag =1;
        }
        if( flag == 0)
        {
            printf("No hay autos que mostrar\n");
        }
        printf("\n\n");

        error = 0;
    }


    return error;
}
