#ifndef NMEA_FILTRATOR__H
#define NMEA_FILTRATOR__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define ID_MENSAJE 			"$GPGGA"		/*COMIENZO DE LINEAS DE INTERES*/
#define ID_MENSAJE_LENGTH 	5				/*LARGO DE LA ID DE INTERES (INICIA EN CERO)*/
#define L_MIN_LINEA			72				/*LARGO MINIMO PARA CADA LINEA UTIL (CAMPOS COMPLETOS)*/		

#define MASK_SUM_VER		0x80			/*MASCARA PARA VERIFICACIÓN DE SUMA*/


/*----------------------------PROTOTIPOS--------------------------------------------*/
status_t nmea_filter ( string line );
status_t check_record_sum ( char * cadena );

#endif