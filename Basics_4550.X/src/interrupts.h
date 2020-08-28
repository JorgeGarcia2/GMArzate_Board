/* 
 * File:   interrupts.h
 * Author: jorge
 *
 * Created on 17 de agosto de 2020, 03:05 PM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include <xc.h>
#include <stdbool.h>
#define ON 1
#define OFF 0
#define IN 1
#define OUT 0


void INTERRUPT_Init(void);
void INTERRUPT_Int0(bool edge);
void INTERRUPT_Int1(bool edge);
void INTERRUPT_Int2(bool edge);
void INTERRUPT_Rb(void);
void INTERRUPT_Tmr0(void);
void INTERRUPT_RX(void);


#endif	/* INTERRUPTS_H */

