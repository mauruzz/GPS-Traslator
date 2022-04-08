
#ifndef ADT_VECTOR__H
#define ADT_VECTOR__H

#include <stdio.h>
#include "types.h"

#define INIT_CHOP 5

typedef struct  {  
	void ** elements;
	size_t size;
	destructor_t destructor;
	exporter_t exporter; 
	sortter_t sortter;  
} ADT_Vector_t;

/*--------------------------PRIMITIVAS---------------------------------*/

status_t ADT_Vector_create( ADT_Vector_t ** p );
status_t ADT_Vector_destroy( ADT_Vector_t **p );
status_t ADT_Vector_append( ADT_Vector_t * p, const void * n );
status_t ADT_Vector_set_destructor( ADT_Vector_t *p, destructor_t destructor );
status_t ADT_Vector_set_exporter( ADT_Vector_t *p, exporter_t exporter );
status_t ADT_Vector_export_as_csv( const ADT_Vector_t * p, const void* delim, FILE * fo );
status_t ADT_Vector_export_as_xml( const ADT_Vector_t * p, const void* delim, FILE * fo );
status_t ADT_Vector_set_sortter ( ADT_Vector_t *p, sortter_t sortter );
status_t ADT_Vector_sort ( ADT_Vector_t ** p );

#endif
