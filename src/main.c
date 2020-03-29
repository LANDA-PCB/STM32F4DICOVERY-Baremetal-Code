
#include "STM32F407VG.h"

/* Peripheral start addresses (common to all STM32 MCUs) */
#define PERIPH_BASE 0x40000000

/* RCC peripheral addresses applicable to GPIOD specific of a given STM32 MCU */
#define RCC_BASE (PERIPH_BASE + 0x23800)
#define RCC_APB1ENR ((uint32_t*)(RCC_BASE + 0x30))

/* GPIOD peripheral addresses specific of a given STM32 MCU */
#define GPIOD_BASE (PERIPH_BASE + 0x20C00)
#define GPIOD_MODER ((uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR ((uint32_t*)(GPIOD_BASE + 0x14))

/*Initialized global variable */
volatile uint32_t dataVar = 0x3F;

void delay(uint32_t count);

int main(void)
 {
/* Enable clock on GPIOD peripheral */
	 *RCC_APB1ENR = 0x8;
/* Configure the PD12 as output pull-up */
     *GPIOD_MODER |= 0x1000000; // Sets MODER14[1:0] = 0x01

while(dataVar == 0x3F)
	{
	*GPIOD_ODR = 0x1000;
	delay(200000);
	*GPIOD_ODR = 0x0;
	delay(200000);
	}
 }

/* Delay funtion definition */
void delay(uint32_t count)
{

   while(count--);

}


//
