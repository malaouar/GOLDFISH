
- init usart2  (simply enable it)
- send a single char or a string
- receive a single char or a string (must give a pointer to our buffer where string will be saved by the USART)
- disable the USART
- Enable/Disable TTY2 receive interrupt or any supported interupt.
- USART and INT functions in separate files.

after compilation with "make" :
- To run the program on the emulator use the command:
	make run
the emulator is invoked with option "-shell", so the serial port 2 will be connected to the current console.
the emulator can output text and we can send text to it !!

- To debug the program via DDD:
  make debug

