#include "system.h"
/*Register: CONFIG1
* PLL Prescaler Selection bits : Divide by 5 (20 MHz oscillator input)
* System Clock Postscaler Selection bits : [Primary Oscillator Src: /1][96 MHz PLL Src: /2]
* USB Clock Selection bit: USB clock: USB clock source comes from the 96 MHz PLL divided by 2
* Oscillator Selection bits: HS oscillator, PLL enabled (HSPLL)
* Fail-Safe Clock Monitor Enable bit: Fail-Safe Clock Monitor disabled
* Internal/External Oscillator Switchover bit: Oscillator Switchover mode disabled
*/
#pragma config PLLDIV = 5, CPUDIV = OSC1_PLL2, USBDIV = 2, FOSC = HSPLL_HS, FCMEN = OFF, IESO = OFF

/*Register: CONFIG2
* Power-up Timer Enable bit: PWRT disabled
* Brown-out Reset Enable bits: Brown-out Reset enabled in hardware only (SBOREN is disabled)
* Brown-out Reset Voltage bits: Minimum setting 2.05V
* USB Voltage Regulator Enable bit: USB voltage regulator enabled
* Watchdog Timer Enable bit: WDT disabled (control is placed on the SWDTEN bit)
* Watchdog Timer Postscale Select bits: 1:32768
*/
#pragma config PWRT = OFF, BOR = ON, BORV = 3, VREGEN = ON, WDT = OFF, WDTPS = 32768

/*Register: CONFIG3
* CCP2 MUX bit: CCP2 input/output is multiplexed with RC1
* PORTB A/D Enable bit: PORTB<4:0> pins are configured as digital I/O on Reset
* Low-Power Timer 1 Oscillator Enable bit: Timer1 configured for higher power operation
* MCLR Pin Enable bit: MCLR pin enabled; RE3 input pin disabled
*/
#pragma config CCP2MX = ON, PBADEN = OFF, LPT1OSC = OFF,  MCLRE = ON

/*Register: CONFIG4
* Stack Full/Underflow Reset Enable bit: Stack full/underflow will cause Reset
* Single-Supply ICSP Enable bit: Single-Supply ICSP disabled
* Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit: ICPORT disabled
* Extended Instruction Set Enable bit: Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
* Background Debugger Enable bit: Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
*/
#pragma config STVREN = ON, LVP = OFF, ICPRT = OFF, XINST = OFF, DEBUG = OFF

/*Register: CONFIG5
* Code Protection bit: Block 0 (000800-001FFFh) is not code-protected
* Code Protection bit: Block 1 (002000-003FFFh) is not code-protected
* Code Protection bit: Block 2 (004000-005FFFh) is not code-protected
* Code Protection bit: Block 3 (006000-007FFFh) is not code-protected
* Boot Block Code Protection bit: Boot block (000000-0007FFh) is not code-protected
* Data EEPROM Code Protection bit: Data EEPROM is not code-protected
*/
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF

/*Register: CONFIG6
* Write Protection bit: Block 0 (000800-001FFFh) is not write-protected
* Write Protection bit: Block 1 (002000-003FFFh) is not write-protected
* Write Protection bit: Block 2 (004000-005FFFh) is not write-protected
* Write Protection bit:Block 3 (006000-007FFFh) is not write-protected
* Configuration Register Write Protection bit: Configuration registers (300000-3000FFh) are not write-protected
* Boot Block Write Protection bit: 	Boot block (000000-0007FFh) is not write-protected
* Data EEPROM Write Protection bit: Data EEPROM is not write-protected
*/
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF, WRTC = OFF, WRTD = OFF

/*Register: CONFIG7
* Table Read Protection bit: Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks
* Table Read Protection bit: Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks
* Table Read Protection bit: Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks
* Table Read Protection bit: Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks
* Boot Block Table Read Protection bit: Boot block (000000-0007FFh) is not protected from table reads executed in other blocks
*/
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF

/** CONFIGURATION Bits *********************************************
#pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
#pragma config FOSC     = HSPLL_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON      //USB Voltage Regulator
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
//#pragma config CCP2MX   = ON
#pragma config STVREN   = ON
#pragma config LVP      = OFF
//#pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
#pragma config XINST    = OFF       // Extended Instruction Set
#pragma config CP0      = OFF
#pragma config CP1      = OFF
//#pragma config CP2      = OFF
//#pragma config CP3      = OFF
#pragma config CPB      = OFF
//#pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
//#pragma config WRT2     = OFF
//#pragma config WRT3     = OFF
#pragma config WRTB     = OFF       // Boot Block Write Protection
#pragma config WRTC     = OFF
//#pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
//#pragma config EBTR2    = OFF
//#pragma config EBTR3    = OFF
 * #pragma config EBTRB    = OFF*/


void SYSTEM_Init(void)
{
    LCD_Init();
    KBD_Init();
    //Using interrupts
    INTERRUPT_Init();
    //INTERRUPT_Rb();

    //Using timer 0
    TIMER0_Int(0, 0, 0, 0);
    TIMER0_SetPs(PS6);
    INTERRUPT_Tmr0();

    //Using SW3 and SW4
    //BUTTON_Enable(SW3);

    //Using LEDs
    BLED_Enable(BL1);
    BLED_Enable(BL2);
    //LED_Enable(L1);
    //LED_Enable(L4);

    //Using module ESUART
    SERIAL_Init(9600);
    //Config GPIO


}
