
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
#include <math.h>

#define O1  LATCbits.LATC1
#define O2  LATCbits.LATC2

int count = 0;

void __interrupt() myISR()
{
    if (INTCONbits.TMR0IF)
    {
        //L1_LAT = TIMER0_SetTime(700.0);
        count++;
        if(count == 10)
        {
            BLED_Toggle(BL1);
            count = 0;
        }
        INTCONbits.TMR0IF = OFF;
    }
}

void SerialLCD_task()
{
    char txt[32]="";
    cleanS(txt);
    SERIAL_Read(txt);
    LCD_CLS();
    LCD_Printf("\rPC: %s",txt);

}

void testMath_task()
{
    LCD_CLS();
    LCD_Printf("\rCount = %d \n", count);
    SERIAL_Printf("\nCount = %d \n", count);
    __delay_ms(100);

}

void KBDSerial_task()
{
    KBD_InChar();
    char c = KBD_GetChar();

    switch (c)
    {
        case 'A':
            LCD_CLS();
            LCD_Printf("\rGiro Derecha \n\r%i .-.",123);
            SERIAL_Printf("\nGiro Derecha %s %d %.2f.-.","Okay",15,30.1475);
            O1 = 0;
            O1 = 1;
            break;
        case 'B':
            LCD_CLS();
            LCD_Printf("\rGiro Izquierda \n\r%.2f .-.",3.14);
            SERIAL_Printf("\nGiro Izquierda %f .-.",3.14);
            O1 = 1;
            O1 = 0;
            break;
        case 'C':
            LCD_CLS();
            LCD_Printf("\rMotor detenido \n\r%E .-.",123.56);
            SERIAL_Printf("\nMotor detenido %E .-.",123.56);
            O1 = 0;
            O1 = 0;
            break;
        case 'D':
            LCD_CLS();
            break;
        case '0':
            LCD_DisplayCtrl(1,0,0);
            break;
        case '*':
            LCD_DisplayCtrl(0,0,0);
            break;
        case '#':
            LCD_DisplayCtrl(1,1,1);
            break;
        default:
            LCD_CLS();
            LCD_Printf("\rTecla: %c .-.", c);
            SERIAL_Printf("\nTecla: %c .-.",c);
    }
    __delay_ms(500);
}

void dtll_task(void)
{
    float temperature;
    float relativeHum;

    if(DHT11_MReq() == 0)
    {
        temperature = DHT11_GetTemp();
        relativeHum = DHT11_GetRHum();
        LCD_CLS();
        LCD_Printf("\rTemp: %.1f C\n\rRel Hum: %.1f%%", temperature, relativeHum);
        SERIAL_Printf("\nTemperature: %.1f °C\nRelative Humedity: %.1f %%\n", temperature, relativeHum);
    }
    else 
    {
        LCD_CLS();
        LCD_Printf("\rERROR");
        SERIAL_Printf("\nERROR\n");
    }

    __delay_ms(2000);
}

void main(void)
{
    SYSTEM_Init();

    L1_LAT = TIMER0_SetTime(100);
    BLED_Color(BL1,0,0);


    LCD_DisplayCtrl(1,0,0);
    LCD_Printf("\rBIENVENIDO :)");
    SERIAL_Printf("BIENVENIDO :)\n\n");
    __delay_ms(1000);

    while (1)
    {
        dtll_task();
    }
}