#include <stdint.h>

//=============== USART2 BASE AND REGS ==========
#define tty2_base  0xFF012000
#define PUT_CHAR  0x00
#define BYTES_READY  0x04
#define CMD  0x08
#define DATA_PTR 0x10
#define DATA_LEN  0x14

//=================  USART COMMANDS ==============
#define CMD_INT_DISABLE	0x00
#define CMD_INT_ENABLE	0x01
#define CMD_WRITE_BUFFER	0x02
#define CMD_READ_BUFFER	0x03

//==================== FUNCTIONS ==============
void tty2_enable();  // enable tty2 port
void tty2_disable();  // disable tty2 port
void tty2_init();  // init tty2 port
void tty2_putc(char c);  // send a char
void tty2_puts(char *s);  // send a string
char tty2_getc();  //  get char
void tty2_gets(char *s, int count);  //  get string
int tty2_isdata(); // is there any available data?

//===============================
int main(){
	char c;

  tty2_init();
	tty2_putc('L'); 
	tty2_putc('M'); 
	tty2_puts(" hello SEB-SEB !!!");

	while (1) {
		if(tty2_isdata()) {
			c = tty2_getc();
			tty2_putc(c);
			if(c == 'q') break;
		}
	}
	
	tty2_disable();
	return 0;
}


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
	*((uint32_t *)(tty2_base + DATA_PTR)) = (uint32_t)s;
	*((uint32_t *)(tty2_base + DATA_LEN)) = count;
	*((uint32_t *)(tty2_base + CMD)) = CMD_READ_BUFFER;
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
	*((uint32_t *)(tty2_base + PUT_CHAR)) = c;
}

//====================================
void tty2_puts(char *s){
	while(*s) tty2_putc(*s++);
}

//=================================================
void tty2_enable(){
	*((uint32_t *)(tty2_base + CMD)) = CMD_INT_ENABLE;
}

//===========================================
void tty2_disable(){
	*((uint32_t *)(tty2_base + CMD)) = CMD_INT_DISABLE;
}
