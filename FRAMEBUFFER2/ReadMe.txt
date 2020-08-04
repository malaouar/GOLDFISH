
- Read the framebuffer width and height in pixels
- Read Color format
- set framebuffer base adress in RAM
- draw an image (photo.bin).
  
First, in the root directory of this example, convert "photo.bin" to object file "photo.o" using objcopy:

	arm-none-eabi-objcopy -I binary -O elf32-littlearm -B arm photo.bin photo.o

objcopy transforms an architecture-less input file into an object file (section data). You can access this binary data inside the program by referencing the special symbols that are created by the conversion process. These symbols are called _binary_photo_bin_start, _binary_photo_bin_end and _binary_photo_bin_size.  

In the makefile this object file is added to the list of linked files. 

after compilation with "make" :
- To run the program on the emulator use the command:
	make run
- To debug the program via DDD:
  make debug

