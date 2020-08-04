
#include "int.h"
#include "uart.h"
#include "timer.h"
#include "printf.h"


void itohex(unsigned int n);

char ch=0;
//====================================
void c_irq_handler(){
	int irq = 0, num = 0;
	unsigned long tm = 0;

	irq = get_irq_num();
	num = get_irq_status();

	printf("=>Enter ARM_irq(%d), pending num=%d\n", irq, num);

	switch (irq) {
	case IRQ_TTY0:
		printf("=>IRQ_TTY0.\n");
		break;
	case IRQ_TTY1:
		printf("=>IRQ_TTY0.\n");
		break;
	case IRQ_TTY2:
	    ch = tty2_getc();
			printf("=>IRQ_TTY2. ch=%c\n", ch);
		
		if(ch == 't') {
			/* Unit test 4: set timer to trigger timer interrupt. */
			set_timer(0);
		}
		break;
	case IRQ_TIMER:
		/* We can clear either interrupt or alarm here.
		printf("IRQ_TIMER - clear interrupt.\n");	*/
		clear_alarm(); // or clear_timer_int();

		printf("=>IRQ_TIMER - clear alarm.\n");
		break;
	default:
		printf("=>Unknown IRQ %x.\n", irq);
		break;
	}
	tm = timer_read();
	printf("=>Exit ARM_irq(%d). tm=%lu\n", irq, tm);	
}


//=========================================================
int main(){
	unsigned long int tm = 0;

	tty2_init(); // must init usart 
	dev_out(tty2_putc); // tell to printf which output function to use

	printf("Enter main() ...\n");

	unmask_irq(IRQ_TIMER);
	unmask_irq(IRQ_TTY2);

	/* We do nothing in main() */
	for(;;) {
		if(ch != 0) {
			/* Unit test 1: print out serial input and time stamp. */
			printf("1. Command is %c. time=(%lu).\n", ch, tm);

			if(ch == 'd') {
				/* Unit test 2: disable timer interrupt. */
				mask_irq(IRQ_TIMER);
				printf("  - Disabled timer.\n");
			}

			if(ch == 'e') {
				/* Unit test 3: enable timer interrupt. */
				unmask_irq(IRQ_TIMER);
				printf("  - Enabled timer.\n");
			}

		    ch = 0;
		    tm = timer_read();
		    printf("2. ----- End loop (%lu) -----\n", tm);
		}  // end of if(ch!=0)

		else { tm = timer_read();}
	}
	return 0;
}

//===========================================
// Not used here
void itohex(unsigned int n){
    unsigned int i=32, j;

    while(1){
        i-=4;
        j=(n>>i)&0xF;
        if(j>9) j+=0x37; else j+=0x30;
        tty2_putc(j);
        if(i==0) break;
    }
    tty2_putc(0x20); // add a space at the end
}


