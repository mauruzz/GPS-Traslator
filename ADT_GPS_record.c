#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "ADT_GPS_record.h"
#include "utils.h"

/*-------------------CREAR ADT_GPS_Record----------------------------------*/
status_t ADT_GPS_Record_create( ADT_GPS_Record_t ** p )
{
	if ( p == NULL )
		return ERROR_NULL_POINTER;
	
	if ( ( *p = ( ADT_GPS_Record_t * ) calloc( 1, sizeof( ADT_GPS_Record_t ) ) ) == NULL )
		return ERROR_MEMORY;
	
	return OK;
}

/*-------------------ELIMINAR ADT_GPS_Record----------------------------------*/
status_t ADT_GPS_Record_delete( ADT_GPS_Record_t ** gps_record )
{
	if ( gps_record == NULL )
		return ERROR_NULL_POINTER;
	
	free( * gps_record );
	*gps_record = NULL;
	return OK;
}

/*-------------------SETEAR COORDENADAS EN ADT_GPS_Record----------------------------------*/
status_t ADT_GPS_Record_set_coord( ADT_GPS_Record_t * gps_record, double reg_time, double latitude, double longitude, double height )
{
	if ( gps_record == NULL )
		return ERROR_NULL_POINTER;
	
	gps_record->reg_time = reg_time;
	gps_record->latitude = latitude;
	gps_record->longitude = longitude;
	gps_record->height = height;
	return OK;
}

/*-------------------EXPORTAR ADT_GPS_Record COMO CSV----------------------------------*/
status_t ADT_GPS_Record_export_as_csv( const void * gps_record, const void * delim, FILE * fo )
{
	time_t t;
	struct tm *tm;

	if ( gps_record == NULL || fo == NULL )
		return ERROR_NULL_POINTER;
	
	t = time( NULL );
	tm = localtime( &t );

	fprintf( fo,"%02d%02d%02d%.0f%c%.14f%c%.14f%c%.1f\n", 1900+tm->tm_year, 1+tm->tm_mon, tm->tm_mday,
												( ( ADT_GPS_Record_t * ) gps_record )->reg_time, *( ( char * ) delim ),
												( ( ADT_GPS_Record_t * ) gps_record )->latitude, *( ( char * ) delim ),
												( ( ADT_GPS_Record_t * ) gps_record )->longitude, *( ( char * ) delim ),
												( ( ADT_GPS_Record_t * ) gps_record )->height );
	return OK;
}

/*-------------------EXPORTAR ADT_GPS_Record COMO KML----------------------------------*/
status_t ADT_GPS_Record_export_as_kml( const void * gps_record, const void * delim, FILE * fo )
{
	if ( gps_record == NULL || fo == NULL )
		return ERROR_NULL_POINTER;
	
	fprintf( fo,"%.14f%c%.14f%c%.0f\n",	( ( ADT_GPS_Record_t * ) gps_record )->longitude, * ( ( char * ) delim ),
										( ( ADT_GPS_Record_t * ) gps_record )->latitude, * ( ( char * ) delim ),
										( ( ADT_GPS_Record_t * ) gps_record )->height );
	return OK;
}

/*-------------------ORDENAR REGISTROS SEGUN REG_TIME----------------------------------*/
status_t ADT_GPS_Record_sort ( void ** ptr1 , void ** ptr2 )
{
	if ( ptr1 == NULL || ptr2 == NULL )
		return ERROR_NULL_POINTER;

	if ( ( ( ADT_GPS_Record_t * ) ptr1 )->reg_time > ( ( ADT_GPS_Record_t * ) ptr2 )->reg_time )
	{
		swap( ptr1 , ptr2 );
	}

	return OK;
}