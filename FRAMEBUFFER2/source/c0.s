
.section .init
.globl _start
@ ================== interrupts vectors ===============
_start:
    ldr pc,reset_handler	@ load PC with contents of address "reset_handler".
@ put other vectors here
@	................................

@====================== adresses of interrupts handlers ===========
reset_handler:      
	.word reset		@ contents of this address = address of code labeled "reset". (word=4bytes)
@ put other interupts handlers here
@	................................

@====================================
reset:
    @ initialize stack pointer 
    mov sp,#0x10000    // top of first 64k block of RAM 
											 // 0x10000  is the load adress of kernel but since the stack is full descending
											 //  there is no problem !!!

    @ call C code:
    bl main

	/* if main returns  */
halt:
	b halt		/*  loop forever */

