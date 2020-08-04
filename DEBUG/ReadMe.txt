test of remote debugging using gdb and android emulator
done with emulator from SDK tools REV-23.0.2,  emulator from SDK tools REV-10 also works.

PART I:  
 - create an avd (system image for gingerbread tested  OKK) named avd233.

 - install "ddd" the GUI for gdb if it's not already:
   sudo apt-get install ddd

PART II:
1- compile with -g option (for debugging) and link the source code:
  arm-none-eabi-as -g -march=armv5te -o test.o -c test.S
  arm-none-eabi-ld -T test.ld --entry ResetISR --gc-sections -o test.elf test.o
2- get the binary program to load in the emulator:
  arm-none-eabi-objcopy -O binary test.elf test.bin 

3- Launch the emulator:
  
  $ emulator -avd avd233 -verbose -show-kernel -netfast  -shell -qemu -s -S -kernel test.bin

 the qemu -s option to launch gdb-server on port 1234
          -S option to halt the cpu until receive command from gdb

PART III:
1- launch the gdb via gui ddd:
	$ ddd --debugger arm-none-eabi-gdb test.elf
2- connect to the emulator:
  (gdb) target remote :1234

- In the View menu, Select Machine Code Windows to see the dissasmbled instructions.
- To view the contents of the registers, From the Status menu select Registers.... A window appears. Note that all   registers have a value of zero.
  
- Add a break point at the start of the program  (attention to CASE of letters):
	(gdb) b RestISR
 a "stop" icon appears at the first line after the label "ResetISR"
- Now type "c" to launch the program on the emulator:
 (gdb) c

 a green array appears befor the stop icon in both the source code window and the disassembler window.
 Now:
	PC register has a value of 0x10000 (kernel load adress in RAM).
	CPSR = 0x400001D3
	SP = 0x00000
and:
	r0 = 0
	r1 = 0x5A1  (1441) ARM machine code for the goldfish
	r2 = 0x100  adress of ATAGS in memory
these values are saved by the emulator in order to pass them to the kernel.

- From the DDD window you can step into the program and watch the values of registers

 

