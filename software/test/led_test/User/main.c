#include "stm32f10x.h"

void delay_ms(uint32_t count)
{
	uint32_t i, x;
	for(; count != 0; count--) {
		for(i = 1000; i != 0; i--) {
			for(x = 72; x != 0; x--) {
			}
		}
	}
}

void gpio_init()
{
		GPIO_InitTypeDef gpio;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		gpio.GPIO_Pin = GPIO_Pin_All;	
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;   
		gpio.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOA, &gpio);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		gpio.GPIO_Pin = GPIO_Pin_All;	
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;   
		gpio.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOB, &gpio);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		gpio.GPIO_Pin = GPIO_Pin_All;	
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;   
		gpio.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOC, &gpio);
}

void gpio_on()
{
	GPIO_SetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOB, GPIO_Pin_All);
	GPIO_SetBits(GPIOC, GPIO_Pin_All);
}

void gpio_off()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);
	GPIO_ResetBits(GPIOB, GPIO_Pin_All);
	GPIO_ResetBits(GPIOC, GPIO_Pin_All);
}

int main(void)
{	
	gpio_init();
	
	while (1) {
		gpio_on();
		delay_ms(100);

		gpio_off();
		delay_ms(10);
	}

	return 0;
}
