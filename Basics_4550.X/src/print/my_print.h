#ifndef MY_PRINT_H
#define MY_PRINT_H

/** INCLUDES *******************************************************/
#include <stdarg.h>

#include "../serial.h"
#include "format.h"

/** DEFINICIONES ***************************************************/

//Define el máximo tamaño de la cadena de texto de salida para la función my_vprintf. 
//Su valor por defecto es de 128 caracteres.
#define STR_SIZE 128

//Define el máximo tamaño de cada argumento formateado que se sustituirá en la cadena de 
//texto de salida de la función my_vprintf. Su valor por defecto es de 64 caracteres.
#define BUFF_SIZE 64

/*********************************************************************
* Funcion: int my_vprintf(const char *sformat, ... );
*
* Descripción: Esta función imprime un mensaje en código ASCII al dispositivo de salida de
* texto seleccionado en el archivo my_print.h, usado una cadena de formato que puede especificar 
* como los argumentos posteriores son convertidos para su salida.
*
* Parámetros: 
* 	char *sformat - Cadena de caracteres que contiene el texto que se escribirá en el dispositivo 
* 	de salida. Puede contener caracteres ordinarios o etiquetas de formato los cuales inician con 
* 	el carácter '%'. Estos últimos se remplazan por los valores especificados en argumentos adicionales 
* 	posteriores y formateados según lo especificado. El prototipo de las etiquetas de formato es:
* 	%[banderas] [ancho de campo] [.precisión] [especificador de tipo de conversión]

* 	[...] - Dependiendo de la cadena formateada, la función puede esperar una secuencia de argumentos 
* 	adicionales. Cada uno de estos contendrá un valor para ser insertado en el lugar de la etiqueta de formato.
*
* Valor de retorno: Retorna el número de caracteres imprimidos o un número negativo en caso de haber un error.
*
********************************************************************/
int my_vprintf(const char *sformat, ...);
#endif