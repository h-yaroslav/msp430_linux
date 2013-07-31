/* Blink LED example 
 *
 * Compile:
 *      msp430-gcc -Os -mmcu=msp430g2452 -o led_1.elf led_1.c
 *
 *    where:
 *      -Os - optimize for size
 *
 * Install:
 *      sudo mspdebug rf2500
 *      erase
 *      prog led_1.elf
 *      run
 *
 * */

#include <msp430g2452.h>

#define true 1
#define false 0

void delay(unsigned int d) {
    unsigned int i;
    unsigned int j;
    for (i = 0; i<2; i++) {
    for (j = 0; j<d; j++) {
        __nop();
    }
    }
}

int main(void) {
    // Stop watchdog (WDT) timer. This line of code is needed at the beginning
    // of most MSP430 projects. This line of code turns off the watchdog timer,
    // which can reset the device after a certain period of time.
    WDTCTL = WDTPW | WDTHOLD;
    
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
    P1DIR = 0xFF;
    P1OUT = 0x01;

    while(true) {
        P1OUT = ~P1OUT;
        delay(0xffff);
    }
}
