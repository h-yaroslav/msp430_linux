/* Blink LED example
 *
 * Compile:
 *      msp430-gcc -Os -mmcu=msp430g2452 -o led_2.elf led_2.c
 *
 *    where:
 *      -Os - optimize for size
 *
 * Install:
 *      sudo mspdebug rf2500
 *      erase
 *      prog led_2.elf
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

int main(void) {
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

    while(true) {
        // Toggle P1.0 using exclusive-OR operation (^=)
        // P1OUT is another register which holds the status of the LED.
        // '1' specifies that it's ON or HIGH, while '0' specifies that it's
        // OFF or LOW. Since our LED is tied to P1.0, we will toggle the 0 bit
        // of the P1OUT register
        P1OUT ^= (R_LED);
		delay_ms(500);
        P1OUT ^= (G_LED);
    }
}
