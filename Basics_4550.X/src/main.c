
/*************************************************************************
* File: msin.c
* Author: Jorge
* Date: August, 2020
*
* This program uses the PIC PIC18F4550 with GMArzate board.
* The program test peripherial devices on de board.
*
* The LCD is connected to PORTD.
*
*************************************************************************/


#include "system.h"

#define M1  LATCbits.LATC1
#define M2  LATCbits.LATC2

char Pattern1[] = {0x0e,0x0e,0x04,0x04,0x1f,0x04,0x0a,0x0a};
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

    __delay_ms(1000);
    my_vprintf("BIENVENIDO\n\n");

    LCD_DisplayCtrl(1,0,0);
    CreateChar (Pattern1, 0);

    while (1)
    {
        KBD_InChar();
        c = KBD_GetChar();

        switch (c)
        {
            case 'A':
                LCD_Write("Motor girando a la Derecha\n\r");
                my_vprintf("Motor girando a la Derecha\n\n");
                M1 = 0;
                M2 = 0;
                __delay_ms(1000);
                M1 = 0;
                M2 = 1;
                break;
            case 'B':
                LCD_Write("Motor girando a la Izquierda\n\r");
                my_vprintf("Motor girando a la Izquierda\n\n");
                M1 = 0;
                M2 = 0;
                __delay_ms(1000);
                M1 = 1;
                M2 = 0;
                break;
            case 'C':
                LCD_Write("Motor detenido\n");
                my_vprintf("Motor detenido\n\n");
                M1 = 0;
                M2 = 0;
                break;
            default:
                my_vprintf("La ultima tecla fue %u\n\n", c);
                if (c == '0')
                    LCD_CLS();
                else if (c == '*')
                    LCD_DisplayCtrl(0,0,0);
                else if (c == '#')
                    LCD_DisplayCtrl(1,1,1);
                else
                {
                    //LCD_WriteChar(0);
                    LCD_CLS();
                    LCD_SetRowCol(0, 3);
                    LCD_Write("BIENVENIDO\n :)");
                }
        }
        __delay_ms(500);
    }
}