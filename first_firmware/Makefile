
ARMGNU ?= arm-none-eabi

XCPU = -mcpu=cortex-m0

AOPS = --warn --fatal-warnings $(XCPU)
COPS = -Wall -O2 -ffreestanding -nostartfiles $(XCPU)
LOPS = -nostdlib 

all : firmware.uf2 clean

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f u2f_converter

upload: upload.sh
	./upload.sh firmware.uf2
	
u2f_converter : u2f_converter.c
	gcc -O2 u2f_converter.c -o u2f_converter
	
firmware.uf2 : main.bin u2f_converter
ifdef loc
	./u2f_converter $(loc) main.bin
else
	./u2f_converter flash main.bin
endif
	

start.o : start.s
	$(ARMGNU)-as $(AOPS) start.s -o start.o

utils.o : utils.s
	$(ARMGNU)-as $(AOPS) utils.s -o utils.o

main.o : main.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c main.c -o main.o

main.bin : memmap.ld start.o utils.o main.o
	$(ARMGNU)-ld $(LOPS) -T memmap.ld start.o utils.o main.o -o main.elf
	$(ARMGNU)-objdump -D main.elf > main.list
	$(ARMGNU)-objcopy -O binary main.elf main.bin