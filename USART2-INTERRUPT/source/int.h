#ifndef INT_H
#define INT_H

#define IO_START	0xff000000   // Physical Adress of IO

// ================ INTERRUPT CONTROLER REGISTERS ===========
#define INTERRUPT_BASE     (IO_START + 0x0)
#define INTERRUPT_STATUS       (0x00) // number of pending interrupts
#define INTERRUPT_NUMBER       (0x04)
#define INTERRUPT_DISABLE_ALL  (0x08)
#define INTERRUPT_DISABLE      (0x0c)
#define INTERRUPT_ENABLE       (0x10)

//=============== GOLD FISH IRQs ============
#define IRQ_PDEV_BUS    (1)
#define IRQ_TIMER       (3)
#define IRQ_TTY0    (4)
#define IRQ_RTC       (10)
#define IRQ_TTY1    (11)
#define IRQ_TTY2       (12)

//===================== FUNCTIONS ==============
void mask_irq(unsigned int irq);
void unmask_irq(unsigned int irq);
void disable_all_irq();
int get_irq_num();
int get_irq_status();

#endif
