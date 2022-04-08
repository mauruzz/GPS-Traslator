#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "ADT_vector.h"
#include "utils.h"

/*-------------------CREAR ADT_VECTOR----------------------------------*/
status_t ADT_Vector_create ( ADT_Vector_t ** p )
{
    if ( p == NULL )
        return ERROR_NULL_POINTER;
    
    if ( ( *p = ( ADT_Vector_t * ) malloc( sizeof( ADT_Vector_t ) ) ) == NULL )
        return ERROR_MEMORY;

    (*p)->elements = ( void ** ) malloc( INIT_CHOP * sizeof( void * ) );
	if ( ( *p )->elements == NULL ){
		free( *p );
		*p = NULL;
		return ERROR_MEMORY;
	}

    ( *p )->size = 0;
    ( *p )->destructor = NULL;
    ( *p )->exporter = NULL;
    ( *p )->sortter = NULL;

    return OK;
}

/*-------------------DESTRUIR ADT_VECTOR----------------------------------*/
status_t ADT_Vector_destroy ( ADT_Vector_t **p )
{
    size_t i;
    status_t st;

	if ( p == NULL || (*p)->destructor == NULL )
		return ERROR_NULL_POINTER;
	
	for ( i=0 ; i < (*p)->size ; i++ )
    {
		if ( ( st = ( *( ( *p )->destructor ) ) ( ( *p )->elements[ i ] ) ) != OK )
			return st;
		
		( *p )->elements[ i ] = NULL;
	}
    free( ( *p )->elements );
	( *p )->elements = NULL;
    free( *p );
    *p = NULL;
    return OK;
}

/*-------------------AGREGAR ELEMENTO AL FINAL DE ADT_VECTOR----------------------------------*/
status_t ADT_Vector_append ( ADT_Vector_t * p, const void * n )
{
	void ** aux;

	if ( p == NULL || n == NULL )
		return ERROR_NULL_POINTER;
	
	if ( ( aux = ( void ** ) realloc( p->elements , ( p->size + 1 ) * sizeof( void* ) ) ) == NULL )

		return ERROR_MEMORY;
	
	p->elements = aux;
	p->elements[ p->size ] = n;
	( p->size )++;
	return OK;
}

/*-------------------SETEAR DESTRUCTOR EN ADT_VECTOR----------------------------------*/
status_t ADT_Vector_set_destructor ( ADT_Vector_t *p, destructor_t destructor )
{
	if ( p == NULL )
		return ERROR_NULL_POINTER;

	p->destructor = destructor;

	return OK;
}

/*-------------------SETEAR EXPORTADOR EN ADT_VECTOR----------------------------------*/
status_t ADT_Vector_set_exporter ( ADT_Vector_t *p, exporter_t exporter )
{
	if( p == NULL )
		return ERROR_NULL_POINTER;

	p->exporter = exporter;

	return OK;
}

/*-------------------EXPORTAR ELEMENTOS DE ADT_VECTOR A CSV----------------------------------*/
status_t ADT_Vector_export_as_csv ( const ADT_Vector_t * p, const void * delim, FILE * fo )
{
	size_t i;
	status_t st;
	int c;
	FILE * f_csv_header, * f_csv_footer;

	if( p == NULL || delim == NULL || fo == NULL )
		return ERROR_NULL_POINTER;

/*-------------------IMPRIMIR HEADER (en este caso vacio)----------------------------------*/
	if ( ( f_csv_header = fopen( "csv_header.txt", "rt" ) ) == NULL )
		return ERROR_OPEN_XML_HEADER_FILE;

	while ( ( c = fgetc( f_csv_header ) ) != EOF )
		fputc( c, fo );

	fclose( f_csv_header );

/*-------------------IMPRIMIR DATOS----------------------------------*/
	for ( i = 0 ; i < ( ( ADT_Vector_t * ) p )->size ; i++ )
		if( ( st = ( *( ( ( ADT_Vector_t * ) p )->exporter ) ) ( (void*) ( ( ( ADT_Vector_t * ) p )->elements[ i ] ), delim, fo ) ) != OK )
			return st;		

/*-------------------IMPRIMIR FOOTER (en este caso vacio)----------------------------------*/	
	if ( ( f_csv_footer = fopen( "csv_footer.txt", "rt" ) ) == NULL )
		return ERROR_OPEN_XML_FOOTER_FILE;

	while ( ( c = fgetc( f_csv_footer ) ) != EOF )
		fputc( c, fo );

	fclose( f_csv_footer );

	return OK;
}

/*-------------------EXPORTAR ELEMENTOS DE ADT_VECTOR A KML----------------------------------*/
status_t ADT_Vector_export_as_xml ( const ADT_Vector_t * p, const void * delim, FILE * fo )
{
	size_t i;
	status_t st;
	int c;
	FILE * f_xml_kml_header, * f_xml_kml_footer;

	if ( p == NULL || delim == NULL || fo == NULL )
		return ERROR_NULL_POINTER;

/*-------------------IMPRIMIR HEADER----------------------------------*/
	if ( ( f_xml_kml_header = fopen( "xml_kml_header.txt", "rt" ) ) == NULL )
		return ERROR_OPEN_XML_HEADER_FILE;

	while ( ( c = fgetc( f_xml_kml_header ) ) != EOF )
		fputc( c, fo );

	fclose( f_xml_kml_header );

/*-------------------IMPRIMIR DATOS----------------------------------*/
	for(i=0 ; i < ( ( ADT_Vector_t * ) p )->size ; i++ )
		if( ( st = ( *( ( ( ADT_Vector_t * ) p )->exporter ) ) ( (void*) ( ( ( ADT_Vector_t * ) p )->elements[ i ] ), delim, fo ) ) != OK )
			return st;

/*-------------------IMPRIMIR FOOTER----------------------------------*/	
	if ( ( f_xml_kml_footer = fopen( "xml_kml_footer.txt", "rt" ) ) == NULL )
		return ERROR_OPEN_XML_FOOTER_FILE;

	while ( ( c = fgetc( f_xml_kml_footer ) ) != EOF )
		fputc( c, fo );

	fclose( f_xml_kml_footer );

	return OK;
}
/*--------------------SETEAR SORTTER DE ADT_VECTOR--------------------------*/
status_t ADT_Vector_set_sortter ( ADT_Vector_t *p, sortter_t sortter )
{
	if( p == NULL )
		return ERROR_NULL_POINTER;

	p->sortter = sortter;

	return OK;	
}

/*-------------------ORDENAR ELEMENTOS EN ADT_VECTOR----------------------------------*/
status_t ADT_Vector_sort ( ADT_Vector_t **p )
{
	status_t st;
	size_t i, j;

	if( p == NULL )
		return ERROR_NULL_POINTER;

	for( i = 0 ; i < (*p)->size ; i++ )
	{
		for( j = 0; j < ( (*p)->size - 1 - i ) ; j++ )
		{
			if( ( st = ( *( ( * p )->sortter ) ) ( ( ( *p )->elements[ i ] ),  ( ( *p )->elements[ i + 1 ] ) ) ) != OK )
				return st;	
		}
	}
	return OK;
}
