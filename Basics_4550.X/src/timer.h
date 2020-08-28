/* 
 * File:   timer.h
 * Author: jorge
 *
 * Created on 19 de agosto de 2020, 02:48 PM
 */

#ifndef TIMER_H
#define	TIMER_H
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#define TIMER0_SetL(val) (TMR0L = val)
#define TIMER0_SetH(val) (TMR0H = val)

typedef enum
{
    PS0,    //1:2 Prescale value
    PS1,    //1:4 Prescale value
    PS2,    //1:8 Prescale value
    PS3,    //1:16 Prescale value
    PS4,    //1:32 Prescale value
    PS5,    //1:64 Prescale value
    PS6,    //1:128 Prescale value
    PS7     //1:256 Prescale value     
}PRESCALE;


void TIMER0_Int(bool t0_8b, bool t0_cs, bool t0_se, bool t0_psa);
void TIMER0_SetPs(PRESCALE prescale);

void TIMER1_Int(bool t0_8b, bool t0_cs, bool t0_se, bool t0_psa);
void TIMER1_SetPs(PRESCALE prescale);
void TIMER1_Set(uint16_t val);

#endif	/* TIMER_H */