/******************************************************************************
 * @file     startup_STM32407VG.c
 * @brief    Device Startup File for STM32407VG
 * @version  V1.0
 * @date     29. March 2020
 ******************************************************************************/
/* MIT License
 * Copyright (c) 2020 LAND-PCB. All rights reserved.
 *
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*
*/

#include <stdint.h>
/* Memory start addresses (common to all STM32 MCUs) */
#define FLASH_BASE 0x08000000
#define SRAM_BASE 0x20000000

#define SRAM_SIZE 112*1024 // STM32F407VG has 112 KB of RAM
#define SRAM_END (SRAM_BASE + SRAM_SIZE)

/* User functions */
void __attribute__ ((noreturn,weak)) reset_handler(void);
void __initialize_data (uint32_t* flash_begin, uint32_t* data_begin, uint32_t* data_end);
void __initialize_bss ( uint32_t* bss_begin, uint32_t* bss_end);
extern void __attribute__((__noreturn__)) main(void);

/* Minimal vector table */
uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
(uint32_t *) SRAM_END, // initial stack pointer
(uint32_t *) reset_handler // Reset_Handler
};

// Begin address for the initialization values of the .data section; defined in linker script
extern uint32_t _sidata;
// Begin address for the .data section; defined in linker script
extern uint32_t _sdata;
// End address for the .data section; defined in linker script
extern uint32_t _edata;

// Begin address for the .bss section; defined in linker script
extern uint32_t _sbss;
// Begin address for the .bss section; defined in linker script
extern uint32_t _ebss;


void reset_handler(void)
     {

	__initialize_data(&_sidata, &_sdata, &_edata);
	__initialize_bss(&_sbss, &_ebss);
	 main();
	 while(1);

	 }

void __initialize_data (uint32_t* flash_begin, uint32_t* data_begin, uint32_t* data_end)
{
uint32_t *p = data_begin;
while (p < data_end)
*p++ = *flash_begin++;
}

void __initialize_bss ( uint32_t* bss_begin, uint32_t* bss_end)
{
uint32_t *p = bss_begin;
while (p < bss_end)
*p++ = 0;
}
