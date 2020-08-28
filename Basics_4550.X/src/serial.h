#ifndef SERIAL_H
#define SERIAL_H

#include <xc.h>
#include <string.h>
#include "system.h"

#define RX_TIMEOUT 5000

void SERIAL_Init(long BAUD);

void SERIAL_WriteChar(char data);

void SERIAL_Write(char *str);

void SERIAL_WriteLine(char *str);

char SERIAL_ReadChar(void);

int SERIAL_Read(char* str);


#endif