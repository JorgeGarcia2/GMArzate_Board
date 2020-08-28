/* 
 * File:   kbd.h
 * Author: jorge
 *
 * Created on 18 de agosto de 2020, 12:32 PM
 */

#ifndef KBD_H
#define	KBD_H

#include "system.h"

#define c4 LATBbits.LATB0
#define c3 LATBbits.LATB1
#define c2 LATBbits.LATB2
#define c1 LATBbits.LATB3
#define r4 PORTBbits.RB4
#define r3 PORTBbits.RB5
#define r2 PORTBbits.RB6
#define r1 PORTBbits.RB7
//row as input
//collumns as output

void KBD_Init(void);

char KBD_GetChar(void);



#endif	/* KBD_H */

