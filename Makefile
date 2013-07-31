
CC=msp430-gcc
CPPFLAGS=-Os -mmcu=msp430g2452 -Wall

PROGS = \
		led_1 \
		led_2 \
		led_button \
		led_fade \
		led_red \
		led_red_green \
		rgb

all: $(PROGS)

clean::
	rm -f $(PROGS)
