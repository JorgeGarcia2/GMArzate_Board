#ifndef LCD_H
#define LCD_H

#include "system.h"

#define LCD_DATA    LATD
#define LCD_RS      LATDbits.LATD1 //LCD Register/Select pin
#define LCD_RW      LATDbits.LATD2 //LCD Read/Write pin
#define LCD_E       LATDbits.LATD0 //LCD Enable pin
#define LCD_D4      LATDbits.LATD4 //LCD Data 4 pin
#define LCD_D5      LATDbits.LATD5 //LCD Data 5 pin
#define LCD_D6      LATDbits.LATD6 //LCD Data 6 pin
#define LCD_D7      LATDbits.LATD7 //LCD Data 7 pin

/*********************************************************************
* Function: void LCD_Init(void);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_Init(void);

/*********************************************************************
* Function: void LCD_Lat(void);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_Lat(void);

/*********************************************************************
* Function: void LCD_SendNibble(uint8_t data);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_SendNibble(uint8_t data);

/*********************************************************************
* Function: void LCD_SendCmd(uint8_t data,bool fbyte);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_SendCmd(uint8_t data,bool fbyte);

/*********************************************************************
* Function: void LCD_WriteByte(char wData);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_WriteByte(char wData);

/*********************************************************************
* Function: void LCD_WriteChar(char WData);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_WriteChar(char WData);

/*********************************************************************
* Function: void LCD_CLS(void);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_CLS(void);

/*********************************************************************
* Function: void LCD_RH(void);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_RH(void);

/*********************************************************************
* Function: void LCD_DisplayCtrl(bool disOn, bool curOn, bool curBlink);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_DisplayCtrl(bool disOn, bool curOn, bool curBlink);

/*********************************************************************
* Function: void LCD_DisplayShift(bool sc, bool rl);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_DisplayShift(bool sc, bool rl);

/*********************************************************************
* Function: void LCD_EntryMode(bool id, bool s);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_EntryMode(bool id, bool s);

/*********************************************************************
* Function: void LCD_SetCGRAM(uint8_t address);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_SetCGRAM(uint8_t address);

/*********************************************************************
* Function: void LCD_SetRowCol(bool row, uint8_t col);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void LCD_SetRowCol(bool row, uint8_t col);

/*********************************************************************
* Function: void CreateChar (char *pattern, uint8_t pos);
*
* Description: Esta función es usada para buscar un carácter dentro de una cadena. 
*
* parameters: 
* 	--char *str - Cadena de caracteres donde se buscara el carácter.
*
* return value: None.
*
********************************************************************/
void CreateChar (char *pattern, uint8_t pos);

void LCD_Write(char *str);



#endif	/* LCD_H */
