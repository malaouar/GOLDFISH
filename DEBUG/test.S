	.syntax unified
	.cpu arm7tdmi
	.fpu softvfp

/******************************************************************************
 *
 * This is the code that gets called when the processor first starts execution
 * following a reset event.
 *
*******************************************************************************/
	.section	.text.ResetISR,"ax",%progbits
	.align	2
	.global	ResetISR
	.type	ResetISR, %function
ResetISR:
    mov   r0, #5         @ Load register r0 with the value 5
    mov   r1, #4         @ Load register r1 with the value 4
    add   r2, r1, r0     @ Add r0 and r1 and store in r2
ResetISR_STOP:
	b	ResetISR_STOP    @ Infinite loop to stop execution
	.size	ResetISR, .-ResetISR

