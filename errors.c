#include <stdio.h>
#include "errors.h"
#include "types.h"

char * errors[ MAX_ERRORS ] = {
	"EJECUCIÓN EXITOSA.",
	"PUNTERO NULO.",
    "POCOS ARGUMENTOS.",
    "MUCHOS ARGUMENTOS.",
    "FALLA DE INVOCACIÓN.",
	"NO HAY ESPACIO EN DISCO.",
    "FORMATO INCORRECTO.",
    "NO SE PUEDE ABRIR ARCHIVO ENTRADA.",
    "NO SE PUEDE ABRIR ARCHIVO SALIDA.",
    "FALLA DE MEMORIA.",
	"REGISTRO CORRUPTO.",
    "NO SE PUEDE ABRIR ARCHIVO HEADER.",
    "NO SE PUEDE ABRIR ARCHIVO FOOTER."
};

/*----------------------IMPRIMIR ERRORES-----------------------------*/
status_t show_error( status_t st )
{
	fprintf( stderr, "%s\n\n", errors[ st ] );
	return OK;
}
