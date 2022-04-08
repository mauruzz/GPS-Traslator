CC = gcc
CFLAGS = -ansi -pedantic -Wall

all : gpsviewer clean

gpsviewer : main.o nmea_filtrator.o gps_processor.o ADT_vector.o ADT_GPS_record.o utils.o errors.o
	$(CC) $(CFLAGS) -o gpsviewer main.o nmea_filtrator.o gps_processor.o ADT_vector.o ADT_GPS_record.o utils.o errors.o

main.o : main.c main.h
	$(CC) $(CFLAGS) -o main.o -c main.c

nmea_filtrator.o : nmea_filtrator.c nmea_filtrator.h
	$(CC) $(CFLAGS) -o nmea_filtrator.o -c nmea_filtrator.c

gps_processor.o : gps_processor.c gps_processor.h
	$(CC) $(CFLAGS) -o gps_processor.o -c gps_processor.c

ADT_GPS_record.o : ADT_GPS_record.c ADT_GPS_record.h
	$(CC) $(CFLAGS) -o ADT_GPS_record.o -c ADT_GPS_record.c

ADT_vector.o : ADT_vector.c ADT_vector.h
	$(CC) $(CFLAGS) -o ADT_vector.o -c ADT_vector.c

utils.o : utils.c utils.h
	$(CC) $(CFLAGS) -o utils.o -c utils.c

errors.o : errors.c errors.h
	$(CC) $(CFLAGS) -o errors.o -c errors.c


clean :
	rm *.o
