#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wiringPi.h>

#define UART_GPIO   (25)

//#define BIT_TIME_US 104 /* 9600 baud */
//#define BIT_TIME_US 833 /* 1200 baud */

//#define BIT_TIME_US     (1000000 / 600) /* 600 baud */
#define BIT_TIME_US     (1000000 / 300) /* 300 baud */

#define UART_GPIO_SET(x) do {if(x) {digitalWrite(UART_GPIO, HIGH);} else {digitalWrite(UART_GPIO, LOW);}} while(0)

void uart_reset()
{
    UART_GPIO_SET(1);
    usleep(100000);
}

int uart_putc(char c)
{
    int i;

    /* Start Bit */
    UART_GPIO_SET(0);

    usleep(BIT_TIME_US);

    for (i = 0; i < 8; ++i) { 
        UART_GPIO_SET((c >> i) & 1);
        usleep(BIT_TIME_US);
    }

    /* Stop Bit */
    UART_GPIO_SET(1);
    usleep(BIT_TIME_US);
    return 0;
}

int uart_puts(char *s)
{
    int i;

    for(i = 0; s[i]!= '\0'; i++) {
        uart_putc(s[i]);
    }

    return 0;
}

int main()
{

    if (wiringPiSetup() < 0) {
        fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
        return 1;
    }

    pinMode(UART_GPIO, OUTPUT);

    while(1) {
        uart_reset();
        uart_puts("aaaaaaaa");
    }

    return 0;
}
