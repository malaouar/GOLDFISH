
#ifndef UART_H
#define UART_H

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

#endif
