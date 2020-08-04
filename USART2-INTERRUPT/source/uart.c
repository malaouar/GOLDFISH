#include "uart.h"

//==========================
void tty2_init(){
	tty2_enable();
}

//===========================
int tty2_isdata(){
	int count = 0;
	count = *((int *)(tty2_base + BYTES_READY));
	return count;
}

//============================
void tty2_gets(char *s, int count){
	*((unsigned int *)(tty2_base + DATA_PTR)) = (unsigned int)s;
	*((unsigned int *)(tty2_base + DATA_LEN)) = count;
	*((unsigned int *)(tty2_base + CMD)) = CMD_READ_BUFFER;
}

//=====================================
char tty2_getc(){
	char buf[16];
	char data = 0;

	tty2_gets(buf, 1);
	data = buf[0];
	return  data;
}

//=======================================
void tty2_putc(char c){
	*((unsigned int *)(tty2_base + PUT_CHAR)) = c;
}

//====================================
void tty2_puts(char *s){
	while(*s) tty2_putc(*s++);
}

//=================================================
void tty2_enable(){
	*((unsigned int *)(tty2_base + CMD)) = CMD_INT_ENABLE;
}

//===========================================
void tty2_disable(){
	*((unsigned int *)(tty2_base + CMD)) = CMD_INT_DISABLE;
}
