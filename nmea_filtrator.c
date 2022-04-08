#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "nmea_filtrator.h"
#include "utils.h"

/*----------------------FILTRAR REGISTRO DE ARCHIVO NMEA-----------------------------*/
status_t nmea_filter( string line )
{
	status_t st;

/*-------------------SALTEAR LOS QUE NO COMIENCEN CON $GPGGA---------------------------------------------*/
		if ( ( strncmp( ID_MENSAJE, line, ID_MENSAJE_LENGTH ) ) )
			return ERROR_CORRUPT_GPS_RECORD;

/*-------------------SALTEAR LOS QUE NO TENGAN TODOS LOS DATOS---------------------------------------------*/
		if ( strlen( line ) < L_MIN_LINEA )
			return ERROR_CORRUPT_GPS_RECORD;

/*-------------------SUMA DE VERIFICACIÓN---------------------------------------------*/
		if ( ( st = check_record_sum( line ) ) != OK ) 
			return ERROR_CORRUPT_GPS_RECORD;

	return OK;
}

/*-------------COMPROBAR SUMA DE VERIFICACIÓN DE REGISTRO DE ARCHIVO NMEA--------------------*/
status_t check_record_sum( char * cadena )
{
	uchar suma = 0x00, verif;
	size_t i, largo;
	char veri[2], *aux; 

	if( cadena == NULL )
		return ERROR_NULL_POINTER;

	for ( i = 1 ; cadena[ i ] != '*' ; i++ )
		suma = suma ^ ( cadena[ i ] & ( ~MASK_SUM_VER ) );

	largo = strlen( cadena );
	veri[0] = cadena[ largo - 3 ];
	veri[1] = cadena[ largo - 2 ];
	verif = strtol( veri, &aux, 16 );

	if( suma != verif )
		return ERROR_CORRUPT_GPS_RECORD;

	return OK;
}