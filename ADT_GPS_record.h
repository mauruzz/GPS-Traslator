#ifndef ADT_GPS_RECORD__H
#define ADT_GPS_RECORD__H

#include <stdio.h>
#include "types.h"

typedef struct  {  
	float reg_time; 
	float latitude;
	float longitude;
	float height;
} ADT_GPS_Record_t;

/*---------------------PRIMITIVAS------------------------------------------------*/
status_t ADT_GPS_Record_create(ADT_GPS_Record_t ** gps_record);
status_t ADT_GPS_Record_delete(ADT_GPS_Record_t ** gps_record);
status_t ADT_GPS_Record_set_coord(ADT_GPS_Record_t * gps_record, double reg_time, double latitude, double longitude, double height );
status_t ADT_GPS_Record_export_as_csv(const void * gps_record, const void * delim, FILE * fo );
status_t ADT_GPS_Record_export_as_kml(const void * gps_record, const void * delim, FILE * fo );
status_t ADT_GPS_Record_sort ( void ** ptr1 , void ** ptr2 );

#endif