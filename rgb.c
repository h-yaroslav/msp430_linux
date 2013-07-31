//******************************************************************************
//  MSP430F20xx Demo - RGB LED
//
//  Description; RGB LED via P1.0-3, Tactile Button via P2.7
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F20xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          P2.7|-->Button-->Gnd
//            |                 |
//            |             P1.0|-->LED-G
//            |             P1.1|-->LED-B
//            |             P1.2|-->LED-Common
//            |             P1.3|-->LED-R
//
//  CChung
//  Giftware, no license, no warranty
//  July 2010
//  Built with msp430-gcc, flash via mspdebug
//******************************************************************************

#include <legacymsp430.h>
#include  <msp430g2452.h>

volatile unsigned int clicks=0;
volatile unsigned int ticks=0;
volatile unsigned int outp=0x00;

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    P1DIR |= 0x0f;                            // P1.0 output
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    CCR0 = 100;
    TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

    P2SEL = 0x00;
    P2REN = 0xc0;

    unsigned int rgb=0x00;
    unsigned int button=0;

    _BIS_SR(GIE);
    while (1) {
        if (P2IN&0x80) {
            if (button > 5) {        // button released
                rgb++;
                outp = ((rgb&0x04)<<1) | rgb&0x03;
            }//if
            button = 0;
        }//if
        else {
            button++;
        }//else
    }//while
}

// Timer A0 interrupt service routine
interrupt(TIMER0_A0_VECTOR) Timer_A(void) {
    clicks++;
    if (clicks&0x03) {
        P1OUT = 0x00;
    }//if
    else {
        unsigned int usep = outp;
        //_________ trying to compsensate for individual color brightness
        if ((usep&0x08)&&!(ticks%3))  usep &= ~0x08;
        if ((usep&0x02)&&!(ticks%9))  usep &= ~0x02;
        if ((usep&0x01)&&!(ticks%5))  usep &= ~0x01;
        P1OUT = usep;
        ticks++;
    }//else
}
