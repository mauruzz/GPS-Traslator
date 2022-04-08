#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>
#include "types.h"
	
#define MAX_CMD_ARGS 			6		/*CANTIDAD MAXIMA DE ARGUMENTOS*/
#define CMD_FLAG_FMT_POS 		1		/*ORDEN DE LA OPCIÓN FORMATO*/ 
#define CMD_FMT_OPTION_POS 		2		/*ORDEN DEL FORMATO ELEGIDO*/ 
#define CMD_FLAG_OUT_POS 		3		/*ORDEN DE LA OPCIÓN OUT*/ 
#define CMD_OUT_FILE_ROUTE 		4		/*ORDEN DE LA RUTA DE SALIDA*/ 
#define CMD_IN_FILE_ROUTE 		5		/*ORDEN DE LA RUTA DE ENTRADA*/ 
#define CMD_FLAG_FMT_DES		"-fmt"	/*DESCRIPCIÓN DE LA OPCION FORMATO*/
#define CMD_FLAG_OUT_DES 		"-out"	/*DESCRIPCIÓN DE LA OPCION OUT*/


/*----------------------------PROTOTIPOS--------------------------------------------*/
status_t validar_args( size_t l_arg, char * argv[] );


#endif