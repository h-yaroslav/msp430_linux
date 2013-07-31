/* Blink Red LED example
 *
 * Compile:
 *      msp430-gcc -Os -mmcu=msp430g2452 -o led_button.elf led_button.c
 *
 *    where:
 *      -Os - optimize for size
 *
 * Install:
 *      sudo mspdebug rf2500
 *      erase
 *      prog led_button.elf
 *      run
 *
 * */

#include <msp430g2452.h>

#define true 1
#define false 0
#define R_LED BIT0     // Red LED
#define G_LED BIT6     // Green LED
#define BUTTON BIT3     // Button

void delay_ms(unsigned int ms){
    while(ms--){
        __delay_cycles(1000);
    }
}

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR = G_LED | R_LED;
    P1OUT = G_LED; //0xFF;

    while(true) {
        //if(( P1IN & BIT3 ) == 0 ) {
        //    P1OUT ^= R_LED;
        //} else {
        //    P1OUT ^= (R_LED | G_LED);
        //}
        if(!( P1IN & BIT3 )) {
            P1OUT ^= (R_LED | G_LED); // TODO handle button click
        } else {
            P1OUT ^= (G_LED | R_LED);
        }
        delay_ms(1000);
    }
}

/*
#include <msp430g2452.h>
#define pin0mask  (0x01 << 0)
#define pin3mask  (0x01 << 3)
#define pin6mask  (0x01 << 6)
int main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR = pin0mask | pin6mask;
    P1OUT = pin6mask;
    for( ; ; ) {
        unsigned int i;
        for( i = 0; i < 20000; i++ );
        if(( P1IN & pin3mask ) == 0 ) {
            P1OUT ^= pin0mask;
        } else {
            P1OUT ^= P1OUT ^ (pin0mask|pin6mask);
        }
    }
}
*/
