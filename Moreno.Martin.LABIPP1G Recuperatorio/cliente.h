#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct
{
    int id;
    char nombre[20];
    char sexo;
    int isEmpty;
}eCliente;

#endif // CLIENTE_H_INCLUDED
void mostrarCliente(eCliente clientes);
int mostrarClientes(eCliente clientes[], int tamCL);
int validarIdClientes(eCliente clientes[], int tamCL, int id);
int obtenerNombreCliente(eCliente clientes[], int tamCL, int id, char nombre[]);
