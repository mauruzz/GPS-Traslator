#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

#define LF  						'\n'	
#define NUL  						'\0'

typedef char * string;
typedef unsigned char uchar;

typedef enum { TRUE, FALSE } bool_t;

typedef enum { DOC_TYPE_CSV, DOC_TYPE_KML } doc_type_t;

typedef enum {
	OK, 
	ERROR_NULL_POINTER, 
	ERROR_FEW_ARGUMENTS, 
	ERROR_TOO_MANY_ARGUMENTS, 
	ERROR_INVOCATION, 
	ERROR_MEMORY, 
	ERROR_FORMAT_FILE, 
	ERROR_OPEN_INPUT_FILE, 
	ERROR_OPEN_OUTPUT_FILE, 
	ERROR_OUT_OF_MEMORY,
	ERROR_CORRUPT_GPS_RECORD,
	ERROR_OPEN_XML_HEADER_FILE,
	ERROR_OPEN_XML_FOOTER_FILE
}status_t;

typedef status_t ( * destructor_t )( void * );
typedef status_t ( * exporter_t )( const void *, const void *, FILE * );
typedef status_t ( * sortter_t )( void **, void ** );

#endif
