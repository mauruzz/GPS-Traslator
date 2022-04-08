#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "gps_processor.h"
#include "ADT_vector.h"
#include "ADT_GPS_record.h"
#include "utils.h"
#include "nmea_filtrator.h"

/*--------------------------PROCESAR REGISTROS DE GPS------------------------------------*/
status_t process_gps_records ( FILE * fi, FILE * fo, string fmt )
{
	ADT_Vector_t * records;
	status_t st;
	doc_type_t doc_type;

	if ( fi == NULL )
		return ERROR_NULL_POINTER;
	
	if ( ( st = load_gps_records( fi, &records ) ) != OK )
		return st;

	if ( ( st = sort_gps_records( &records ) ) != OK )
		return st;

	doc_type = set_format( fmt );

	if ( ( st = export_gps_records( records, fo, doc_type ) ) != OK )
		return st;

	return OK;
}

/*-----------------------ORDENAR REGISTROS DE GPS----------------------------*/
status_t sort_gps_records( ADT_Vector_t ** records )
{
	status_t st;
	sortter_t sortter;

	sortter = ( sortter_t ) ADT_GPS_Record_sort;

	if ( ( st = ADT_Vector_set_sortter( * records, (sortter_t)sortter ) ) != OK ) 
		return st;

	if ( ( st = ADT_Vector_sort( records ) ) != OK ) 
		return st;

	return OK;
}

/*--------------------------CARGAR REGISTROS DE GPS------------------------------------*/
status_t load_gps_records( FILE * fi, ADT_Vector_t ** records )
{
	status_t st;
	ADT_GPS_Record_t *gps_record;
	bool_t eof;
	string line;


	if ( fi == NULL || records == NULL )
		return ERROR_NULL_POINTER;
	
	if( ( st = ADT_Vector_create( records ) ) != OK)
		return st;
	
	if ( ( st = ADT_Vector_set_destructor( *records, (destructor_t)ADT_GPS_Record_delete ) ) != OK )
		return st;

	
	eof = FALSE;
	while ( eof != TRUE )
	{
		if ( (st = read_line( fi, &line, &eof ) ) != OK )
			return st; 

		if ( ( st = nmea_filter( line ) ) != OK )
			continue;
		
		if ( ( st = build_gps_record( line, &gps_record ) ) != OK )
		{
			ADT_Vector_destroy( records );
			return st;
		}
		if ( ( st = ADT_Vector_append( *records, (void*) gps_record ) ) != OK )
		{
			ADT_Vector_destroy( records );
			return st;
		}
	}
	return OK;
}

/*--------------------------CONSTRUIR REGISTRO DE GPS------------------------------------*/
status_t build_gps_record ( string line, ADT_GPS_Record_t ** gps_record )
{
	status_t st;
	string * str_array;
	size_t array_len;
	double reg_time, latitude, longitude, height;
	
	if( gps_record == NULL || line == NULL )
		return ERROR_NULL_POINTER;

/*----------------------------PARSEO-----------------------------------------------*/
	if ( ( st = split( line, &array_len, &str_array, GPS_RECORD_DELIM_CHAR ) ) != OK )
		return st;

/*-------------------------CREAR GPS RECORD------------------------------------------*/
	if ( ( st = ADT_GPS_Record_create( gps_record ) ) != OK )
		return st;

/*--------------------------OBTENER COORDENADAS----------------------------------*/
	if ( ( st = get_gps_record_coordinates( str_array, &reg_time, &latitude, &longitude, &height ) ) != OK )
		return st;

/*---------------------------CARGAR COORD A GPS RECORD-----------------------------------*/
	if ( ( st = ADT_GPS_Record_set_coord( *gps_record, reg_time, latitude, longitude, height ) ) != OK )
		return st;

	return OK;
}


/*-------------OBTENER HORA Y INFO GEOLOCALIZACIÓN DE REGISTRO GPS--------------------*/
status_t get_gps_record_coordinates( string *str_array, double *reg_time, double *latitude, double *longitude, double *height )
{
	char aux_string[ MAX_SIZE_COORDINATES + 1 ], * temp, deg;  
	double min;

	if ( str_array == NULL || latitude == NULL || longitude == NULL || height == NULL )
		return ERROR_NULL_POINTER;

/*------------------------------OBTENER HORA------------------------------------------*/
	if ( str_array[ GPS_RECORD_TIME_POS ] )
	{
		*reg_time = strtod( str_array[ GPS_RECORD_TIME_POS ], &temp );
		
		if( *temp )
			return ERROR_CORRUPT_GPS_RECORD;
	}

/*-----------------------------OBTENER LATITUD--------------------------------------*/
	if ( str_array[GPS_RECORD_LATITUDE_POS] )
	{
		if ( memcpy( aux_string, str_array[ GPS_RECORD_LATITUDE_POS ] + COORD_LATITUDE_DEGREES_POS, COORD_LATITUDE_DEGREES_LENGTH * sizeof( char ) ) == NULL )
			return ERROR_OUT_OF_MEMORY;
		
		aux_string[ COORD_LATITUDE_DEGREES_LENGTH ] = '\0';
		deg = ( char ) strtol( aux_string, &temp, 10 );
		
		if ( *temp )
			return ERROR_CORRUPT_GPS_RECORD;

		if ( memcpy( aux_string, str_array[ GPS_RECORD_LATITUDE_POS ] + COORD_LATITUDE_MINUTES_POS, COORD_LATITUDE_MINUTES_LENGTH * sizeof(char) ) == NULL )
			return ERROR_OUT_OF_MEMORY;

		aux_string[ COORD_LATITUDE_MINUTES_LENGTH ] = '\0';
		min = strtod( aux_string, &temp );
		
		if ( *temp )
		return ERROR_CORRUPT_GPS_RECORD;
		
		*latitude = ( double ) deg + ( min / 60 );

		if ( str_array[ GPS_RECORD_N_S_POS ] && str_array[ GPS_RECORD_N_S_POS ][ 0 ] == INDICATOR_CHAR_SOUTH )
			*latitude = -( *latitude );
	}

/*----------------------------OBTENER LONGITUD---------------------------------------------*/
	if(str_array[GPS_RECORD_LONGITUDE_POS])
	{
		if ( memcpy( aux_string, str_array[ GPS_RECORD_LONGITUDE_POS ] + COORD_LONGITUDE_DEGREES_POS, COORD_LONGITUDE_DEGREES_LENGTH * sizeof( char ) ) == NULL )
			return ERROR_OUT_OF_MEMORY;
		
		aux_string[ COORD_LONGITUDE_DEGREES_LENGTH ] = '\0';
		deg = (char) strtol( aux_string, &temp, 10 );

		if ( *temp )
			return ERROR_CORRUPT_GPS_RECORD;

		if ( memcpy( aux_string, str_array[ GPS_RECORD_LONGITUDE_POS ] + COORD_LONGITUDE_MINUTES_POS, COORD_LONGITUDE_MINUTES_LENGTH * sizeof( char ) ) == NULL )
			return ERROR_OUT_OF_MEMORY;
		
		aux_string[ COORD_LONGITUDE_MINUTES_LENGTH ] = '\0';
		min = strtod( aux_string, &temp );
		
		if ( *temp )
			return ERROR_CORRUPT_GPS_RECORD;
		
		*longitude = ( double ) deg + ( min / 60 );

		if ( str_array[ GPS_RECORD_E_W_POS ] && str_array[ GPS_RECORD_E_W_POS ][ 0 ] == INDICATOR_CHAR_WEST )
			*longitude = -( *longitude );
	}

/*------------------------------OBTENER ALTURA------------------------------------------*/
	if ( str_array[ GPS_RECORD_HEIGHT_POS ] )
	{
		*height = strtod( str_array[ GPS_RECORD_HEIGHT_POS ], &temp );
		
		if ( *temp )
			return ERROR_CORRUPT_GPS_RECORD;
	}

	return OK;
}

/*--------------------------SETEAR FORMATO DE EXPORTACIÓN------------------------------*/
doc_type_t set_format( string fmt )
{
	if ( !strcmp( fmt, FMT_OPTION_CSV ) )
		return DOC_TYPE_CSV;

	else
		return DOC_TYPE_KML;
}

/*--------------------------EXPORTAR REGISTROS------------------------------------*/
status_t export_gps_records( ADT_Vector_t * records, FILE * fo, doc_type_t doc_type )
{
	status_t st;
	exporter_t exporter;
	exporter_t gps_record_exporter;
	char delim[ MAX_FORMATS ] = { CSV_DELIM_CHAR, KML_DELIM_CHAR };

	if ( records == NULL || fo == NULL )
		return ERROR_NULL_POINTER;
	
	if ( doc_type == DOC_TYPE_CSV )  /*ESTO ES LO QUE VOS PASAS POR LINEA DE ORDENES*/
	{
		exporter = (exporter_t)ADT_Vector_export_as_csv;
		gps_record_exporter = (exporter_t)ADT_GPS_Record_export_as_csv;

		if ( ( st = ADT_Vector_set_exporter( records, (exporter_t)gps_record_exporter ) ) != OK ) 
			return st;

		if ( ( st = exporter( ( void * ) records, ( void * ) ( &delim[ DOC_TYPE_CSV ]), fo ) ) != OK )
			return st;

		return OK;
	}
	else /*ESTE ES EL CASO DE KML*/
	{
		exporter = ( exporter_t )ADT_Vector_export_as_xml;
		gps_record_exporter = ( exporter_t ) ADT_GPS_Record_export_as_kml;

		if ( ( st = ADT_Vector_set_exporter( records, (exporter_t)gps_record_exporter ) ) != OK )
			return st;

		if ( ( st = exporter( ( void * ) records, ( void * ) ( &delim[ DOC_TYPE_KML ] ), fo ) ) != OK )
			return st;

		return OK;
	}
}
