#include "leds.h"

void LED_Enable(LED led)
{
    switch (led)
    {
        case L1: 
            L1_TRIS = 0;
            L1_LAT = LED_OFF;
            break;
        case L2: 
            L2_TRIS = 0;
            L2_LAT = LED_OFF;
            break;
        case L3: 
            L3_TRIS = 0;
            L3_LAT = LED_OFF;
            break;
        case L4: 
            L4_TRIS = 0;
            L4_LAT = LED_OFF;
    }
}

void LED_On(LED led)
{
    switch (led)
    {
        case L1: 
            L1_LAT = LED_ON;
            break;
        case L2: 
            L2_LAT = LED_ON;
            break;
        case L3: 
            L3_LAT = LED_ON;
            break;
        case L4: 
            L4_LAT = LED_ON;
    }
}

void LED_Off(LED led)
{
    switch (led)
    {
        case L1: 
            L1_LAT = LED_OFF;
            break;
        case L2:
            L2_LAT = LED_OFF;
            break;
        case L3: 
            L3_LAT = LED_OFF;
            break;
        case L4: 
            L4_LAT = LED_OFF;
    }
}

void LED_Toggle(LED led)
{
    switch (led)
    {
        case L1: 
            L1_LAT ^= 1;
            break;
        case L2: 
            L2_LAT ^= 1;
            break;
        case L3: 
            L3_LAT ^= 1;
            break;
        case L4: 
            L4_LAT ^= 1;
    }
}

void BLED_Enable(BILED biled)
{
    switch (biled)
    {
        case BL1: 
            BLG1_TRIS = 0;
            BLR1_TRIS = 0;
            BLG1_LAT = LED_OFF;
            BLR1_LAT = LED_OFF;
            break;
        case BL2:
            BLG2_TRIS = 0;
            BLR2_TRIS = 0;
            BLG2_LAT = LED_OFF;
            BLR2_LAT = LED_OFF;
    }
}

void BLED_Color(BILED biled, bool green, bool red)
{
    switch (biled)
    {
        case BL1: 
            BLG1_LAT = (green? LED_ON : LED_OFF);
            BLR1_LAT = (red? LED_ON : LED_OFF);
            break;
        case BL2: 
            BLG2_LAT = (green? LED_ON : LED_OFF);
            BLR2_LAT = (red? LED_ON : LED_OFF);
    }
}

void BLED_Toggle(BILED biled)
{
    switch (biled)
    {
        case BL1: 
            BLG1_LAT ^= 1;
            BLR1_LAT ^= 1;
            break;
        case BL2: 
            BLG2_LAT ^= 1;
            BLR2_LAT ^= 1;
    }
}
