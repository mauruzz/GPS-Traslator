#ifndef UTILS__H
#define UTILS__H

#include <stdio.h>
#include "types.h"

#define INIT_CHOP_STR				72
#define CHOP_SIZE					2

/*----------------------------PROTOTIPOS--------------------------------------------*/
status_t read_line( FILE * archivo_entrada, string * str, bool_t * eof );
status_t split( const string s, size_t *l, string **fields, char delimiter );
status_t destroy_strings( string **fields, size_t l );
char * strdupl( string cadena );
status_t swap( void ** a, void ** b );

#endif