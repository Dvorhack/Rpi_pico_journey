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


#[entry]
fn main() -> ! {
    asm::nop(); // To not have main optimize to abort in release mode, remove when you add code

    // Reset IO_BANK0
    let reset_clr = unsafe { &mut *((0x4000c000+0x3000) as *mut u32) };
    let reset_io_bank0 = 1<< 5;
    unsafe { core::ptr::write_volatile(reset_clr, reset_io_bank0) };

    // Wait for reset to be effective
    let resdone_rw = unsafe { &mut *((0x4000c000+0x8+0x0000) as *mut u32) };
    let mut value = 0;
    while (value & reset_io_bank0) == 0 {
        value = unsafe { core::ptr::read_volatile(resdone_rw) };
    } 
    
    // Enable gpio25
    let sio = unsafe { &mut *(0xD0000000 as *mut SIO_GPIO) };
    let gpio25 = 1 << 25;
    unsafe { core::ptr::write_volatile(&mut sio.oe_clr, gpio25) }; //output disable
    unsafe { core::ptr::write_volatile(&mut sio.out_clr, gpio25) }; //turn off pin 25
    let gpio_25_fct = unsafe { &mut *((0x40014000+(0x8*25)+4+0x0000) as *mut u32) };
    unsafe { core::ptr::write_volatile(gpio_25_fct, 5) }; //set the function select to SIO (software controlled I/O)
    unsafe { core::ptr::write_volatile(&mut sio.oe_set, gpio25) }; //output enable

    loop {
        // turn on
        unsafe { core::ptr::write_volatile(&mut sio.out_set, gpio25) }; 
    
        for _ in 0..0x10000 {
            asm::nop();
        }

        // turn off
        unsafe { core::ptr::write_volatile(&mut sio.out_clr, gpio25) }; 

        for _ in 0..0x10000 {
            asm::nop();
        }
    }
}
