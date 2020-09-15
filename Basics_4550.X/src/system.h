/*************************************************************************
* File: dht11.h
* Author: Jorge
* Date: August, 2020
*
*************************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H


#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define _XTAL_FREQ  48000000
#define setbit (var, bit) ((var) |= (1<<(bit)))
#define clearbit (var, bit) ((var) =~ (1<<(bit)))

#include "print/my_print.h"
#include "serial.h"
#include "kbd.h"
//#include "buttons.h"
#include "leds.h"
#include "interrupts.h"
#include "timer.h"
#include "lcd.h"
#include "dht11.h"

void SYSTEM_Init(void);


#endif //SYSTEM_H
