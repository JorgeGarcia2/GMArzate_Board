#include "serial.h"

void SERIAL_Init(long BAUD)
{
    //Baudios
    uint16_t baudrate = (((_XTAL_FREQ/BAUD)/4)-1);
    //Configuración de los pines
    TRISCbits.RC6 = 1;      //RC6 = Tx -> Salida
    TRISCbits.RC7 = 1;      //RC7 = Rx -> Entrada
    
    //Configuración 
    RCSTAbits.SPEN = 1;     //Serial Port Enable bit
    TXSTAbits.SYNC = 0;     //Asincrono
    TXSTAbits.BRGH = 1;     //High Speed
    BAUDCONbits.BRG16 = 1;   //16 bits baud rate register
    SPBRGH = baudrate >> 8;
    SPBRG = baudrate;
    
    //Transmisión
    TXSTAbits.TX9 = 0;      //8 bits
    TXSTAbits.TXEN = 1;     //Transmit Enable bit

    //Recepción
    RCSTAbits.RC9 = 0;      //8 bits
    RCSTAbits.CREN = 1;     //Continuous Receive Enable bit
}

void SERIAL_WriteChar(char data){
    while (!TXSTAbits.TRMT); //waiting till TX register is empty
    TXREG = data;
}

void SERIAL_Write(char *str) {
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        SERIAL_WriteChar(str[i]);
    }
}

void SERIAL_WriteLine(char *str) {
    int i;
    SERIAL_WriteChar('\n');
    for (i = 0; i < strlen(str); i++)
    {
        SERIAL_WriteChar(str[i]);
    }
}

char SERIAL_ReadChar(void)
{
    while(!PIR1bits.RCIF);
    if (RCSTAbits.OERR)
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    return RCREG;
}

int SERIAL_Read(char* str)
{
    int len = 0;
    int timeout;
    
    if (RCSTAbits.OERR)
        {
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
        }
    
    while(1)
    {   
        timeout = 0;
        
        while(!PIR1bits.RCIF)
        {
            if (timeout == RX_TIMEOUT && len > 0)
                return len;
            else
                timeout++;        
        }
        str[len] = RCREG;
        len++;
    }
}


#ifdef MY_PRINT_H
int SERIAL_Printf(const char *restrict fmt, ...)
{
    char strout[STR_SIZE];
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = my_vsprintf(strout, fmt, ap);
    va_end(ap);
    SERIAL_Write(strout);
    return ret;
}
#endif