/*
 * File:   buttons.h
 * Author: jorge
 *
 * Created on 18 de agosto de 2020, 01:11 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#include<xc.h>
#include <stdbool.h>

#define SW1_PORT  PORTBbits.RB0 //GMArzate BOARD Switch 1
#define SW2_PORT  PORTBbits.RB1 //GMArzate BOARD Switch 2
#define SW3_PORT  PORTBbits.RB2 //GMArzate BOARD Switch 3
#define SW4_PORT  PORTBbits.RB3 //GMArzate BOARD Switch 4

#define SW1_TRIS  TRISBbits.TRISB0
#define SW2_TRIS  TRISBbits.TRISB1
#define SW3_TRIS  TRISBbits.TRISB2
#define SW4_TRIS  TRISBbits.TRISB3

#define BUTTON_PRESSED 0

typedef enum
{
    SW1,
    SW2,
    SW3,
    SW4
}BUTTON;

void BUTTON_Enable(BUTTON button);

bool BUTTON_IsPressed(BUTTON button);



#endif	/* BUTTONS_H */
