/* Blink LED example 
 *
 * Compile:
 msp430-gcc -Os -mmcu=msp430g2452 -o led.elf led.c

where:
-Os - optimize for size
 *
 * Install:
 sudo mspdebug rf2500
 erase
 prog led.elf
 run
 *
 * */

#include <msp430g2452.h>

#define true 1
#define false 0
#define R_LED BIT0      // Red LED
#define G_LED BIT6      // Green LED

void delay_ms(unsigned int ms){
    while(ms--){
        __delay_cycles(1);
    }
}

void main(void) {
    // Stop watchdog (WDT) timer. This line of code is needed at the beginning
    // of most MSP430 projects. This line of code turns off the watchdog timer,
    // which can reset the device after a certain period of time.
    WDTCTL = WDTPW + WDTHOLD;

    // P1DIR is a register that configures the direction (DIR) of a port pin
    // as an output or an input. To set a specific pin as output or input, we
    // write a '1' or '0' on the appropriate bit of the register.
    // P1DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>
    // Since we want to blink the on-board red LED, we want to set the
    // direction of Port 1, Pin 0 (P1.0) as an output. We do that by writing
    // a 1 on the PIN0 bit of the P1DIR register
    // P1DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>
    // P1DIR = 0000 0001
    // P1DIR = 0x01     <-- this is the hexadecimal conversion of 0000 0001
    P1DIR |= (R_LED + G_LED);

    P1OUT = 0xFF;

    unsigned int i, j;

    while(true) {
        for(i=0; i<255; i++){
            for(j=0; j<10; j++){
                P1OUT ^= P6;
                delay_ms(i);
                P1OUT ^= P6;
                P1OUT ^= P0;
                delay_ms(255-i);
                P1OUT ^= P0;
            }
        }
    }
}
