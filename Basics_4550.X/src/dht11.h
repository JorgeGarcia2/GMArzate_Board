/*************************************************************************
* File: dht11.h
* Author: Jorge
* Date: September, 2020
*
*************************************************************************/

#ifndef DHT11_H
#define	DHT11_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "system.h"


#define DHT11Pin_In PORTCbits.RC0
#define DHT11Pin_Out LATCbits.LATC0
#define DHT11Pin_Tris TRISCbits.TRISC0


void DHT11_Init(void);

int DHT11_Wait4Resp(bool LtoH, int timeout_10us);

bool DHT11_MReq(void);

float DHT11_GetTemp(void);

float DHT11_GetRHum(void);

#endif	/* TIMER_H */