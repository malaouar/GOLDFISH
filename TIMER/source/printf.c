/*------------------------------------------------------------------------/
/  Universal string handler for user console interface
/-------------------------------------------------------------------------*/
#include <stdarg.h>
#include "printf.h"


void (*func_out)(unsigned char);	/* Pointer to the output stream */
static char *outptr;

/*----------------------------------------------*/
/* Put a character                              */
/*----------------------------------------------*/

void putc (char c){
	//if (_CR_CRLF && c == '\n') putc('\r');		/* CR -> CRLF */

	if (outptr) {
		*outptr++ = (unsigned char)c;
		return;
	}

	if (func_out) func_out((unsigned char)c);
}

/*----------------------------------------------*/
/* Put a null-terminated string                 */
/*----------------------------------------------*/
/* Put a string to the default device */
/* str: Pointer to the string */
void puts (const char* str){
	while (*str) putc(*str++);
}

/*----------------------------------------------*/
/* Formatted string output                      */
/*----------------------------------------------*/
/*  printf("%d", 1234);			"1234"
    printf("%6d,%3d%%", -200, 5);	"  -200,  5%"
    printf("%-6u", 100);			"100   "
    printf("%ld", 12345678L);		"12345678"
    printf("%04x", 0xA3);			"00a3"
    printf("%08LX", 0x123ABC);		"00123ABC"
    printf("%016b", 0x550F);		"0101010100001111"
    printf("%s", "String");		"String"
    printf("%-4s", "abc");			"abc "
    printf("%4s", "abc");			" abc"
    printf("%c", 'a');				"a"
    printf("%f", 10.0);            <xprintf lacks floating point support>
*/
/* const char*	fmt: Pointer to the format string */
/* va_list arp: Pointer to arguments */
static void vprintf (const char*	fmt,va_list arp){
	unsigned int r, i, j, w, f;
	unsigned long v;
	char s[16], c, d, *p;

	for (;;) {
		c = *fmt++;					/* Get a char */
		if (!c) break;				/* End of format? */
		if (c != '%') {				/* Pass through it if not a % sequense */
			putc(c); continue;
		}
		f = 0;
		c = *fmt++;					/* Get first char of the sequense */
		if (c == '0') {				/* Flag: '0' padded */
			f = 1; c = *fmt++;
		} else {
			if (c == '-') {			/* Flag: left justified */
				f = 2; c = *fmt++;
			}
		}
		for (w = 0; c >= '0' && c <= '9'; c = *fmt++)	/* Minimum width */
			w = w * 10 + c - '0';
		if (c == 'l' || c == 'L') {	/* Prefix: Size is long int */
			f |= 4; c = *fmt++;
		}
		if (!c) break;				/* End of format? */
		d = c;
		if (d >= 'a') d -= 0x20;
		switch (d) {				/* Type is... */
		case 'S' :					/* String */
			p = va_arg(arp, char*);
			for (j = 0; p[j]; j++) ;
			while (!(f & 2) && j++ < w) putc(' ');
			puts(p);
			while (j++ < w) putc(' ');
			continue;
		case 'C' :					/* Character */
			putc((char)va_arg(arp, int)); continue;
		case 'B' :					/* Binary */
			r = 2; break;
		case 'O' :					/* Octal */
			r = 8; break;
		case 'D' :					/* Signed decimal */
		case 'U' :					/* Unsigned decimal */
			r = 10; break;
		case 'X' :					/* Hexdecimal */
			r = 16; break;
		default:					/* Unknown type (passthrough) */
			putc(c); continue;
		}

		/* Get an argument and put it in numeral */
		v = (f & 4) ? va_arg(arp, long) : ((d == 'D') ? (long)va_arg(arp, int) : (long)va_arg(arp, unsigned int));
		if (d == 'D' && (v & 0x80000000)) {
			v = 0 - v;
			f |= 8;
		}
		i = 0;
		do {
			d = (char)(v % r); v /= r;
			if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
			s[i++] = d + '0';
		} while (v && i < sizeof(s));
		if (f & 8) s[i++] = '-';
		j = i; d = (f & 1) ? '0' : ' ';
		while (!(f & 2) && j++ < w) putc(d);
		do putc(s[--i]); while(i);
		while (j++ < w) putc(' ');
	}
}

//========================================================
/* Put a formatted string to the default device */
/* const char*	fm: Pointer to the format string */
/* ... : Optional arguments */
void printf (const char*	fmt, ...){
	va_list arp;

	va_start(arp, fmt);
	vprintf(fmt, arp);
	va_end(arp);
}

//=======================================================
/* Put a formatted string to the memory */
/* char* buff: Pointer to the output buffer */
/* const char*	fmt: Pointer to the format string */
/* ... : Optional arguments */
void sprintf (char* buff,	const char*	fmt, ...){
	va_list arp;

	outptr = buff;		/* Switch destination for memory */

	va_start(arp, fmt);
	vprintf(fmt, arp);
	va_end(arp);

	*outptr = 0;		/* Terminate output string with a \0 */
	outptr = 0;			/* Switch destination for device */
}


