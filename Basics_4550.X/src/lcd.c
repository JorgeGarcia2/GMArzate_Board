
#include "lcd.h"

bool lcd_r = 0;
int lcd_c = 0;

void LCD_Init(void)
{
    TRISD = 0x00;
    LCD_RW = 0;
    LCD_E = 0;
    LCD_RS = 0;

    __delay_ms(15);
    LCD_SendCmd(0x03,0);
    __delay_ms(4);
    LCD_SendCmd(0x03,0);
    __delay_ms(4);
    LCD_SendCmd(0x03,0);
    LCD_SendCmd(0x02,0);
    LCD_SendCmd(0x28,1);
    LCD_SendCmd(0x0E,1);
    LCD_SendCmd(0x01,1);
    __delay_ms(1);
    LCD_SendCmd(0x06,1);
    LCD_SendCmd(0x80,1);
}

void LCD_Lat(void)
{
    LCD_E = 1; 
    __delay_ms(1);     //waits for 39 us
    LCD_E = 0;
   
}

void LCD_SendNibble(uint8_t data)
{
    LCD_DATA &= 0x0F;
    LCD_DATA |= (data & 0xF0);
    LCD_Lat();
}

void LCD_SendCmd(uint8_t data,bool fbyte)
{
    LCD_RW = 0;
    LCD_RS = 0;
    if(fbyte)
        LCD_SendNibble(data);
    data <<= 4;
    LCD_SendNibble(data);
}


void LCD_WriteByte(char wData)
{
    LCD_RS = 1;
    LCD_SendNibble(wData);
    wData <<= 4;
    LCD_SendNibble(wData);
}

void LCD_WriteChar(char wData)
{

    LCD_WriteByte(wData);
    lcd_c++;

    if (lcd_c == 16 )
    {
        if(lcd_r == 0)
            LCD_SetRowCol(1,0);
    }
}

void LCD_CLS(void)//cleare screen
{
    LCD_SendCmd(0x01,1);
    __delay_ms(1);
    lcd_c = 0;
    lcd_r = 0;
}

void LCD_RH(void)//Return home
{
    LCD_SendCmd(0x02,1);
    __delay_ms(1);
    lcd_c = 0;
    lcd_r = 0;
}


void LCD_DisplayCtrl(bool disOn, bool curOn, bool curBlink)//0b00001ABC
{
    uint8_t cmd = 0b00001000;
    cmd |= (disOn << 2);
    cmd |= (curOn << 1);
    cmd |= (curBlink << 0);
    LCD_SendCmd(cmd,1);
}

void LCD_DisplayShift(bool sc, bool rl)//0b0001ABXX
{
    uint8_t cmd = 0b00010000;
    cmd |= (sc << 3);
    cmd |= (rl << 2);
    LCD_SendCmd(cmd,1);
}

void LCD_EntryMode(bool id, bool s)//0b000001AB
{
    uint8_t cmd = 0b00000100;
    cmd |= (id << 1);
    cmd |= (s << 0);
    LCD_SendCmd(cmd,1);
}

void LCD_SetCGRAM(uint8_t address)//0b01AAAAAA
{
    if (address < 0b01000000)
    {
        uint8_t cmd = 0b01000000;
        cmd |= address;
        LCD_SendCmd(cmd,1);
    }
}

void LCD_SetRowCol(bool row, uint8_t col)//0b01AAAAAA
{
    if (col < 16)
    {
        int cmd = ((row * 64) + col) + 128;
        LCD_SendCmd(cmd, 1);
        lcd_c = col;
        lcd_r = row;
    }
}

void CreateChar (char *pattern, uint8_t pos)
{
    int i = 0;
    pos *= 8;
     //Send the Address of CGRAM
    for (i=0; i<8; i++)
    {
        LCD_SetCGRAM (pos+i);
        LCD_WriteByte (pattern[i]);
    }
    LCD_SetRowCol(lcd_r, lcd_c);
}

void LCD_Write(char *str)
{
    int i = 0;
    while(str[i] != 0)
    {
        switch(str[i])
        {
            case '\n':
                LCD_SetRowCol(1, lcd_c);
                break;
            case '\r':
                lcd_c = 0;
                LCD_SetRowCol(lcd_r, lcd_c);
                break;
            default:
                LCD_WriteChar(str[i]);
        }
        i++;
    }
}

#ifdef MY_PRINT_H
int LCD_Printf(const char *restrict fmt, ...)
{
    char strout[STR_SIZE];
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = my_vsprintf(strout, fmt, ap);
    LCD_Write(strout);
    va_end(ap);
    return ret;
}
#endif