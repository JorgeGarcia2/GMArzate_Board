/* 
 * File:   leds.h
 * Author: jorge
 *
 * Created on 18 de agosto de 2020, 01:13 PM
 */

#ifndef LEDS_H
#define	LEDS_H

#include <xc.h>
#include <stdbool.h>

#define L1_LAT  LATBbits.LATB4 //GMArzate BOARD LED 1
#define L2_LAT  LATBbits.LATB5 //GMArzate BOARD LED 2
#define L3_LAT  LATBbits.LATB6 //GMArzate BOARD LED 3  
#define L4_LAT  LATBbits.LATB7 //GMArzate BOARD LED 4  
#define BLR1_LAT  LATEbits.LATE0 //GMArzate BOARD BICOLOR LED 1 - Green  
#define BLG1_LAT  LATEbits.LATE1 //GMArzate BOARD BICOLOR LED 1 - Red  
#define BLR2_LAT  LATCbits.LATC1 //GMArzate BOARD BICOLOR LED 2 - Green  
#define BLG2_LAT  LATCbits.LATC2 //GMArzate BOARD BICOLOR LED 2 - Red  

#define L1_TRIS  TRISBbits.TRISB4
#define L2_TRIS  TRISBbits.TRISB5
#define L3_TRIS  TRISBbits.TRISB6
#define L4_TRIS  TRISBbits.TRISB7
#define BLR1_TRIS  TRISEbits.RE0
#define BLG1_TRIS  TRISEbits.RE1
#define BLR2_TRIS  TRISCbits.RC1
#define BLG2_TRIS  TRISCbits.RC2

#define LED_ON 1
#define LED_OFF 0


typedef enum
{
    L1,
    L2,
    L3,
    L4
}LED;

typedef enum
{
    BL1,
    BL2
}BILED;


void LED_Enable(LED led);

void LED_On(LED led);

void LED_Off(LED led);

void LED_Toggle(LED led);

void BLED_Enable(BILED biled);

void BLED_Color(BILED biled, bool green, bool red);

void BLED_Toggle(BILED biled);

#endif	/* LEDS_H */

