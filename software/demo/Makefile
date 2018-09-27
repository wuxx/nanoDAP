CC = gcc

ROOT = .

CFLAGS = -Wall 

.PHONY: all

all: 
	$(CC) $(CFLAGS) jtag/jtag_gpio.c -o jtag/jtag_gpio
	$(CC) $(CFLAGS) uart/uart_gpio.c -lwiringPi -o uart/uart_gpio
	cd swd && make

clean:	
	-rm -f *.o
	-rm -f swd_gpio
