/*------------------------------------------------------------------------*/
/* Universal string handler for user console interface  (C)ChaN, 2011     */
/*------------------------------------------------------------------------*/

#ifndef _STRFUNC
#define _STRFUNC


#define dev_out(func) func_out = (void(*)(unsigned char))(func)

extern void (*func_out)(unsigned char);
void putc (char c);
void puts (const char* str);
void printf (const char* fmt, ...);
void sprintf (char* buff, const char* fmt, ...);

#define DW_CHAR		sizeof(char)
#define DW_SHORT	sizeof(short)
#define DW_LONG		sizeof(long)


#endif
