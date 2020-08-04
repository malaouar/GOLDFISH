
 To run this test look at book "embedded progrmming android" by Roger Ye, chap7 exercice1 (c07e1)

- Timer functions and Interrupt.
- init usart2  (simply enable it)
- send a single char or a string
- receive a single char or a string (must give a pointer to our buffer where string will be saved by the USART)
- disable the USART
- Enable/Disable TTY2 receive interrupt (or any supported interupt).
- USART, TIMER, and INT functions in separate files.
- Tiny local PRINTF used !!
  

after compilation with "make" :
- To run the program on the emulator use the command:
	make run
the emulator is invoked with option "-shell", so the serial port 2 will be connected to the current console.
the emulator can output text and we can send text to it !!

- To debug the program via DDD:
  make debug

