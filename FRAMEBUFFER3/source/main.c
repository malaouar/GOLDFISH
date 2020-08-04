#include <stdint.h>

// this is the start of the image binary data in our program file
// look at objcopy option "-B" help for more details on how to insert an image binary
// file in the program
// extern cause it's in other file (photo.o). 
extern uint16_t _binary_photo_bin_start; //this sympole is created by objcopy 
extern uint8_t _binary_font_bin_start;

// Framebuffer parameters
#define FBCON_BASE 0xFF014000  //framebuffer controller base adress
uint32_t  pitch = 480*2 ;  // Number of bytes per line
int fb_adress = 0x30000;  // video RAM base adress  (arbitrary adress choosen by us)

// Console parameters to keep track of position of next char in framebuffer
static uint32_t cons_x = 1;
static uint32_t cons_y = 1;

#define FNT_WIDTH	8
#define FNT_HEIGHT 16

int display_photo(uint32_t x, uint32_t y);
void set_pixel(uint32_t x, uint32_t y, uint16_t color);
void console_write(const char *msg);
void display_char(int8_t c);

//===============================
int main(){

	uint32_t w, h, f; // screen width, height, color format
	int fb_length;  // framebuffer length
	int error;  //received error code

	uint32_t *fbcon_ptr = (uint32_t*)(FBCON_BASE); // a 32bit pointer to framebuffer controller base adress

/*
	// Not used here
	w = *fbcon_ptr;  // get width
	h = *(fbcon_ptr += 0x4/4);	// get height  ( FBCON_BASE + 0x4)
	f = *(fbcon_ptr += (0x24/4)-1);	// get color format ( FBCON_BASE + 0x24) Note: we already added 1 befor!!
	fb_length = w*h*2;  // total framebuffer length in bytes
*/

	// Set framebuffer base adress
	fbcon_ptr = (uint32_t*)(FBCON_BASE);  // first reset pointer (if it's used befor)
	*(fbcon_ptr += 0x10/4) = fb_adress;  // set adress base ( FBCON_BASE + 0x10)

	console_write("Framebuffer initialized!\n"); 

	//draw all chars in the font file
	//for(w=0; w<128; w++) display_char(w);

	if((error = display_photo(200, 600)) == -1) { /* do some thing here*/ } ;	

	return 0;
}

//==============================
int display_photo(uint32_t x, uint32_t y){
  uint32_t i, j;
	uint16_t color;
	uint16_t *photo_ptr = &(_binary_photo_bin_start);  // 

	if((x + 128) > 480 || (y + 128) > 853) return -1; // error

		// display a photo with resolution 128x128 16bit colors (RGB565)
		for(j=0; j< 128; j++){  // height
			for(i=0; i<x; i++){ set_pixel(i, y+j, 00);} 

			for(i=x; i<128+x; i++){  // width 
				color = *photo_ptr++; // get RGB value of pixel 
				//*fb_ptr++ = color;
				set_pixel(i, y+j, color); // draw pixel
				}

			// the emulator screen resolution is 480 width x 853 height
      // so we must fill the remaining pixels in the raw
			for(; i< 480; i++) { set_pixel(i, y+j, 00);} // draw black pixel
		}
}

//==========================================
void set_pixel(uint32_t x, uint32_t y, uint16_t color){
	uint32_t offset = (y * pitch) + (x * 2); //there is "pitch" bytes per line and 2 bytes per pixel 
	// a pointer to video RAM start adress (16bit RGB565)
  uint16_t *fb_ptr = (uint16_t*)(fb_adress + offset); 
  *fb_ptr = color; // put color in framebuffer
}

//=================================================
void display_char(int8_t c){
  uint32_t x,y;
	uint32_t row=0, col=0;
	uint32_t font_offset = c*16; // each char is encoded on 16 bytes
	uint8_t *font_ptr = &(_binary_font_bin_start);


	/* clear the pixel first. This erases the old char, if any, at (x, y). 
    Otherwise, it will display the composite bit patterns of the chars, making it unreadable. */

	for(y=cons_y; y<cons_y + FNT_HEIGHT; y++){
		col=0;
		for(x=cons_x; x<cons_x+FNT_WIDTH; x++){
			set_pixel(x, y, 0); // clear the pixel first.
			if(*(font_ptr + font_offset + row)&(1<<col++)) set_pixel(x, y, 0xFFFF); // if pixel=1, color = white
			else		set_pixel(x, y, 0); // else color = black
		}
		row++;
	}

	// find next position in frame buffer
	cons_x += FNT_WIDTH; // next X position in framebuffer = current pos + font_width
	if(cons_x > 480){
		cons_x =1;
		cons_y += FNT_HEIGHT; // next y position in framebuffer = current pos + font_height
		if(cons_y > 853) cons_y = 1;
	}  
}		

//=========================================
void console_write(const char *msg){

	for(;*msg;msg++){ // while char different from zero
		if(*msg == '\r')  cons_x = 1; // if feedback char rest X counter
		else if(*msg == '\n')	cons_y+=FNT_HEIGHT; // if next line char add font height to Y position
		else	display_char(*msg); // else display char
	}
}


