#ifndef TOSTRING_H
#define	TOSTRING_H

/** INCLUDES *******************************************************/
#include <string.h>


/*********************************************************************
* Funcion: void reverse(char *str);
*
* Descripción: Invierte la cadena str.
*
* Parámetros: 
* 	char *str - Cadena de caracteres.
*
* Valor de retorno: Ninguno.
*
********************************************************************/
void reverse(char *str);

/*********************************************************************
* Funcion: char *itoa(char *str, int num, int base_);
*
* Descripción: Convierte un número entero a una cadena de carácter usando 
* una base especificada.
*
* Parámetros: 
* 	char *str - Cadena de caracteres en que se guardara el resultado.
*
* 	int num - Numero entero a convertir.
*
*	int base_ - Base numérica usada para la representación de num.
*
* Valor de retorno: Puntero a la cadena de carácter destino. La misma que el parámetro str.
*
********************************************************************/
char *itoa(char *str, long num, int base_);

/*********************************************************************
* Funcion: int atoui(char *str);
*
* Descripción: Convierte una cadena de caracteres con números en código ASCII a un entero.
*
* Parámetros: 
* 	char *str - Cadena de caracteres con números en código ASCII.
*
* Valor de retorno: Entero que representa el número de la cadena str.
*
********************************************************************/
int atoui(char *str);

/*********************************************************************
* Funcion: int normalize(double *val);
*
* Descripción: Normaliza los números reales de tal forma que quede representado por el 
* coeficiente, formado por un número real con un solo digito entero, un punto y varios 
* números fraccionarios, y de un exponente entero.
*
* Parámetros: 
* 	double *val - Número real a convertir.
*
* Valor de retorno: Numero entero con signo que corresponde al exponente.
*
********************************************************************/
int normalize(double *val);

/*********************************************************************
* Funcion: void ftoa(char *buffer, double value);
*
* Descripción: Convierte un número real a cadena de caracteres.
*
* Parámetros: 
* 	char *buffer - Cadena de caracteres destino.
*
*	double value - Número real a convertir.
*
* Valor de retorno: Ninguno.
*
********************************************************************/
void ftoa(char *buffer, double value);

/*********************************************************************
* Funcion: int ftoa_sci(char *buffer, double value);
*
* Descripción: Convierte un número real a cadena de carácter en formato de notación científica.
*
* Parámetros: 
* 	char *buffer - Cadena de caracteres destino.
*
*	double value - Número real a convertir.
*
* Valor de retorno: Numero entero con signo que corresponde al exponente.
*
********************************************************************/
int ftoa_sci(char *buffer, double value);

#endif	/* TOSTRING_H */

