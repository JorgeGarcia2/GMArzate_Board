/*
 * File:   main.c
 * Author: jorge
 *
 * Created on 11 de agosto de 2020, 07:03 PM
 */
#include "system.h"
int count = 0;

void __interrupt() Interrupts()
{
    if (INTCONbits.TMR0IF)
    {
        uint16_t x;
        TIMER0_SetH(0x48);
        TIMER0_SetL(0xE5);
        count++;
        if(count == 20)
        {
            LED_Toggle(L4);
            count = 0;
        }
        INTCONbits.TMR0IF = OFF;
    }
}


void main(void) {
    SYSTEM_Init();
    TIMER0_SetH(0x48);
    TIMER0_SetL(0xE5);

    int i, x = 0;
    char usr[50] = "";
    char pass[50] = "";
    LED_On(L1);

    while (1)
    {
        x++;
        LED_Toggle(L1);
        BLED_Color(BL1,0,0);
        BLED_Color(BL2,0,0);

        for(i=strlen(usr);i>=0;i--)
            usr[i] = 0;

        for(i=strlen(pass);i>=0;i--)
            pass[i] = 0;

        my_vprintf("Ingrese el usuario: ");
        SERIAL_Read(usr);
        my_vprintf("%s\n",usr);
        if(strcmp(usr, "Jorge") == 0)
        {
            BLED_Color(BL2,1,0);
            my_vprintf("Ingrese la contrasenia: ");
            SERIAL_Read(pass);
            my_vprintf("%s\n",pass);
            if(strcmp(pass, "123456") == 0)
            {
                BLED_Color(BL1,1,0);
                my_vprintf("Bienvenido\n\n");
                x = 0;
            }
            else
            {
                my_vprintf("Usuario o contrasenia incorrecta\nNumero de intentos: %i\n",x);
                BLED_Color(BL1,0,1);
            }
        }
        else
            {
                my_vprintf("Usuario o contrasenia incorrecta\nNumero de intentos: %i\n\n",x);
                BLED_Color(BL2,0,1);
            }
        __delay_ms(2000);
    }
}