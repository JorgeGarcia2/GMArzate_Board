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
extern bool reqKey;
uint8_t x;

void __interrupt() Interrupts()
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
    if (INTCONbits.RBIF)
    {
        INTCONbits.RBIF = OFF;
        x = (PORTB & 0xF0)>> 4;
        if((reqKey) && (x != 15))
            reqKey = false;
    }

}


void main(void) 
{
    SYSTEM_Init();
    TIMER0_SetH(0x48);
    TIMER0_SetL(0xE5);

    BLED_Color(BL1,0,0);
    BLED_Color(BL2,0,1);
    
    my_vprintf("BIENVENIDO\n\n");
    char c;

    while (1)
    {
        BLED_Color(BL2,1,0);
        c = KBD_GetChar();
        BLED_Color(BL2,0,1);
        if (c == 'A')
        {
            M1 = 0;
            M2 = 0;
            __delay_ms(1000);
            my_vprintf("Motor girando a la Derecha\n\n");
            M1 = 0;
            M2 = 1;
        }
        if (c == 'B')
        {
            M1 = 0;
            M2 = 0;
            __delay_ms(1000);
            my_vprintf("Motor girando a la Izquierda\n\n");
            M1 = 1;
            M2 = 0;
        }

        __delay_ms(2000);
    }
}