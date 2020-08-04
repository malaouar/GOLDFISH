#include <stdint.h>
#include "timer.h"

void writel(unsigned int b, void  *addr){
	*(unsigned int  *) addr = b;
}

unsigned int readl( void *addr){
	return *(unsigned int *) addr;
}

// ======================= Goldfish specific Timer functions ================

void set_timer(unsigned long cycles){
	uint32_t timer_base = TIMER_BASE;
	unsigned long lo, hi, tmp;

	lo = readl((void *)timer_base + TIME_LOW);
	hi = (int64_t)readl((void *)timer_base + TIME_HIGH);

	hi = hi + cycles / 4096; /* Move 12 bits left. */
	tmp = lo + ((cycles % 4096) << 20);
	if(lo > tmp) {
		lo = tmp;
		hi = hi + 1;
	}
	else {
		lo = tmp;
	}

	writel(hi, (void *)timer_base + ALARM_HIGH);
	writel(lo, (void *)timer_base + ALARM_LOW);
}

//=====================================================
void clear_timer_int(void){
	uint32_t timer_base = TIMER_BASE;

	writel(1, (void *)timer_base + CLEAR_INTERRUPT);
}

//=====================================
unsigned long timer_read(void){
	uint32_t timer_base = TIMER_BASE;
	unsigned long  rv;

	rv = readl((void *)timer_base + TIME_LOW);
	rv |= (int64_t)readl((void *)timer_base + TIME_HIGH) << 32;

	return rv;
}

//==================================
void clear_alarm(void){
	uint32_t timer_base = TIMER_BASE;

	writel(1, (void *)timer_base + CLEAR_ALARM);
}
