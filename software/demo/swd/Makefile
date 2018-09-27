CC = gcc

ROOT = .

INCLUDE=$(ROOT)/locallib/include/wiringPi

CFLAGS = -Wall -I$(INCLUDE) 

.PHONY: all

all: 
	$(CC) $(CFLAGS) -c gpio.c -o gpio.o
	$(CC) $(CFLAGS) -c swd_gpio.c  -o swd_gpio.o
	$(CC) gpio.o swd_gpio.o $(ROOT)/locallib/lib/libwiringPi.a -lpthread -o swd_gpio

clean:	
	-rm -f *.o
	-rm -f swd_gpio
