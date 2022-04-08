#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"

/*-------------------------LEER LINEA--------------------------*/
status_t read_line( FILE * fi, string * s, bool_t * eof )
{
	int c;
	size_t alloc_size;
	size_t used_size;
	char * aux;

	if ( fi == NULL || s == NULL || eof == NULL )
		return ERROR_NULL_POINTER;

	if ( ( *s = malloc( INIT_CHOP_STR * sizeof( char ) ) ) == NULL )
		return ERROR_MEMORY;
	alloc_size = INIT_CHOP_STR;
	used_size = 0;

	while ( ( c = fgetc( fi )) != LF && c != EOF )
	{
		if ( used_size == alloc_size - 1 )
		{
			if ( ( aux = realloc( *s, ( alloc_size + CHOP_SIZE ) * sizeof( char ) ) ) == NULL )
			{
				free( *s );
				*s = NULL;
				return ERROR_MEMORY;
			}
			alloc_size += CHOP_SIZE;
			*s = aux;
		}
		(*s)[ used_size++ ] = c;
	}
	(*s)[ used_size ] = NUL;
	*eof = ( c == EOF ) ? TRUE : FALSE;
	
	return OK;
}

/*----------------------PARSEAR CADENA-----------------------------*/
status_t split ( const string s, size_t *l, string **fields, char delimiter )
{
	string str, q, p;
	size_t i;
	char str_delimiter [ 2 ];

	str_delimiter[ 0 ] = delimiter;
	str_delimiter[ 1 ] = NUL;

	if ( s == NULL || l == NULL || fields == NULL )
		return ERROR_NULL_POINTER;
	

	if ( ( str = strdupl( s ) ) == NULL ){
		*l = 0;
		return ERROR_MEMORY;
	}

	for ( i = 0, *l = 0 ; str[ i ] ; i++ )
		if ( str[ i ] == delimiter )
			( *l )++;
	( *l )++;

	if ( ( *fields = ( string * ) malloc( ( *l ) * sizeof( string ) ) ) == NULL){
		free( str );
		*l = 0;
		fprintf( stderr, "%s\n", "no hay memoria" );
		return ERROR_MEMORY;
	}

	for ( i = 0, q = str ; ( p = strtok( q, str_delimiter ) ) != NULL ; q = NULL, i++)
	{
		if ( ( ( *fields ) [ i ] = strdupl( p ) ) == NULL )
		{
			free( str );
			destroy_strings( fields, *l );
			*l = 0;
			return ERROR_MEMORY;
		}
	}
	
	free( str );
	
	return OK;
}

/*----------------------DESTRUIR CADENAS DEL PARSEO-----------------------------*/
status_t destroy_strings( string ** fields, size_t l )
{
	size_t i;

	if ( fields == NULL )
		return ERROR_NULL_POINTER;

	for ( i = 0 ; i < l ; i++ )
	{
		free( ( *fields ) [ i ] );
		( *fields ) [ i ] = NULL;
	}
	free( *fields );
	*fields = NULL;

	return OK;
}

/*----------------------DUPLICAR CADENAS-----------------------------*/
char * strdupl( string cadena )
{
	string copia;
	size_t i;

	if ( ( copia = ( string ) malloc( ( strlen( cadena ) + 1 ) * sizeof( char ) ) ) == NULL )
		return NULL;	
	
	for ( i = 0; ( copia[ i ] = cadena[ i ] ); i++ );
	
	return copia;
}

/*----------------------INTERCAMBIAR POSICIONES-----------------------------*/
status_t swap( void ** a, void ** b )
{
	void * aux;

	if( a == NULL || b == NULL )
		return ERROR_NULL_POINTER;
	
	aux = *a;
	*a = *b;
	*b = aux;
	
	return OK;	
}
