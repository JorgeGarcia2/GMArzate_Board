#include "timer.h"

uint8_t PS_TMR0 = 0;
uint8_t PS_TMR1 = 0;

void TIMER0_Int(bool t0_8b, bool t0_cs, bool t0_se, bool t0_psa)
{
    T0CONbits.TMR0ON = 1; //Timer 0: ON / OFF
    T0CONbits.T08BIT = t0_8b; //Timer 0: 8 bit timer/counter / 16 bit timer/counter
    T0CONbits.T0CS = t0_cs; //Timer 0 clock source: T0CKI / CLKO
    T0CONbits.T0SE = t0_se; //Timer 0 source edge: high to low / low to high
    T0CONbits.PSA = t0_psa; //Timer 0 preescaler: is not assigned / is assigned
    if (t0_cs)
        TRISAbits.RA4 = 1; //RA4 as an input
}
void TIMER0_End(void)
{
    T0CONbits.TMR0ON = 0;
}

void TIMER0_SetPs(PRESCALE prescale)
{
    switch (prescale)
    {
        case PS0: //Timer 0 prescale = 000
            T0CONbits.T0PS0 = 0;
            T0CONbits.T0PS1 = 0;
            T0CONbits.T0PS2 = 0;
            break;
        case PS1:
            T0CONbits.T0PS0 = 1;
            T0CONbits.T0PS1 = 0;
            T0CONbits.T0PS2 = 0;
            break;
        case PS2:
            T0CONbits.T0PS0 = 0;
            T0CONbits.T0PS1 = 1;
            T0CONbits.T0PS2 = 0;
            break;
        case PS3:
            T0CONbits.T0PS0 = 1;
            T0CONbits.T0PS1 = 1;
            T0CONbits.T0PS2 = 0;
            break;
        case PS4:
            T0CONbits.T0PS0 = 0;
            T0CONbits.T0PS1 = 0;
            T0CONbits.T0PS2 = 1;
            break;
        case PS5:
            T0CONbits.T0PS0 = 1;
            T0CONbits.T0PS1 = 0;
            T0CONbits.T0PS2 = 1;
            break;
        case PS6:
            T0CONbits.T0PS0 = 0;
            T0CONbits.T0PS1 = 1;
            T0CONbits.T0PS2 = 1;
            break;
        case PS7:
            T0CONbits.T0PS0 = 1;
            T0CONbits.T0PS1 = 1;
            T0CONbits.T0PS2 = 1;
    }
    PS_TMR0 = prescale;
}

void TIMER0_SetReg(uint16_t val)
{
    TMR0H = val >> 8;
    TMR1L = val;
}

bool TIMER0_SetTime(float time)
{
    float CT = 4.0/(_XTAL_FREQ/1000.0); //Cycle time in ms
    float MC = T0CONbits.T08BIT? 255: 65535;
    
    float tmax = CT * PS_TMR0 * MC;
    float tmin = CT * PS_TMR0;
    bool e = 0;
    
    if ((time <= tmax)&& (time >= tmin)) 
        TIMER0_SetReg(MC - lround(time/(CT*(PS_TMR0+1.0))));
    else
    {
        TIMER0_End();
        e = 1;
    }
    return e; 
}



void TIMER1_Int(bool t1_cs, bool t0_cs, bool t0_se, bool t0_psa)
{
    T1CONbits.TMR1ON = 1; //Timer1: ON / OFF
    T1CONbits.RD16 = 1; //Timer1: use one 16-bit register / use two 8-bit register
    T1CONbits.T1RUN = t0_cs; //Timer1 Device clock: derived from Timer1 oscillator / derived from another source
    T1CONbits.T1OSCEN = t0_se; //Timer1 oscillator: enabled / shut off
    T1CONbits.T1SYNC = t0_psa; //Timer1 External Clock Input Synchronization: Do not synchronize / synchronize
    T1CONbits.TMR1CS = t1_cs; //Timer1 Clock Source: External(RC0) or Timer1 oscillator / internal(FOSC/4)

}

void TIMER1_SetPs(PRESCALE prescale)
{
    switch (prescale)
    {
        case PS0: //Timer 0 prescale = 00
            T1CONbits.T1CKPS0 = 0;
            T1CONbits.T1CKPS1 = 0;
            break;
        case PS1: //Timer 0 prescale = 01
            T1CONbits.T1CKPS0 = 1;
            T1CONbits.T1CKPS1 = 0;
            break;
        case PS2: //Timer 0 prescale = 10
            T1CONbits.T1CKPS0 = 0;
            T1CONbits.T1CKPS1 = 1;
            break;
        case PS3: //Timer 0 prescale = 11
            T1CONbits.T1CKPS0 = 1;
            T1CONbits.T1CKPS1 = 1;
            break;
        default:
            break;
    }
    PS_TMR1 = prescale;
}

void TIMER1_SetReg(uint16_t val)
{
    TMR1H = val >> 8;
    TMR1L = val;
}
/*
void TIMER0_HSet(char val)
{
    TMR0H = val;
}*/
