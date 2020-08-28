/** INCLUDES *******************************************************/
#include "my_print.h"

/*********************************************************************
* Funcion: int my_vprintf(const char *sformat, ... );
********************************************************************/

int my_vprintf(const char *sformat, ... ) {
	va_list valist;
	/* Inicializa valist para el numero de argumentos*/
	va_start(valist, 10);

	const char tipo[]= {'%','c','s','d','i','x','X','o','u','f','g','G','e','E','n'}; //Tipos de formato
	char string[STR_SIZE] = ""; //String de salida 
	int length = 0; //Tamaño del stting de salida
	int int_temp = 0; //Variable temporar tipo entero con signo
	uint16_t uint_temp = 0; //Variable temporar tipo entero sin signo
	int i, j, x;//Variables auxiliares para recorrer listas
	char char_temp[2] = {0,0}; //Variable temporar tipo char
	char *string_temp; //Variable temporar tipo string
	double double_temp; //Variable temporar tipo doble
	char ch[2]={0,0}; //Vector para recorrer los caracteres en my_vprintf();)
	char format[10]; // buffer para las especificaciones de los formatos
	char buffer[BUFF_SIZE] = " "; //buffer para los textos formateados
	int expA; //Exponente del numero en notacion cientifica "e"
	int prec; //Especificacion de la presicion 
	int width;//Especificacion del ancho de campo 
	int error = 0;

	/* Con ch se recorre cada uno de los caracteres de sformat,
	 * si inicia con el caracter '%' se le da el formato que se especifique,
	 * de lo contrario es un caracter ordinario que se agrega directamente a la cadena de salida
	 */
	while ( (ch[0] = *sformat++)) {
		if ( '%' == ch[0] ) {
			cleanS(buffer);
			cleanS(format);
			width = -1;
			prec = -1;

			format[0]='%';
			x = 0;
			i = 1;
			//Se obtienen las especificaciones de formato y se guardan en la cadena format
			while (x==0) {
				 format[i] = *sformat++;
				 for(j = 0; j < 15; j++) {
				    if (format[i] ==  tipo[j])
						x = i;
				 }
				 i++;
			}
			//En caso de ´que se encuentre el caracter '*' en format se le asignara el valor del siguiente 
			//argumento como especificacion del ancho de campo o precision
			i=0;
			for (j=0; j < x; j++) {
				if(format[j]=='*' && i==0) 
					width = va_arg(valist, int);
				else if(format[j]=='*' && i==1) 
					prec = va_arg(valist, int);
				else if(format[j]=='.')
					i++;
			}

			getWP(format, &width, &prec);
			//Si la especificacion del ancho de campo o precision supera al tomaño del buffer, definido en my_print.h, 
			//se le asignara el valor de 0.
			if (width >= BUFF_SIZE)
				width = 0;
			if (prec >= BUFF_SIZE)
				prec = 0;

			switch (format[x]) {
				case '%': //%%: imprime el caracter '%''  
					strcpy(buffer, "%");
					break;
				case 'c': //%c: imprime un caracter
					char_temp[0] = va_arg(valist, char);
					strcpy(buffer, char_temp);
					break;
				case 's': // %s: imprime una cadena de caracteres
					string_temp = va_arg(valist, char *);
					strcpy(buffer, string_temp);
					precS(buffer, &prec);
					break;
				case 'd': // %d: imprime un entero decimal con signo 
					int_temp = va_arg(valist, int);
					itoa(buffer, int_temp, 10);
					precI(buffer, &prec);
					addSig(buffer, (double)int_temp);
					break;
				case 'i': //%i: imprime un entero decimal con signo 
					int_temp = va_arg(valist, int);
					itoa(buffer, int_temp, 10);
					precI(buffer, &prec);
					addSig(buffer, (double)int_temp);
					break;
				case 'u': //%u: imprime un entero decimal sin signo 
					uint_temp = va_arg(valist,uint16_t);
					itoa(buffer, uint_temp, 10);
					precI(buffer, &prec);
					break;
				case 'X': // %X: imprime un entero hexadecimal sin signo (letras mayusculas)
					int_temp = va_arg(valist, uint16_t);
					itoa(buffer, int_temp, 16);
					precI(buffer, &prec);
					addOx(buffer, int_temp,'x');
					upperCL(buffer);
					
					break;
				case 'x': // %x: imprime un entero hexadecimal sin signo
					int_temp = va_arg(valist, uint16_t);
					itoa(buffer, int_temp, 16);
					precI(buffer, &prec);
					addOx(buffer, int_temp,'x');
					break;
				case 'o': // %o: imprime un entero octal sin signo
					int_temp = va_arg(valist, uint16_t);
					itoa(buffer, int_temp, 8);
					precI(buffer, &prec);
					addOx(buffer, int_temp,'o');
					break;
				case 'f': // %f: imprime un decimal de punto flotante
					double_temp = va_arg(valist, double);
					ftoa(buffer, double_temp);
					precF(buffer, &prec);
					addSig(buffer, double_temp);
					break;
				case 'e': // %e: Notacion cientifica (mantisa/exponente) usando el caracter e
					double_temp = va_arg(valist, double);
					ftoa_sci(buffer, double_temp);
					precE(buffer, &prec);
					addSig(buffer, double_temp);
					break;
				case 'E': // %E: Notacion cientifica (mantisa/exponente) usando el caracter E
					double_temp = va_arg(valist, double);
					ftoa_sci(buffer, double_temp);
					precE(buffer, &prec);
					addSig(buffer, double_temp);
					upperCL(buffer);
					break;
				case 'g': // %g: Usa el mas corto entre %e y %f
					double_temp = va_arg(valist, double);
					expA = ftoa_sci(buffer, double_temp);
					ftoa(buffer, double_temp);
					j=0;
					for (i=0;i<strlen(buffer);i++)
					{
						if (buffer[i]=='.')
							break;

						if (buffer[i]>=48 &&  buffer[i]<=57)
							j++;
					}
					if (prec == -1)
						prec = dPrec_g;
					if (expA <= -4 || j > prec)
						ftoa_sci(buffer, double_temp); 
					precG(buffer, &prec);
					addSig(buffer, double_temp);
					break;
				case 'G': // %G: Usa el mas corto entre %E y %f
					double_temp = va_arg(valist, double);
					expA = ftoa_sci(buffer, double_temp);
					ftoa(buffer, double_temp);
					j=0;
					for (i=0;i<strlen(buffer);i++)
					{
						if (buffer[i]=='.')
							break;

						if (buffer[i]>=48 &&  buffer[i]<=57)
							j++;
					}
					if (prec == -1)
						prec = dPrec_g;
					if (expA <= -4 || j > prec)
						ftoa_sci(buffer, double_temp);
					precG(buffer, &prec);
					addSig(buffer, double_temp);
					upperCL(buffer); 
					break;
				case 'n': // %n: Imprime un espacio en blanco
					strcpy(buffer," ");
					break;
				default:
					error--;
			}
			setWidth(buffer, &width);
			strcat(string, buffer);
			length += strlen(buffer);

		}
		else 
		{
			strcat(string, ch);
			length++;
		}
	}
	// limpia la memoria para valist
	va_end(valist);
	//Sustituir la funcion segun la libreria usada para la comunicacion con la terminal serie.
	SERIAL_Write(string); 
	return error < 0? error : length;
}