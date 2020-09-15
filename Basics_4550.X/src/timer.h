/*************************************************************************
* File: dht11.h
* Author: Jorge
* Date: August, 2020
*
*************************************************************************/

#ifndef TIMER_H
#define	TIMER_H
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "system.h"

typedef enum
{
    PS0 = 1,	//1:2 Prescale value
    PS1 = 3,    //1:4 Prescale value
    PS2 = 7,    //1:8 Prescale value
    PS3 = 15,   //1:16 Prescale value
    PS4 = 31,   //1:32 Prescale value
    PS5 = 63,   //1:64 Prescale value
    PS6 = 127,  //1:128 Prescale value
    PS7 = 255   //1:256 Prescale value     
}PRESCALE;


void TIMER0_Int(bool t0_8b, bool t0_cs, bool t0_se, bool t0_psa);
void TIMER0_End(void);
void TIMER0_SetPs(PRESCALE prescale);
void TIMER0_SetReg(uint16_t val);
bool TIMER0_SetTime(float time);

void TIMER1_Int(bool t0_8b, bool t0_cs, bool t0_se, bool t0_psa);
void TIMER1_SetPs(PRESCALE prescale);
void TIMER1_SetReg(uint16_t val);

#endif	/* TIMER_H */