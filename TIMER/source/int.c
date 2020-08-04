#include "int.h"

//=========================================================
//Writing an interrupt number to INTERRUPT_DISABLE register it will disable the specified interrupt.
void mask_irq(unsigned int irq){
	*((unsigned int *)(INTERRUPT_BASE + INTERRUPT_DISABLE)) = irq;
}

//=========================================================
//Writing an interrupt number to INTERRUPT_ENABLE register it will enable the specified interrupt.
void unmask_irq(unsigned int irq){
	*((unsigned int *)(INTERRUPT_BASE + INTERRUPT_ENABLE)) = irq;
}

//=========================================================
//Writing any value other than 0 DISABLE_ALL register to it will disable all interrupts.
void disable_all_irq(){
	*((unsigned int *)(INTERRUPT_BASE + INTERRUPT_DISABLE_ALL)) = 1;
}

//=========================================================
// INTERRUPT_NUMBER register contains the lowest pending, enabled interrupt number
int get_irq_num(){
	return *((unsigned int *)(INTERRUPT_BASE + INTERRUPT_NUMBER));
}

//=========================================================
// INTERRUPT_STATUS register contains the number of pending interrupts.
int get_irq_status(){
	return *((unsigned int *)(INTERRUPT_BASE + INTERRUPT_STATUS));
}

