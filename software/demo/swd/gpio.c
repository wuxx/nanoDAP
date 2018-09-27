#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "wiringPi.h"
#include "swd.h"

#define USE_wiringPi

#ifndef USE_wiringPi
void __gpio_init(int gpio_num, char *direct)
{
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "gpio mode %d %s", gpio_num, direct);
    system(cmd);
}

int gpio_get(int gpio_num)
{
    int i;
    FILE *fp;
    char cmd[512];
    char out[512];

    memset(out, 0, sizeof(out));
    snprintf(cmd, sizeof(cmd), "gpio read %d", gpio_num);

    fp = popen(cmd, "r");
    fread(out, sizeof(char), sizeof(out), fp);

    if (strcmp(out, "0\n") == 0) {
        pclose(fp);
        return 0;
    } else if (strcmp(out, "1\n") == 0) {
        pclose(fp);
        return 1;
    } else {
        printf("error: gpio %d read return [%s]\n", gpio_num, out);

        for(i = 0; i < 10; i++) {
            printf("[%d]: 0x%02x\n", i, out[i]);
        }

        exit(-1);
    }
}

void gpio_set(int gpio_num, int value)
{
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "gpio write %d %d", gpio_num, value);
    system(cmd);
    if (gpio_get(gpio_num) != value) {
        printf("error: gpio %d set %d fail \n", gpio_num, value);
        exit(-1);
    }

}

void gpio_mode(int gpio_num, char *direct)
{
    __gpio_init(gpio_num, direct);
}

void gpio_init()
{
    printf("SWD_CLK: gpio mode %d out\n", SWD_CLK);
    __gpio_init(SWD_CLK, "out");
    printf("SWD_IO:  gpio mode %d out\n", SWD_IO);
    __gpio_init(SWD_IO, "out");
}

#else
/*********************************************************************/

int gpio_get(int gpio_num)
{
    return digitalRead(gpio_num);
}

void gpio_set(int gpio_num, int value)
{
    if (value) {
        digitalWrite(gpio_num, HIGH);
    } else {
        digitalWrite(gpio_num, LOW);
    }
}

void gpio_mode(int gpio_num, char *direct)
{
    if (strcmp(direct, "out") == 0) {
        pinMode(gpio_num, OUTPUT); 
    } else if (strcmp(direct, "in") == 0) {
        pinMode(gpio_num, INPUT); 
    } else {
        printf("invalid direct %s\n", direct);
        exit(-1);
    }

}

void gpio_init()
{
    wiringPiSetup();

    pinMode(SWD_CLK, OUTPUT);
    pinMode(SWD_IO,  OUTPUT);

    digitalWrite(SWD_CLK, HIGH);
    digitalWrite(SWD_IO,  HIGH);
}

#endif /* USE_wiringPi */
