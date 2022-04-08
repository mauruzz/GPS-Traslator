#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "main.h"
#include "gps_processor.h"
#include "errors.h"

int main ( int argc, char * argv[] )
{
	status_t st;
	FILE *input_file, *output_file;

/*-----------------VALIDAR ARGUMENTOS------------------------------------------*/
	if ( ( st = validar_args( argc, argv ) ) != OK )
	{
		show_error( st );
		return st;
	}

/*-------------------------------ABRIR ARCHIVOS--------------------------------*/
	if ( ( input_file = fopen( argv[ CMD_IN_FILE_ROUTE ], "rt" ) ) == NULL )
	{
		show_error( ERROR_OPEN_INPUT_FILE );
		return ERROR_OPEN_INPUT_FILE;
	}

	if ( ( output_file = fopen( argv[ CMD_OUT_FILE_ROUTE ], "wt" ) ) == NULL )
	{
		fclose( input_file );
		show_error( ERROR_OPEN_OUTPUT_FILE );
		return ERROR_OPEN_OUTPUT_FILE;
	}

/*-----------------PROCESAR REGISTROS DE GPS-------------------------------------*/
	if ( ( st = process_gps_records( input_file, output_file, argv[ CMD_FMT_OPTION_POS ] ) ) != OK )
	{
		show_error( st );
		return st;
	}

/*-----------------CERRAR ARCHIVOS----------------------------------------------*/
	fclose( input_file );
	if ( fclose( output_file ) == EOF )
	{
		show_error( ERROR_MEMORY );
		return ERROR_MEMORY;
	}

	return OK;
}


/*-----------------------------------VALIDAR ARGUMENTOS-------------------------*/
status_t validar_args( size_t l_arg, char * argv[] )
{
	if ( argv == NULL )
		return ERROR_NULL_POINTER;

	if ( l_arg < MAX_CMD_ARGS )
		return ERROR_FEW_ARGUMENTS;

	if ( l_arg > MAX_CMD_ARGS )
		return ERROR_TOO_MANY_ARGUMENTS;

	if ( ( strcmp( argv[ CMD_FLAG_FMT_POS ], CMD_FLAG_FMT_DES ) ) || ( strcmp( argv[ CMD_FLAG_OUT_POS ], CMD_FLAG_OUT_DES ) ) )
		return ERROR_INVOCATION;

	if ( ( strcmp( argv[ CMD_FMT_OPTION_POS ], FMT_OPTION_KML ) ) && ( strcmp( argv[ CMD_FMT_OPTION_POS ], FMT_OPTION_CSV ) ) )
		return ERROR_FORMAT_FILE;

	return OK;
}
