#ifndef FORMAT_H
#define FORMAT_H

/** INCLUDES *******************************************************/
#include <stdbool.h>
#include "toString.h"

/** DEFINICIONES ***************************************************/
#define dPrec_f 4 //valor de precision por default de dPrec_f
#define dPrec_e 4 //valor de precision por default de dPrec_e
#define dPrec_g 6 //valor de precision por default de dPrec_g
#define dPrec_i 1 //valor de precision por default de dPrec_i


/*********************************************************************
* Funcion: bool searchc(char *str, char c);
*
* Descripción: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* Parámetros: 
* 	char *str - Cadena de caracteres donde se buscara el carácter.
*
* 	char c - Carácter a buscar.
*
* Valor de retorno: Devuelve true si se encontró el carácter c en str, de lo contrario 
* devuelve false.
*
********************************************************************/
bool searchc(char *str, char c);

/*********************************************************************
* Funcion: int posc(char *str, char c);
*
* Descripción: Esta función busca dentro de una cadena de caracteres, la posición en 
* la que se encuentra un carácter determinado.
*
* Parámetros: 
* 	char *str - Cadena de caracteres donde se buscara el carácter.
*
* 	char c - Carácter a buscar.
*
* Valor de retorno: Devuelve la posición en la que se encuentra el carácter c en 
* la cadena str, si no lo encuentra retornara un numero negativo.
*
********************************************************************/
int posc(char *str, char c);

/*********************************************************************
* Funcion: int roundStr(char *decnum, int e, int prn);
*
* Descripción: Esta función toma la cadena de caracteres decnum que representa 
* un número real en formato f, e o E,  y redondea el valor del número que este 
* en la posición que se indique en prn.
*
* Parámetros: 
* 	char* decnum - Cadena de caracteres con un número decimal ya sea en formato f o e.
* 	
*	int e - Posición en la que se encuentra el carácter ‘e’ en la cadena decnum sí está 
*	en formato e, en caso de ser formato f se deberá poner un número negativo.
*
*	int prn - Posición del digito a redondear.
*
* Valor de retorno: Devuelve 1 en caso de que se haya tenido que agregar un 1 por haber 
* redondeado un caso como 99.99 en formato f. En caso contrario Devuelve 0.
*
********************************************************************/
int roundStr(char *decnum, int e, int prn);

/*********************************************************************
* Funcion: void upperCL(char *str);
*
* Descripción: Esta función toma una cadena de caracteres y en donde encuentre letras minúsculas, 
* las convierte en mayúsculas.
*
* Parámetros: 
*	char *str - Cadena de caracteres.
* 	
* Valor de retorno:Ninguno.
*
********************************************************************/
void upperCL(char *str);

/*********************************************************************
* Funcion: void cleanS(char *str);
*
* Descripción: Esta función toma una cadena de caracteres y le pone a cada una de sus posiciones 
* el carácter nulo.
*
* Parámetros: 
* 	char *str - Cadena de caracteres.
* 	
* Valor de retorno: Ninguno.
*
********************************************************************/
void cleanS(char *str);

/*********************************************************************
* Funcion: void getWP(char *form, int *width, int *precision);
*
* Descripción: Esta función toma la cadena en la que se encuentra la etiqueta de formato de la 
* función my_vprintf() y obtiene las especificaciones de ancho de campo y precisión, así como 
* las banderas de zeros, alingL, sig, space y numeral.
*
* Parámetros: 
* 	char *form - Caracteres de la etiqueta de formato.
*
*	int *width - Puntero a la variable que especifica la el ancho de campo.
*
*	int *precision - Puntero a la variable que especifica la precisión.
* 	
* Valor de retorno: Ninguno.
*
********************************************************************/
void getWP(char *form, int *width, int *precision);

/*********************************************************************
* Funcion: void precF(char *str, int *precision);
*
* Descripción: Esta función toma la cadena que contiene los caracteres de un número decimal y
*  le aplica el formato de la precisión para tipo f.
*
* Parámetros: 
*	char *str - Cadena de caracteres.
* 	
*	int *precision - Puntero a la variable que especifica la precisión.
*
* Valor de retorno: Ninguno.
*
********************************************************************/
void precF(char *str, int *precision);

/*********************************************************************
* Funcion: void precE(char *str, int *precision);
*
* Descripción: Esta función toma la cadena que contiene los caracteres de un numero decimal y
* le aplica el formato de la precisión para tipo e o E.
*
* Parámetros: 
*	char *str - Cadena de caracteres.
* 	
*	int *precision - Puntero a la variable que especifica la precisión.
*
* Valor de retorno: Ninguno.
*
********************************************************************/
void precE(char *str, int *precision);

/*********************************************************************
* Funcion: void precG(char *str, int *precision);
*
* Descripción: Esta función toma la cadena que contiene los caracteres de un número decimal y
* le aplica el formato de la precisión para tipo g o G.
*
* Parámetros: 
*	char *str - Cadena de caracteres.
* 	
*	int *precision - Puntero a la variable que especifica la precisión.
*
* Valor de retorno: Ninguno. 
*
********************************************************************/
void precG(char *str, int *precision);

/*********************************************************************
* Funcion: void precI(char *str, int *precision);
*
* Descripción: Esta función toma la cadena que contiene los caracteres de un numero entero y
* le aplica el formato de la precisión para tipo i, d, u, o, x o X.
*
* Parámetros: 
*	char *str - Cadena de caracteres.
* 	
*	int *precision - Puntero a la variable que especifica la precisión.
*
* Valor de retorno: Ninguno.
*
********************************************************************/
void precI(char *str, int *precision);

/*********************************************************************
* Funcion: void precS(char *str, int *precision);
*
* Descripción: Esta función toma la cadena de caracteres y le aplica el formato de la precisión
* para tipo s.
*
* Parámetros: 
*	char *str - Cadena de caracteres.
* 	
*	int *precision - Puntero a la variable que especifica la precisión.
*
* Valor de retorno: Ninguno.
*
********************************************************************/
void precS(char *str, int *precision);

/*********************************************************************
* Funcion: void addOx(char *hoS, int num, char type);
*
* Descripción:Esta función toma la cadena de caracteres de un número octal o hexadecimal y le agrega
* los caracteres "0" o 0x" si la bandera numeral (#) se ha activado y num es diferente de 0. 
*
* Parámetros: 
* 	char *hoS - Cadena de caracteres de un numero octal o hexadecimal
*
* 	int num - Numero decimal representado en la cadena hoS.
*
*	char type - Tipo de formato de la cadena hoS. Para formato octal o y para para hexadecimal x.
*
* Valor de retorno: Ninguno.
*
********************************************************************/
void addOx(char *hoS, int num, char type);

/*********************************************************************
* Funcion: void addSig(char *numS, double num);
*
* Descripción: Esta función toma la cadena de caracteres de un número y le agrega un signo positivo
* o negativo en la posición 0, dependiendo del valor de num.
*
* Parámetros: 
*	char *numS - Cadena de caracteres.
* 	
* 	double num - Numero representado en la cadena numS.
*
* Valor de retorno: Ninguno.
*
********************************************************************/
void addSig(char *numS, double num);

/*********************************************************************
* Funcion: void setWidth(char *str, int *width);
*
* Descripción: Esta función toma la cadena de caracteres del argumento formateado y le aplica el ancho
* de campo en caso de que se hubiera especificado. También aplicara las banderas de cero y alineación.
*
* Parámetros: 
* 	char *str - Cadena de caracteres del argumento formateado.
*
* 	int *width - Puntero a la variable que especifica la el ancho de campo.
*
* Valor de retorno: Ninguno.
*
********************************************************************/
void setWidth(char *str, int *width);

#endif //FORMAT_H
