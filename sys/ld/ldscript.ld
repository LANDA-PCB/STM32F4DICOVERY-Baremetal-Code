
/* memory layout for an STM32F407VG */

MEMORY
{
 FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
 SRAM (xrw) : ORIGIN = 0x20000000, LENGTH = 96K
}

ENTRY(reset_handler) 

SECTIONS
{
     . = ORIGIN(FLASH);
     .text : ALIGN(4)
     {
     *(.isr_vector)             /* Vector table */
     *(.text)                   /* Program code */
     *(.text*)                  /* Merge all .text.* sections inside the .text section */
     KEEP(*(.isr_vector))       
     } >FLASH
     
     _sidata = LOADADDR(.data); /* Used by the startup to initialize data */  
    
     . = ORIGIN(SRAM);    
     .data : ALIGN(4)
     {
     _sdata = .;               /* create a global symbol at data start */
     *(.data)
     *(.data*)
     . = ALIGN(4);
     _edata = .;               /* define a global symbol at data end */
     } >SRAM AT>FLASH 
     
     
     .bss : ALIGN(4)
    {
    _sbss = .;                /* define a global symbol at bss start */
   *(.bss .bss*)
   *(COMMON)

   . = ALIGN(4);
   _ebss = .;                  /* define a global symbol at bss end */
   } >SRAM AT>SRAM
     
     
}
 