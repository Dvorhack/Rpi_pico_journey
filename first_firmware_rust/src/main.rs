#![no_std]
#![no_main]

// pick a panicking behavior
use panic_halt as _; // you can put a breakpoint on `rust_begin_unwind` to catch panics
// use panic_abort as _; // requires nightly
// use panic_itm as _; // logs messages over ITM; requires ITM support
// use panic_semihosting as _; // logs messages to the host stderr; requires a debugger

use cortex_m::asm;
use cortex_m_rt::entry;
use volatile_register::{RW, RO};
use core::mem::replace;


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

pub struct SysTick {
    p: &'static mut SysTickRegisters
}

#[repr(C)]
struct SysTickRegisters {
    pub csr: RW<u32>, // Use the SysTick Control and Status Register to enable the SysTick features.
    pub rvr: RW<u32>, // specify the start value to load into the current value register when the counter reaches 0
    pub cvr: RW<u32>, // get  the current value in the register
    pub calib: RO<u32>, // enable software to scale to any required speed using divide and multiply
}

impl SysTick {
    pub fn new() -> SysTick {
        SysTick {
            p: unsafe { &mut *(0xE000_E010 as *mut SysTickRegisters) }
        }
    }

    pub fn get_time(&self) -> u32 {
        self.p.cvr.read()
    }

    pub fn set_reload(&mut self, reload_value: u32) {
        unsafe { self.p.rvr.write(reload_value) }
    }
}

pub struct Timer {
    p: &'static mut TimerRegisters
}

#[repr(C)]
struct TimerRegisters {
    pub hw: RW<u32>, 
    pub lw: RW<u32>, 
    pub hr: RW<u32>, 
    pub lr: RW<u32>, 
    pub alarm0: RW<u32>,
    pub alarm1: RW<u32>,
    pub alarm2: RW<u32>,
    pub alarm3: RW<u32>,
    pub armed: RW<u32>,
    pub awh: RW<u32>,
    pub awl: RW<u32>,
    pub dbgpause: RW<u32>,
    pub pause: RW<u32>,
    pub intr: RW<u32>,
    pub inte: RW<u32>,
    pub intf: RW<u32>,
    pub ints: RW<u32>,
}

impl Timer {
    pub fn new() -> Timer {
        Timer {
            p: unsafe { &mut *(0x4005_4000 as *mut TimerRegisters) }
        }
    }
    pub fn get_time(&self) -> u64{
        let lo = self.p.lr.read();
        let hi = self.p.hr.read();
        ((hi as u64) << 32) | (lo as u64)
    }
}

pub struct Watchdog {
    p: &'static mut WatchdogRegisters
}

#[repr(C)]
struct WatchdogRegisters {
    pub ctrl: RW<u32>,
    pub load: RW<u32>,
    pub reason: RW<u32>,
    pub scratch0: RW<u32>,
    pub scratch1: RW<u32>,
    pub scratch2: RW<u32>,
    pub scratch3: RW<u32>,
    pub scratch4: RW<u32>,
    pub scratch5: RW<u32>,
    pub scratch6: RW<u32>,
    pub scratch7: RW<u32>,
    pub tick: RW<u32>,
}

impl Watchdog {
    pub fn new() -> Watchdog {
        Watchdog {
            p: unsafe { &mut *(0x4005_8000 as *mut WatchdogRegisters) }
        }
    }
    pub fn start_tick(&mut self){
        unsafe{ self.p.tick.write(12 |  (1 << 9)) }
    }
}

struct Peripherals {
    watchdog: Option<Watchdog>,
    timer: Option<Timer>,
    systick: Option<SysTick>,
}
impl Peripherals {
    fn init(&mut self){
        self.watchdog = Some(Watchdog::new());
        self.timer = Some(Timer::new());
        self.systick = Some(SysTick::new());
    }
    fn take_watchdog(&mut self) -> Watchdog {
        let p = replace(&mut self.watchdog, None);
        p.unwrap()
    }
    fn take_timer(&mut self) -> Timer {
        let p = replace(&mut self.timer, None);
        p.unwrap()
    }
    fn take_systick(&mut self) -> SysTick {
        let p = replace(&mut self.systick, None);
        p.unwrap()
    }
}

static mut PERIPHERALS: Peripherals = Peripherals {
    watchdog: None,
    timer: None,
    systick: None,
};


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

fn delay(cycle_nb: u64){
    // for _ in 0..cycle_nb {
    //     asm::nop();
    // }
    let timer = unsafe { PERIPHERALS.take_timer() };
    let start = timer.get_time();
    while timer.get_time() < (start+cycle_nb ) {}
}

fn clock_init(){
    /*
        We'll need the Timer to be running for the delay function
        The Timer shares the same reference clock as the Watchdog, then we need to select it on the Watchdog
        in order to have the Time start counting (rp2040-datasheet Section 4.6.4)
    */
    let mut watchdog = unsafe { PERIPHERALS.take_watchdog() };
    watchdog.start_tick();
}

fn pico_init(){
    unsafe{ PERIPHERALS.init() };
    clock_init();
}


#[entry]
fn main() -> ! {
    asm::nop(); // To not have main optimize to abort in release mode, remove when you add code

    pico_init();
    clock_init();

    // Reset bank0
    let reset_io_bank0 = 1<< 5;
    reset_preripheral(reset_io_bank0);
    
    // Enable gpio25
    let led_gpio = 25;
    gpio_enable(led_gpio);

   
    loop {
        // turn led n
        gpio_high(led_gpio);
    
        delay(1000);

        // turn led off
        gpio_low(led_gpio);

        delay(1000);
    }
}
