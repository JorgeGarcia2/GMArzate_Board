/** INCLUDES *******************************************************/
#include "toString.h"


/*********************************************************************
* Funcion: void reverse(char *str)
********************************************************************/
void reverse(char *str) { 
    int i; 
    int j = strlen(str) -1;
    char auxstr[64] = " ";
    
    for(i = 0; i <= j;i++)
         auxstr[i] = str[j-i];

    strcpy(str, auxstr);
}
  
/*********************************************************************
* Funcion: char *itoa(char *str,int num, int base_)
********************************************************************/
char *itoa(char *str,long num, int base_) {
    int i = 0;
    int isNegative = 0;

    // En caso que se trate del numero 0, se imprime '0' directamente
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    //Solo se permiten numeros negativos para la base 10. Las otras bases se consideran sin signo.
    if (num < 0 && base_ == 10) {
        isNegative = 1;
        num = -num;
    }
  
    // procesa los digitos individualmente
    while (num != 0) { 
        long rem = num % base_;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base_;
    }

    str[i] = '\0'; // Agrega el caracter nullo al final de la cadena

    // Invierte la cadena
    reverse(str);

    return str;
}

/*********************************************************************
* Funcion: int atoui(char *str)
********************************************************************/
int atoui(char *str) {
    int i;
    int num = 0;
    int vp = 1;

    for (i = 0; i < strlen(str); i++) {
        if(str[i] >= '0' && str[i] <= '9'){
            num += (str[i] - 48) * vp;
            vp *= 10;
        }
        else
            break;
    }
    return num;
}

/*********************************************************************
* Funcion: int normalize(double *val)
********************************************************************/
int normalize(double *val) {
    int exponent = 0;
    double value = *val;
    
    while (value >= 1.0) {
        value /= 10.0;
        ++exponent;
    }

    while (value < 0.1) {
        value *= 10.0;
        --exponent;
    }
    *val = value;

    return exponent;
}

/*********************************************************************
* Funcion: int ftoa_sci(char *buffer, double value)
********************************************************************/
int ftoa_sci(char *buffer, double value) {
    //Esta función puede devolver un máximo de 6 dígitos decimales. 
    //Se recomienda usar 4 digitos, después de 4 digitos pude haber errores de precisión.
    int exponent = 0;
    static const int width = 6;

    if (value == 0.0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }

    if (value < 0.0) {
        value = -value;
    }

    exponent = normalize(&value);
    
    int digit = value * 10.0;
    *buffer++ = digit + '0';
    value = value * 10.0 - digit;
    --exponent;

    *buffer++ = '.';
    int i;
    for (i = 0; i < width; i++) {
        int digit = value * 10.0;
        *buffer++ = digit + '0';
        value = value * 10.0 - digit;
    }

    *buffer++ = 'e';
    if (exponent >= 0)
        *buffer++ = '+';
    else 
        *buffer++ = '-';
    itoa(buffer, exponent, 10);
    return exponent;
}

/*********************************************************************
* Funcion: void ftoa(char *buffer, double value)
********************************************************************/
void ftoa(char *buffer, double value) {  
    //Esta función puede devolver un máximo de 7 dígitos y tiene una 
    //Se recomienda usar 4 digitos, después de 4 digitos pude haber errores de precisión.

    int exponent = 0;
    int places = 0;
    static const int width = 7;

    if (value == 0.0) {
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = '0';
        buffer[3] = '\0';
        return;
    }         

    if (value < 0.0) {
        value = -value;
    }
    
    exponent = normalize(&value);

    while (exponent > 0) {
        int digit = value * 10;
        *buffer++ = digit + '0';
        value = value * 10 - digit;
        ++places;
        --exponent;
    }

    if (places == 0)
        *buffer++ = '0';
    if (places < width)
        *buffer++ = '.';

    while ((exponent < 0) && (places < width)) {
        *buffer++ = '0';
        ++exponent;
        ++places;
    }

    while (places < width) {
        int digit = value * 10.0;
        *buffer++ = digit + '0';
        value = value * 10.0 - digit;
        ++places;
    }
    *buffer = '\0';
}
