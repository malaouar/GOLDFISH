#include <stdint.h>

// this is the start of the image binary data in our program file
// look at objcopy option "-B" help for more details on how to insert an image binary
// file in the program
// extern cause it's in other file (photo.o). 
extern uint16_t _binary_photo_bin_start; //this sympole is created by objcopy 

#define FBCON_BASE 0xFF014000  //framebuffer controller base adress

//===============================
int main(){
  uint32_t x, y;
	uint32_t w, h, f; // screen width, height, color format
	int fb_length;  // framebuffer length
	int fb_adress = 0x30000;  // video RAM base adress  (arbitrary adress choosen by us)

	uint16_t *ptr = &(_binary_photo_bin_start);  // 
	uint16_t color;
	
	uint32_t *fbcon_ptr = (uint32_t*)(FBCON_BASE); // a 32bit pointer to framebuffer controller base adress
  uint16_t *fb_ptr = (uint16_t*)(fb_adress); // a pointer to video RAM start adress (16bit RGB565)

/*
	// Not used here
	w = *fbcon_ptr;  // get width
	h = *(fbcon_ptr += 0x4/4);	// get height  ( FBCON_BASE + 0x4)
	f = *(fbcon_ptr += (0x24/4)-1);	// get color format ( FBCON_BASE + 0x24) Note: we already added 1 befor!!
	fb_length = w*h*2;  // total framebuffer length in bytes
*/

	// Set framebuffer base adress
	fbcon_ptr = (uint32_t*)(FBCON_BASE);  // first reset pointer value (if it's used befor)
	*(fbcon_ptr += 0x10/4) = fb_adress;  // set adress base ( FBCON_BASE + 0x10) 
	

		// display a photo with resolution 128x128 16bit colors (RGB565)
		for(y=0;y<128;y++){  // height
			for(x=0;x<128;x++){  // width 
				color = *ptr++; // get RGB value of pixel 
				*fb_ptr++ = color;// draw pixel
				}
			// the emulator screen resolution is 480 width x 853 height
      // so we must fill the remaining pixels in the raw
			for(; x< 480; x++) {*fb_ptr++ = 00; } // RGB= black
		}

	return 0;
}


