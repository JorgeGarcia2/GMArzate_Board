/** INCLUDES *******************************************************/
#include "format.h"

/** VARIABLES ******************************************************/
bool sig, zeros, alingL, precInt, space, numeral;    //Signo, Ceros, Alineacion a la izquierda , precision


/*********************************************************************
* Funcion: bool searchc(char *str, char c)
********************************************************************/
bool searchc(char *str, char c) {
    int a; 
    for(a = 0; a < strlen(str); a++)
    {
        if (str[a]==c)
            return true;
    }
    return false;
}

/*********************************************************************
* Funcion: int posc(char *str, char c)
********************************************************************/
int posc(char *str, char c) {
    int a;
    for(a = 0; a < strlen(str); a++)
    {
        if (str[a]==c)
            return a;
    }
    return -1;
}


/*********************************************************************
* Funcion: int roundStr(char *decnum, int e, int prn);
*********************************************************************/
int roundStr(char *decnum, int e, int prn) {  
    int len = strlen(decnum);
    int p = posc(decnum,'.');  //Posición en la que se encuentra el punto decimal
    int i, k;

    /* Se recorre decnum desde el digito en la posición anterior a prn hasta 
     * el primero en busca del primer digito que no sea 9. Si el digito en la 
     * posición prn es mayor o igual que 5, el primer digito que no sea 9 se le 
     * sumara 1 y los que están antes de él tomaran el valor de 0. Si no se encontró 
     * ningún digito diferente de 9 como por ejemplo 99.999 o 9.99e+2, si es notación 
     * científica el primer digito a la izquierda del punto será 1 y los que estén a la 
     * izquierda serán 0 y se le sumara 1 al exponente (1.00e+3), en caso contrario  se 
     * añade un 1 en el siguiente valor posicional y los demás se ponen en cero (100.000).
     */
    for (k = prn - 1; k >= 0; k--) {
        if (decnum[k] < '9' && decnum[k] != '.') {
            if (decnum[prn] >= '5') {
                decnum[k]++; 
                while (k < prn) {
                    if (decnum[k+1] != '.')
                        decnum[k+1]='0';
                    k++;
                }
            }
            break;
        }
    }
    //Si todos los digitos a la izquierda de prn son 9 y esta en formato f, por ejemplo 99.999,
    //se añade un 1 en el siguiente valor posicional y los demás se ponen en cero (100.000).
    if (k == -1 && e == -1) {
        if (decnum[0] == '+' || decnum[0] == '-') {
            decnum[1] = '1';
            i = 2;
        }
        else {
            decnum[0] = '1';
            i = 1;
        }
        while (i < len) {
            if (decnum[i] == '.') {
                decnum[i]='0';
                decnum[i+1]='.';
                i++;
            }
            else
                decnum[i]='0';
            i++;
            return 1;
        }
    }
    //Si todos los digitos a la izquierda de prn son 9 y esta en formato e, por ejemplo 9.99e+2,
    //el primer digito a la izquierda del punto será 1 y los que estén a la izquierda serán 0 
    //y se le sumara 1 al exponente (1.00e+3),
    else if (k == -1 && e != -1) {
        decnum[p-1] = '1';
        for(i = p+1;i < e;i++)
            decnum[i] = '0';
        decnum[e+2]++;
    }
    return 0;
}

/*********************************************************************
* Funcion: void upperCL(char *str)
********************************************************************/
void upperCL(char *str) {
    int i; 
    for (i = 0; i <= strlen(str);i++) {
        if((str[i] >= 97) && (str[i] <= 122))
            str[i] = str[i] - 32;
    }
    
}

/*********************************************************************
* Funcion: void cleanS(char* str)
********************************************************************/
void cleanS(char *str) {
    int i,len;
    len = strlen(str);
    for(i=0;i<len;i++)
        str[i] = 0;
}

/*********************************************************************
* Funcion: void getWP(char *form, int *width, int *precision)
********************************************************************/
void getWP(char *form, int *width, int *precision) {
    int i, j, k;                        //Variables auxiliares para recorrer listas 
    int p;                              //Posicion en que se encuentra "."" en form
    int len = strlen(form);             //Numero de caracteres de la cadena str                
    char width_str[5] = "";             //Cadena de caracteres con el ancho de campo minimo del buffer
    char prec_str[5] = "";              //Cadena de caracteres con la precision del buffer

    i = 0;
    k = 0;
    zeros = false;
    precInt = false;

    sig = searchc(form, '+');
    alingL = searchc(form, '-');
    space = searchc(form, ' ');
    numeral = searchc(form, '#');

    p = posc(form, '.');

    for(j = 1; j < len; j++) {
        if(form[j] >= '0' &&  form[j] <= '9') {   //si hay un numero del 0 al 9 en form
            if ((j < p)|| (p < 0)) {        //Si j esta antes del punto ---> Anchura
                width_str[i] = form[j];
                i++;
            }
            else if (j > p) {               //Si j esta despues del punto ---> precision
                prec_str[k] = form[j];
                k++;
            }
        }
    }

    if(width_str[0] == '0')
      zeros = true;

    reverse(width_str);
    reverse(prec_str);

    if ((*width) == -1)
        (*width) = atoui(width_str);
    
    if (p >= 0 && (*precision) == -1)      //Si se especifico la precision
        (*precision) = atoui(prec_str);  
}

/*********************************************************************
* Funcion: void precF(char *str, int *precision)
********************************************************************/
void precF(char *str, int *precision) {
    int i, j, k;
    int len = strlen(str);
    int p = posc(str,'.');      //Posicion en la que se encuentra el punto decimal

    //Si no se especifica la precision en getWP() se utiliza la precision por defecto deinida en format.h
    if ((*precision) < 0)
        (*precision) = dPrec_f;

    i = p + (*precision) + 1;      //Posicion del digito que sera redondeado
    j = len - i;                //Se obtiene cuantos decimales seran recortados por la precision
    //En caso de que por lo menos un digito se recorta, se debe redondear i
    // Los digitos que se encuentren fuera del rango de precision se les asignara el caracter nulo
    if(j > 0) {
        roundStr(str, -1, i);
        i = ((*precision) == 0 && numeral == false)? p : (p + (*precision) + 1);
        for (k = i; k < len; k++)
            str[k] = 0;
    }
    //se agregan los decimales que falten en caso que no se complete la presicion
    else if (j < 0 && searchc(str,'.')) {
        for (k = len; k < len + (j * -1); k++)
            str[k] = '0';
    }
}

/*********************************************************************
* Funcion: void precE(char *str, int *precision)
********************************************************************/
void precE(char *str, int *precision) { 
    int i, j, k;
    int len = strlen(str);
    int posE = posc(str,'e');       //Posicion en que se encuentra la letra e o E
    int p = posc(str,'.');          //Posicion en la que se encuentra el punto decimal

    //Si no se especifica la precision en getWP() se utiliza la precision por defecto deinida en format.h
    if ((*precision) < 0)
        (*precision) = dPrec_e;

    i = p + (*precision) + 1;          //Posicion del digito que sera redondeado
    j = posE - i;                   //Se obtiene cuantos decimales seran recortados por la precision

    //En caso de que por lo menos un digito se recorta, se debe redondear i
    if (j > 0) {
        roundStr(str, posE, i);
        if((*precision) == 0 && numeral == false){
            i--;
            j++;
        }
        for (k = i; k < len; k++)
            str[k] = str[k+j];
    }
    //se agregan los decimales que falten en caso que no se complete la presicion
    else if (j < 0) {
        for (k = len - 1 + (j * -1); k >= posE; k--) {
            if (k >= i)
                str[k] = str[k+j];
            else
                str[k] = '0';
        }
    }
}

/*********************************************************************
* Funcion: void precG(char *str, int *precision)
********************************************************************/
void precG(char *str, int *precision) {
    int i, j, k;                
    int len = strlen(str);
    int posE = posc(str,'e');   //Posicion en que se encuentra la letra e o E
    int p = posc(str,'.');      //Posicion en la que se encuentra el punto decimal
    int f = 0;          
    int digS = 0;

    if ((*precision) == - 1)
        (*precision) = dPrec_g;

    k = (posE > 0)? posE : len;

    //Contador de digitos significantes
    //Guarda en f la posicion del primer digito significativo
    for (i = 0; i <= len;i++) {
        if (str[i] >= 48 &&  str[i] <= 57) {
            if (!(str[i] == 48 && digS == 0)){
                digS++;
                if (digS == 1)
                    f = i;
            }
        }
        else if (str[i]=='e')
            break;
    }
    for (i = k-1; i >= 0;i--) {
        if (str[i] == 48)
            digS--;
        else if ((str[i]>=49 &&  str[i] <= 57) || (str[i] == '.'))
            break;
    }

    if (digS > (*precision)) {
        i = f + (*precision);          //Posicion del digito que sera redondeado
        ////Si el primer digito significativo esta antes del punto y el ultimo esta despues se le sumara 1 por la posicion de '.' 
        if (f < p && i >= p) 
            i++;
        //Se obtiene cuantos digitos seran recortados por la precision
        j = k - i;
        /* En caso de que se tenga que recortar uno o mas digitos se aplicara la funcion roundStr(), esta funcion 
         * devolvera un 1 en caso de que se halla tenido que agregar un 1 por haber redondeado un caso como 99.99.
         * Si fue asi se debera de calcular de nuevo el primer digito significativo para calcular la posicion
         * del digito que sera dedondeado y apartir de ahi quitar los espacios recortados.
         */
        if (j > 0) {

            if (roundStr(str, posE, i) == 1) {
                for (k = 0; k <= strlen(str);i++) {
                    if (str[k] >= 49 &&  str[k] <= 57) {
                            f = k;
                            break;
                    }
                }
                i = f + (*precision);
            }
            for (k = i; k < len; k++)
                str[k] = str[k+j];
        }

        //Si hay ceros finales se truncan, al menos que se utilice la bandera # 
        if (numeral == false) {
            p = posc(str,'.');
            len = strlen(str);
            posE = posc(str,'e');
            k = (posE > 0)? posE : len;
            
            for (j = k-1; j >= p; j--){
                if (str[j] >= 49 &&  str[j] <= 57)
                    break;
                else {
                    len = strlen(str);
                    for(i = j; i <= len; i++) {
                        str[i] = str[i+1];
                    }
                }
            } 
        }
    }
}

/*********************************************************************
* Funcion: void precI(char *str, int *precision)
********************************************************************/
void precI(char *str, int *precision) {
    int i, j, k;
    int len = strlen(str);

    if (*precision == -1)
        (*precision) = dPrec_i;
    else
        precInt = true;

    j = (*precision) - len;
    k = len;
    if(j > 0) {
        for(i = (*precision)-1; i >= 0; i--) {
            k--;
            if (i>=j)
                str[i] = str[k];
            else
                str[i] ='0';
        }
    }
}

/*********************************************************************
* Funcion: void precS(char *str, int *precision)
********************************************************************/
void precS(char *str, int *precision) {
    int i;
    int len = strlen(str);

    if ((*precision) != -1) {
        for (i = (*precision); i < len;i++)
            str[i] = 0;
    }       
}

/*********************************************************************
* Funcion: void addSig(char *numS, double num)
********************************************************************/
void addSig(char *numS, double num) {
    int k;
    int len = strlen(numS);

    if(sig==true || num < 0.0) {
        for(k = len;k > 0;k--)
            numS[k]=numS[k-1];
        if (num > 0)
            numS[0]= '+';
        else
            numS[0]= '-';
    }
    else if(space == true) {
        for(k = len;k > 0;k--)
            numS[k]=numS[k-1];
        numS[0]= ' ';
    }
}

/*********************************************************************
* Funcion: void addOx(char *hoS, int num, char type)
********************************************************************/
void addOx(char *hoS, int num, char type) {
    int k;
    int len = strlen(hoS);

    if(numeral == true && num != 0 && type=='x') {
        for(k = len+1;k > 1;k--)
            hoS[k]=hoS[k-2];
        hoS[0]= '0';
        hoS[1]= 'x';
    }
    else if(numeral == true && num != 0 && type=='o') {
        for(k = len;k > 0;k--)
            hoS[k]=hoS[k-1];
        hoS[0]= '0';
    }
}

/*********************************************************************
* Funcion: void setWidth(char *str, int *width)
********************************************************************/
void setWidth(char *str, int *width) {
    int j;
    int len = strlen(str);
    int widthDif;

    widthDif = (*width) - len;
    if (widthDif > 0 && alingL == true) {
        for(j=0; j < widthDif; j++) {

            str[len] =' ';
            len++;
        }
    }
    else if(widthDif > 0 && alingL == false) {
        for(j = (*width)-1; j >= 0; j--) {
            len--;
            if (zeros == true && precInt == false) {
                if (j >= widthDif) {
                    if (str[len] == '+' || str[len] == '-')
                        str [j] = '0';
                    else
                        str[j] = str[len];
                }
                else {
                    if (str[j] != '+' && str [j] != '-')
                        str[j] = '0';
                }
            }
            else {
                if (j >= widthDif)
                    str[j] = str[len];
                else
                    str[j] =' ';
            }
        }
    }
}

