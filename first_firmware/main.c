void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void DELAY ( unsigned int );

#define RESETS_BASE 0x4000c000

#define RESETS_RESET_RW             (RESETS_BASE+0x0+0x0000)
#define RESETS_RESET_XOR            (RESETS_BASE+0x0+0x1000)
#define RESETS_RESET_SET            (RESETS_BASE+0x0+0x2000)
#define RESETS_RESET_CLR            (RESETS_BASE+0x0+0x3000)

#define RESETS_WDSEL_RW             (RESETS_BASE+0x4+0x0000)
#define RESETS_WDSEL_XOR            (RESETS_BASE+0x4+0x1000)
#define RESETS_WDSEL_SET            (RESETS_BASE+0x4+0x2000)
#define RESETS_WDSEL_CLR            (RESETS_BASE+0x4+0x3000)

#define RESETS_RESDONE_RW        (RESETS_BASE+0x8+0x0000)
#define RESETS_RESDONE_XOR       (RESETS_BASE+0x8+0x1000)
#define RESETS_RESDONE_SET       (RESETS_BASE+0x8+0x2000)
#define RESETS_RESDONE_CLR       (RESETS_BASE+0x8+0x3000)

#define RESET_IO_BANK0 1<<5

#define SIO_BASE 0xD0000000

#define SIO_GPIO_OUT_RW  (SIO_BASE+0x10)
#define SIO_GPIO_OUT_SET (SIO_BASE+0x14)
#define SIO_GPIO_OUT_CLR (SIO_BASE+0x18)
#define SIO_GPIO_OUT_XOR (SIO_BASE+0x1C)

#define SIO_GPIO_OE_RW   (SIO_BASE+0x20)
#define SIO_GPIO_OE_SET  (SIO_BASE+0x24)
#define SIO_GPIO_OE_CLR  (SIO_BASE+0x28)
#define SIO_GPIO_OE_XOR  (SIO_BASE+0x2C)


#define IO_BANK0_BASE               0x40014000

#define IO_BANK0_GPIO25_STATUS_RW   (IO_BANK0_BASE+0x0C8+0x0000)
#define IO_BANK0_GPIO25_STATUS_XOR  (IO_BANK0_BASE+0x0C8+0x1000)
#define IO_BANK0_GPIO25_STATUS_SET  (IO_BANK0_BASE+0x0C8+0x2000)
#define IO_BANK0_GPIO25_STATUS_CLR  (IO_BANK0_BASE+0x0C8+0x3000)

#define IO_BANK0_GPIO25_CTRL_RW     (IO_BANK0_BASE+0x0CC+0x0000)
#define IO_BANK0_GPIO25_CTRL_XOR    (IO_BANK0_BASE+0x0CC+0x1000)
#define IO_BANK0_GPIO25_CTRL_SET    (IO_BANK0_BASE+0x0CC+0x2000)
#define IO_BANK0_GPIO25_CTRL_CLR    (IO_BANK0_BASE+0x0CC+0x3000)

void reset_preripheral(unsigned int peripheral){
    PUT32(RESETS_RESET_CLR, peripheral);

    // Wait for reset to be effective
    while(1){
        if( (GET32(RESETS_RESDONE_RW) & peripheral) != 0)
            break;
    }
}

void GPIO_enable(unsigned int gpio_nb){
    // For most GPIO pins function 5 will connect the pin to SIO.
    // The function is selected by writing to the FUNCSEL field in the GPIO’s CTRL register

    //output disable
    PUT32(SIO_GPIO_OE_CLR,1 << gpio_nb);
    //turn off pin 25
    PUT32(SIO_GPIO_OUT_CLR,1 << gpio_nb);

    //set the function select to SIO (software controlled I/O)
    PUT32(IO_BANK0_BASE+0x8*gpio_nb+4+0x0000,5);

    //output enable
    PUT32(SIO_GPIO_OE_SET,1 << gpio_nb);
}

// Goal: blink the led (GPIO25)
void the_main(){

    // Before you can talk to the IO block we have to release reset.
    reset_preripheral(RESET_IO_BANK0);

    // Set GPIO25 to digital output
    GPIO_enable(25);

    GPIO_enable(16);
     
    while(1)
    {
        //turn on the led
        PUT32(SIO_GPIO_OUT_SET,1<<25);
        PUT32(SIO_GPIO_OUT_SET,1<<16);
        DELAY(0x100000);
        //turn off the led
        PUT32(SIO_GPIO_OUT_CLR,1<<25);
        PUT32(SIO_GPIO_OUT_CLR,1<<16);
        DELAY(0x100000);
    }
}