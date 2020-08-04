#ifndef TIMER_H
#define TIMER_H

#define TIMER_BASE     (0xff000000 + 0x3000)

/* Refer to arch/arm/mach-goldfish/include/mach/timer.h */
// we use enum instead of multiple #define 
enum {
	TIME_LOW          = 0x00,
	TIME_HIGH         = 0x04,
	ALARM_LOW         = 0x08,
	ALARM_HIGH        = 0x0c,
	CLEAR_INTERRUPT   = 0x10,
	CLEAR_ALARM       = 0x14,
};

void set_timer(unsigned long cycles);
void clear_timer_int();
unsigned long timer_read();
void clear_alarm();


#endif
