/* Blink Red LED example
 *
 * Compile:
 *      msp430-gcc -Os -mmcu=msp430g2452 -o led_red.elf led_red.c
 *
 *    where:
 *      -Os - optimize for size
 *
 * Install:
 *      sudo mspdebug rf2500
 *      erase
 *      prog led_red.elf
 *      run
 *
 * */

#include <msp430g2452.h>

#define true 1
#define false 0
#define R_LED BIT0     // Red LED
#define G_LED BIT6     // Green LED

void delay_ms(unsigned int ms){
    while(ms--){
        __delay_cycles(1000);
    }
}

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= G_LED;
    P1OUT = G_LED;

    while(true) {
            //delay_ms(500);
            P1OUT ^= R_LED;
            delay_ms(500);
            P1OUT ^= G_LED;
    }
}
