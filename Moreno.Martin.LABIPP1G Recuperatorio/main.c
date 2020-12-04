#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "marca.h"
#include "color.h"
#include "servicio.h"
#include "auto.h"
#include "trabajo.h"
#include "biblioteca.h"
#include "cliente.h"

#define TAM 10
#define TAM_M 5
#define TAM_C 5
#define TAM_S 4
#define TAM_CL 10
#define TAM_T 10

char menu();

int main()
{
    char seguir = 's';
    char confirma;
    int rta;
    int importe=0;
    int proximoIdAuto = 1000;
    //int proximoIdServicio = 1000;
    int proximoIdTrabajo = 1000;
    eAuto autos[TAM];

    eTrabajo trabajos[TAM_T];

    eMarca marcas[TAM_M]=
    {
        {1000, "Renault"},
        {1001, "Fiat"},
        {1002, "Ford"},
        {1003, "Chevrolet"},
        {1004, "Peugeot"},
    };

    eColor colores[TAM_C]=
    {
        {5000, "Negro"},
        {5001, "Blanco"},
        {5002, "Gris"},
        {5003, "Rojo"},
        {5004, "Azul"},
    };

    eServicio lavados[TAM_S]=
    {
        {20000, "Lavado:", 250},
        {20001, "Pulido:", 300},
        {20002, "Encerado:", 400},
        {20003, "Completo:", 600},
    };

    eCliente clientes[TAM_CL]=
    {
        {3000, "Martin", 'm'},
        {3001, "Ricardo", 'm'},
        {3002, "Maria", 'f'},
        {3003, "Juana", 'f'},
        {3004, "Alberto", 'm'},
        {3005, "ivan", 'm'},
        {3006, "maximo", 'm'},
        {3007, "veronica", 'f'},
        {3008, "marta", 'f'},
        {3009, "benito", 'm'}
    };

    if(inicializarAuto(autos, TAM)==0)
    {
        printf("autos inicializadas con exito\n");
    }
    else
    {
        printf("problema al inicializar\n");
    }

    proximoIdAuto += hardcodearAutos(autos, TAM, 8);
    proximoIdTrabajo += hardcodearTrabajos(trabajos, TAM_T, 8);

    do
    {
        switch(menu())
        {
        case 'a':

            if(altaAuto(autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL, proximoIdAuto)==0)
            {
                printf("alta exitosa\n\n");
                proximoIdAuto++;
            }
            else
            {
                printf("problemas con el alta\n\n");
            }

            break;

        case 'b':
            rta = modificarAuto(autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL);

            if( rta == 0)
            {
                printf("modificacion exitosa\n\n");
            }
            else if(rta ==2)
            {
                printf("modificacion cancelada\n\n");
            }
            else
            {
                printf("se a producido un error en la modificacion\n\n");
            }
            break;

        case 'c':
            rta = bajaAuto(autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL);

            if( rta == 0)
            {
                printf("Baja exitosa\n\n");
            }
            else if(rta ==2)
            {
                printf("Baja cancelada\n\n");
            }
            else
            {
                printf("se a producido un error en la Baja\n\n");
            }
            break;

        case 'd':
            system("cls");
            if(!ordenarAutosXMarcaPatente(autos, TAM, ASC, ASC))
            {
                mostrarAutos(autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL);
            }
            else
            {
                printf("problema al ordenar la lista\n\n");
            }
            break;

        case 'e':
            system("cls");
            mostrarMarcas(marcas, TAM_M);
            break;

        case 'f':
            system("cls");
            mostrarColores(colores, TAM_C);
            break;

        case 'g':
            system("cls");
            mostrarServicios(lavados, TAM_S);
            break;

        case 'h':
            system("cls");
            if(altaTrabajo(trabajos, TAM_T, autos, TAM, lavados, TAM_S, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL, proximoIdTrabajo)==0)
            {
                printf("alta exitosa\n\n");
            }
            else
            {
                printf("problemas con el alta\n\n");
            }
            break;

        case 'i':
            system("cls");
            mostrarTrabajos(trabajos, TAM_T, autos, TAM, lavados, TAM_S);
            if(0==0)
            {
                printf("\n\n");
            }
            else
            {
                printf("problemas con la lista de trabajos\n\n");
            }
            break;

        case 'j':
            system("cls");

            if(mostrarColorSeleccionado(colores, TAM_C, autos, TAM, marcas, TAM_M, clientes, TAM_CL))
            {
                printf("\n\n");
            }
            else
            {
                printf("problemas con la lista de colores\n\n");
            }
            break;

        case 'k':
            system("cls");
            if(mostrarMarcaSeleccionada(colores, TAM_C, autos, TAM, marcas, TAM_M, clientes, TAM_CL))
            {
                printf("\n\n");
            }
            else
            {
                printf("problemas con la lista de marcas\n\n");
            }
            break;

        case 'l':
            system("cls");
            if(!mostrarAutosMasViejos(autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL))
            {
                printf("\n\n");
            }
            else
            {
                printf("problemas con los modelos\n\n");
            }

            break;

        case 'm':
            system("cls");
            if(!mostrarAutosSeparadosXMarca(autos,TAM,marcas,TAM_M,colores,TAM_C,clientes,TAM_CL))
            {
                printf("\n\n");
            }
            else
            {
                printf("problema al ordenar la lista\n\n");
            }
            break;

        case 'n':
            system("cls");
            if(autos!=NULL && TAM>0 && marcas!=NULL && TAM_M>0)
            {
                contarColoresYMarcas(autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL);
            }
            else
            {
                printf("problemas al buscar la marca mas usada\n\n");
            }
            break;

        case 'o':
            system("cls");
            if(autos!=NULL && TAM>0 && marcas!=NULL && TAM_M>0)
            {
                marcaMasUsada( autos, TAM, marcas, TAM_M);
            }
            else
            {
                printf("problemas al buscar la marca mas usada\n\n");
            }

            break;

        case 'p':
            system("cls");
            if(mostrarTrabajosPorAuto(trabajos, TAM_T, autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL, lavados, TAM_S))
            {
                printf("\n\n");
            }
            else
            {
                printf("problemas con los trabajos\n\n");
            }

            break;

        case 'q':
            system("cls");

            if(mostrarImportePorAuto(trabajos, TAM_T, autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL, lavados, TAM_S))
            {
                importe =mostrarImportePorAuto(trabajos, TAM_T, autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL, lavados, TAM_S);
                printf("el importe de este auto fue: %d\n\n", &importe);
            }
            else
            {
                printf("problemas con los importes\n\n");
            }
            break;

        case 'r':
            system("cls");
            if(mostrarAutoPorServicio(trabajos, TAM_T, autos, TAM, marcas, TAM_M, colores, TAM_C, clientes, TAM_CL, lavados, TAM_S))
            {
                printf("\n\n");
            }
            else
            {
                printf("problemas al mostrar el Auto\n\n");
            }
            break;

        case 's':
            system("cls");
            if(mostrarServicioPorFecha(trabajos,  TAM_T, lavados, TAM_S))
            {
                printf("\n\n");
            }
            else
            {
                printf("problemas con los modelos\n\n");
            }
            break;

        case 'z':
            printf("Desea salir?: ");
            fflush(stdin);
            scanf("%c", &confirma);
            confirma = tolower(confirma);
            if(confirma == 's')
            {
                seguir = 'n';
            }
            break;

        }
        system("pause");
    }
    while(seguir == 's');

    return 0;
}

char menu()
{
    char opcion;
    system("cls");

    printf("   Lavadero de Autos   \n\n");
    printf("a Alta Auto\n");
    printf("b Modificar Auto\n");
    printf("c Baja Autos\n");
    printf("d Listar Autos\n");
    printf("e Listar Marcas\n");
    printf("f Listar Colores\n");
    printf("g Listar Servicios\n");
    printf("h Alta trabajo\n");
    printf("i Listar trabajos\n");
    printf("j Listar Color seleccionado\n");//
    printf("k Listar marca seleccionado\n");//
    printf("l Mostrar auto mas viejo o viejos\n");
    printf("m Listar autos separados por marca\n");
    printf("n Listar autos por marca y color seleccionado\n");
    printf("o Listar marca mas elegida\n");
    printf("p mostrar todos los trabajos que se le hicieron a un auto\n");
    printf("q informar la suma de los importes que se le hicieron a un auto\n");
    printf("r listar servicios realizados, los autos, y la fecha\n");
    printf("s Listar servicios realizados en fecha seleccionada\n");
    printf("z Salir\n\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    opcion = tolower(getchar());

    return opcion;
}
