#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "fecha.h"


/** \brief muestra los valores de dia, mes y año
 *
 * \param unaFecha eFecha
 * \return void
 *
 */
void mostrarFecha(eFecha unaFecha)
{
    printf("%02d/%02d/%d\n\n", unaFecha.dia, unaFecha.mes, unaFecha.anio);
}
