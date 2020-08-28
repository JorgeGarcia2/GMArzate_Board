/*
 * File:   main.c
 * Author: jorge
 *
 * Created on 11 de agosto de 2020, 07:03 PM
 */
#include "system.h"

#define M1  LATDbits.LATD0
#define M2  LATDbits.LATD1

int count = 0;
char c = 0;
/*uint8_t newChar;
bool busyRB = false;*/

void __interrupt() myISR()
{
    if (INTCONbits.TMR0IF)
    {
        TIMER0_SetH(0x48);
        TIMER0_SetL(0xE5);
        count++;
        if(count == 2)
        {
            BLED_Toggle(BL1);
            count = 0;
        }
        INTCONbits.TMR0IF = OFF;
    }
    /*if (INTCONbits.RBIF && !busyRB)
    {
        busyRB = 1;
        newChar = (PORTB & 0xF0)>> 4;
        if(newChar == 14 || newChar == 13 || newChar == 11 || newChar == 7)
        {
            //c = newChar;
            c = KBD_GetChar();
        }
        INTCONbits.RBIF = OFF;
        busyRB = 0;
    }*/

}


void main(void)
{
    SYSTEM_Init();

    TIMER0_SetH(0x48);
    TIMER0_SetL(0xE5);
    BLED_Color(BL1,0,0);
    BLED_Color(BL2,0,1);

    __delay_ms(1000);
    my_vprintf("BIENVENIDO\n\n");

    while (1)
    {
        BLED_Toggle(BL2);
        KBD_InChar();
        c = KBD_GetChar();
        switch (c)
        {
            case 'A':
                my_vprintf("Motor girando a la Derecha\n\n");
                M1 = 0;
                M2 = 0;
                __delay_ms(1000);
                M1 = 0;
                M2 = 1;
                break;
            case 'B':
                my_vprintf("Motor girando a la Izquierda\n\n");
                M1 = 0;
                M2 = 0;
                __delay_ms(1000);
                M1 = 1;
                M2 = 0;
                break;
            case 'C':
                my_vprintf("Motor detenido\n\n");
                M1 = 0;
                M2 = 0;
            default:
                my_vprintf("La ultima tecla fue %u\n\n", c);

        }
        __delay_ms(2000);
    }
}
