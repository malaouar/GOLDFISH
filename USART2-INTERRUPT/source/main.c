#include <stdint.h>

#include "int.h"
#include "uart.h"

// myitoa(int n, char* buffer, int base);
void itohex(unsigned int n);

void c_irq_handler(){
	char buffer[10];  // to covert numbers to ascii
	char c;
	int irq = 0, num = 0;

	irq = get_irq_num();
	num = get_irq_status();

	tty2_puts("Enter C irq handler.... \r\n");
	tty2_puts(" IRQ= ");
  itohex(irq);
	tty2_puts(" NUM= ");
	itohex(num);

	c = tty2_getc();
	tty2_putc(c);
}

//=========================================================
int main(){
	tty2_init();
	tty2_putc('L'); // test tty2 functions
	tty2_putc('M'); 
	tty2_puts(" hello SEB-SEB !!!\r\n");

	//enable tty2 receive interrupt 
	unmask_irq(IRQ_TTY2); 

	// wait for input from keyboard 
	while(1); 
	return 0;
}

//===========================================
void itohex(unsigned int n){
    unsigned int i=32, j;

    while(1){
        i-=4;
        j=(n>>i)&0xF;
        if(j>9) j+=0x37; else j+=0x30;
        tty2_putc(j);
        if(i==0) break;
    }
    tty2_putc(0x20); // add space at the end
}


