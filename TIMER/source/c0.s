
.section .init
.globl _start
@ ================== interrupts vectors ===============
_start:
@ 8 words
	ldr pc,reset_addr	@ load PC with contents of address "reset_handler".
	ldr pc, undef_addr
	ldr pc, swi_addr
	ldr pc, prefab_addr
	ldr pc, datab_addr
	ldr pc, unused_addr
	ldr pc, irq_addr
	ldr pc, fiq_addr
@====================== adresses of interrupts handlers ===========
@ 8 words
reset_addr: .word reset		@ contents of this address = address of code labeled "reset". (word=4bytes)
undef_addr: .word halt
swi_addr: .word halt
prefab_addr: .word halt
datab_addr:.word halt
unused_addr: .word halt
irq_addr: .word irq_handler
fiq_addr:.word halt

@====================================
reset:
	@copy exceptions vector table from address 0x10000 to address 0x00
	mov r0, #0x10000
	mov r1, #0x00
	@ copy first 8 words (vectors)
	ldmia r0!,{r2-r9} @ copy 8 words in regs r2-r9 from address pointed to by r0 and increment r0 8 times after
	stmia r1!,{r2-r9} @ store 8 words in regs r2-r9 to address pointed to by r1 and increment r1 8 times after
	@ copy next 8 words (adresses)
	ldmia r0,{r2-r9}  @ here we don't need to increment since it's the last operation
	stmia r1,{r2-r9} 

	@ initialize stack pointer for svc_mode:
	mov sp,#0x10000    // top of first 64k block of RAM 
										 // 0x10000  is the load adress of kernel but since the stack is full descending
										 //  there is no problem !!!

	/* get Program Status Register */
	MRS r0, cpsr
	/* go in IRQ mode */
	BIC r1, r0, #0x1F
	ORR r1, r1, #0x12
	MSR cpsr, r1
	/* set IRQ stack */
	mov sp, #0x8000
	/* Enable IRQs */
	BIC r0, r0, #0x80
	/* go back in Supervisor mode */
	MSR cpsr, r0

	@ call C code main() function:
	bl main

	/* if main returns  */
halt:
	b halt		/*  loop forever */

/* ------------------------------------------------ */
@ IRQ handler:
irq_handler:
    push {r0-r12,lr} 	@ save r0 to r12 and lr in stack 
    bl c_irq_handler  @ call C code
    pop  {r0-r12,lr}	@ after return restore regs 
    subs pc,lr,#4			@ spcr =spsr, pc = lr-4 (cause pipe line)

@=============================================
/* some functions to use with asm or  C code */	

/* function to put contents of r1 in memory location pointed by r0 */
.globl poke
poke:
    str r1,[r0]
    bx lr

/* function to read contents of memory location pointed by r0 in r0*/
.globl peek
peek:
    ldr r0,[r0]
    bx lr
