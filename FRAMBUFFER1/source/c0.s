
.section .init
.globl _start
_start:

	ldr r0,=0xff014000  @ framebuffer controlller base adress
	ldr r1,=0x30000			@ video RAM (framebuffer) start adress
	str r1, [r0, #0x10] @ set base adress

	@ fill video RAM with a given color starting from top left angle
	ldr r0,=0x30000			@ load framebuffer adress in r0
	ldr r1,=0x07E0      @ r1 = a color value (in 16bit RGB565 format: RED=0xF800, BLUE=0x001F, GREEN=0x07E0)
	ldr r3,=480*853*2		@ r3 = number of bytes in the framebuffer 
	eor r2, r2					@ clear r2
loop: 
	strh r1,[r0,r2]			@ save the low word in r1 to framebuffer position pointed to by (r0 + r2)
	add r2, #2					@ r2 = r2 + 2 (cause we save 16bits each time)
	teq r2, r3					@ r2 = r3 (all frame buffer filled)?
	bne loop						@ if No continue

halt:
	b halt		/*  loop forever */


/*
	@ to read framebuffer infos:
	ldr r0,=0xff014000  @ framebuffer controlller base adress
	ldr r1,[r0]					@ GET_WIDTH: Read framebuffer width in pixels. 
	ldr r2,[r0, #4]			@ GET_HEIGHT: Read framebuffer height in pixels.
	ldr r3,[r0, #0x24]	@ GET_FORMAT: Read framebuffer pixel format.
*/
