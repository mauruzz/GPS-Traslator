#ifndef GPS_PROCESSOR__H
#define GPS_PROCESSOR__H

#include <stdio.h>
#include "types.h"
#include "ADT_vector.h"
#include "ADT_GPS_record.h"
#include "utils.h"


#define GPS_RECORD_LENGTH 					72

#define MAX_SIZE_COORDINATES 				9
#define GPS_RECORD_TIME_POS 				1
#define GPS_RECORD_LATITUDE_POS 			2
#define GPS_RECORD_LONGITUDE_POS 			4
#define GPS_RECORD_N_S_POS 					3
#define GPS_RECORD_E_W_POS 					5
#define GPS_RECORD_HEIGHT_POS 				9
#define INDICATOR_CHAR_SOUTH 				'S'
#define INDICATOR_CHAR_WEST 				'W'
#define COORD_LATITUDE_DEGREES_POS 			0
#define COORD_LATITUDE_DEGREES_LENGTH 		2
#define COORD_LATITUDE_MINUTES_POS 			2
#define COORD_LATITUDE_MINUTES_LENGTH 		9
#define COORD_LONGITUDE_DEGREES_POS 		0
#define COORD_LONGITUDE_DEGREES_LENGTH 		3
#define COORD_LONGITUDE_MINUTES_POS 		3
#define COORD_LONGITUDE_MINUTES_LENGTH 		9

#define GPS_RECORD_DELIM_CHAR				','
#define MAX_FORMATS 						2 
#define CSV_DELIM_CHAR 						'|'
#define KML_DELIM_CHAR 						','
#define FMT_OPTION_CSV						"csv"	/*FORMATO DE SALIDA*/
#define FMT_OPTION_KML						"kml"	/*FORMATO DE SALIDA*/

/*----------------------------PROTOTIPOS--------------------------------------------*/
status_t process_gps_records( FILE * fi, FILE * fo, string fmt );
status_t load_gps_records( FILE *input_file, ADT_Vector_t ** records );
status_t export_gps_records( ADT_Vector_t * records, FILE * fo, doc_type_t doc_type );
status_t build_gps_record( string line,ADT_GPS_Record_t ** gps_record );
status_t get_gps_record_coordinates( char ** str_array, double *reg_time, double * latitude,double * longitude,double * height );
doc_type_t set_format( string fmt );
status_t sort_gps_records( ADT_Vector_t ** records );

#endif
