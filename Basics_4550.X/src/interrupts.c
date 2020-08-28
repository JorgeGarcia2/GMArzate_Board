#include "interrupts.h"

void INTERRUPT_Init(void)
{
	RCONbits.IPEN = OFF;  //IPEN: Interrupt Priority Enable bit 
    //depending of IPEN value
    INTCONbits.GIEH = ON; // GIE/GIEH: Global Interrupt Enable bit/ Enables all high priority interrupts 
    INTCONbits.GIEL = ON; //PEIE/GIEL: Peripheral Interrupt Enable bit/  Enables all low priority peripheral interrupts 
}

void INTERRUPT_Int0(bool edge)
{
	TRISBbits.RB0 = IN;
	INTCONbits.INT0IE = ON; //INT0IE: INT0 External Interrupt Enable bit 
    INTCON2bits.INTEDG0 = edge; //INTEDG0: External Interrupt 0 Edge Select bit
	INTCONbits.INT0IF = OFF; //INT0IF: INT0 External Interrupt Flag bit 
}

void INTERRUPT_Int1(bool edge)
{
    TRISBbits.RB1 = IN;
	INTCON3bits.INT1IE = ON; //INT1IE: INT1 External Interrupt Enable bit
	INTCON2bits.INTEDG1 = edge; //INTEDG1: External Interrupt 1 Edge Select bit
    INTCON3bits.INT1IF = OFF; //INT1IF: INT1 External Interrupt Flag bit
    //INTCON3bits.INT1IP = 0; //INT1IP: INT1 External Interrupt Priority bit
}

void INTERRUPT_Int2(bool edge)
{
    TRISBbits.RB2 = IN;
	INTCON3bits.INT2IE = ON; //INT2IE: INT2 External Interrupt Enable bit
	INTCON2bits.INTEDG2 = edge; //INTEDG2: External Interrupt 2 Edge Select bit
    INTCON3bits.INT2IF = OFF; //INT2IF: INT2 External Interrupt Flag bit
    //INTCON3bits.INT2IP = 0; //INT2IP: INT2 External Interrupt Priority bit
}

void INTERRUPT_Rb(void)
{
	INTCONbits.RBIE = ON; //RBIE: RB Port Change Interrupt Enable bit 
	INTCONbits.RBIF = OFF; //RBIF: RB Port Change Interrupt Flag bit
	//INTCON2bits.RBIP = 0; //RBIP: RB Port Change Interrupt Priority bit
}

void INTERRUPT_Tmr0(void)
{
	INTCONbits.TMR0IE = ON;//TMR0IE: TMR0 Overflow Interrupt Enable bit 
	INTCONbits.TMR0IF = OFF; //TMR0IF: TMR0 Overflow Interrupt Flag bit 
    //INTCON2bits.TMR0IP = 0; //TMR0IP: TMR0 Overflow Interrupt Priority bit
}

void INTERRUPT_RX(void)
{
	PIE1bits.RCIE = ON;//RX: RX Interrupt Enable bit 
    //IPR1bits.RCIP = OFF = 0; //TMR0IP: TMR0 Overflow Interrupt Priority bit
}


