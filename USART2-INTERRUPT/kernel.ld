
ENTRY(_start)

SECTIONS
{
 	.init 0x10000 : {
		*(.init)
	}

  .text : {
    *(.text)
    *(.rodata)   
  } 

. = ALIGN(4);
  .data	: {
   	  *(.data) 
   } 

  . = ALIGN(4);
  .bss : {
   		*(.bss) 
   } 

}

