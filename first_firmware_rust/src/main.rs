#![no_std]
#![no_main]

// pick a panicking behavior
use panic_halt as _; // you can put a breakpoint on `rust_begin_unwind` to catch panics
// use panic_abort as _; // requires nightly
// use panic_itm as _; // logs messages over ITM; requires ITM support
// use panic_semihosting as _; // logs messages to the host stderr; requires a debugger

use cortex_m::asm;
use cortex_m_rt::entry;


pub static BOOT_LOADER_W25Q080: [u8; 256] =
    *include_bytes!( "boot2_w25q080.padded.bin");

#[link_section = ".boot_loader"]
#[used]
pub static BOOT2_FIRMWARE: [u8; 256] = BOOT_LOADER_W25Q080;

#[repr(C)]
struct SIO_GPIO {
    pub unk1: u64, 
    pub unk2: u64,
    pub out_rw: u32,
    pub out_set: u32,
    pub out_clr: u32,
    pub out_xor: u32,
    pub oe_rw: u32,
    pub oe_set: u32,
    pub oe_clr: u32,
    pub oe_xor: u32,
}

fn put32(address: *mut u32, value: u32){
    unsafe { core::ptr::write_volatile(address, value) };
}

fn get32(address: *mut u32) -> u32{
    unsafe { core::ptr::read_volatile(address) }
}

fn reset_preripheral(peripheral: u32){
    // ask for reset
    let reset_clr = unsafe { &mut *((0x4000c000+0x3000) as *mut u32) };
    put32(reset_clr, peripheral);

    // Wait for reset to be effective
    let resdone_rw = unsafe { &mut *((0x4000c000+0x8+0x0000) as *mut u32) };
    let mut value = 0;
    while (value & peripheral) == 0 {
        value = get32(resdone_rw);
    } 
}

fn gpio_enable(gpio_nb: u32) {
    let sio = unsafe { &mut *(0xD0000000 as *mut SIO_GPIO) };

    // disable output
    put32(&mut sio.oe_clr, 1 << gpio_nb);
    // turn gpio off
    put32(&mut sio.out_clr, 1 << gpio_nb);
    let gpio_25_fct = unsafe { &mut *((0x40014000+(0x8*gpio_nb)+4+0x0000) as *mut u32) };
    // select alternative function to SIO (Software IO)
    put32(gpio_25_fct, 5);
    // enable output
    put32(&mut sio.oe_set, 1 << gpio_nb);

}

fn gpio_high(gpio_nb: u32){
    let sio = unsafe { &mut *(0xD0000000 as *mut SIO_GPIO) };
    unsafe { core::ptr::write_volatile(&mut sio.out_set, 1 << gpio_nb) }; 
}

fn gpio_low(gpio_nb: u32){
    let sio = unsafe { &mut *(0xD0000000 as *mut SIO_GPIO) };
    unsafe { core::ptr::write_volatile(&mut sio.out_clr, 1 << gpio_nb) }; 
}

fn delay(cycle_nb: usize){
    for _ in 0..cycle_nb {
        asm::nop();
    }
}


#[entry]
fn main() -> ! {
    asm::nop(); // To not have main optimize to abort in release mode, remove when you add code

    // Reset bank0
    let reset_io_bank0 = 1<< 5;
    reset_preripheral(reset_io_bank0);
    
    // Enable gpio25
    let led_gpio = 25;
    gpio_enable(led_gpio);

   
    loop {
        // turn led n
        gpio_high(led_gpio);
    
        delay(0x10000);

        // turn led off
        gpio_low(led_gpio);

        delay(0x10000);
    }
}
