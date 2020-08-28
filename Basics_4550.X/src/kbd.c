#include "kbd.h"

char keyPad[5][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'},
    {0,0,0,0}
};



void KBD_Init(void)
{
    PORTB = 0x00;
    TRISB = 0XF0;
    LATB = 0x00;
    INTCON2bits.RBPU = 0; //Pull up Enable
}

char KBD_GetChar(void)
{
    char key = 0;
    int row = 0, col = 0;

    for(col = 0; col <= 3; col++)
    {
        c1 = col == 0? 0:1;
        c2 = col == 1? 0:1;
        c3 = col == 2? 0:1;
        c4 = col == 3? 0:1;
        __delay_ms(10);

        if(!r1)
        {
            row = 0;
            break;
        }
        else if(!r2)
        {
            row = 1;
            break;
        }
        else if(!r3)
        {
            row = 2;
            break;
        }
        else if(!r4)
        {
            row = 3;
            break;
        }
        if (col == 3)
            row = 4;
    }
    key = keyPad[row][col];

    c1 = 0;
    c2 = 0;
    c3 = 0;
    c4 = 0;
    return key;
}

void KBD_InChar(void)
{
    while(1)
    {
        uint8_t newChar= (PORTB & 0xF0)>> 4;
        if(newChar == 14 || newChar == 13 || newChar == 11 || newChar == 7)
            return;
    }
}
