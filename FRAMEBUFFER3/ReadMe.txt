
- Read the framebuffer width and height in pixels
- Read Color format
- set framebuffer base adress in RAM
- draw an image (photo.bin) on a given position (x, y).
- write text using font.bin.
  
In the makefile first, we convert "photo.bin" and "font.bin" to object files "photo.o" and "font.o"  using objcopy:

  arm-none-eabi-objcopy -I binary -O elf32-littlearm -B arm photo.bin photo.o
  arm-none-eabi-objcopy -I binary -O elf32-littlearm -B arm font.bin font.o

objcopy transforms an architecture-less input file into an object file (section data). You can access this binary data inside the program by referencing the special symbols that are created by the conversion process. These symbols are called _binary_filename_bin_start, _binary_filename_bin_end and _binary_filename_bin_size.  

then these object files are added to the list of linked files. 

after compilation with "make" :
- To run the program on the emulator use the command:
	make run
- To debug the program via DDD:
  make debug
