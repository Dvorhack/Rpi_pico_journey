// arm-none-eabi-as --warn -fatal-warnings -mcpu=cortex-m0 start.s -o start.o

.cpu cortex-m0
.thumb

// Set a stack
ldr r0, =0x20001000
mov sp, r0

// Call main
bl the_main

// infinite loop
b .
