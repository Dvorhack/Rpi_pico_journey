# Raspberry Pi Pico Journey
Welcome to my RPi Pico Journey !  
It'll be a deep dive into the internals of this board.  

The aim of this research is to learn about hardware, low level programming, etc.  

## Roadmap
- [x] Find ressources
- [x] HowTo build Toolchain
- [x] Blink led in C
- [x] Blink led in Rust
- [ ] Use runner and build rust
- [ ] Document bootloader 


## Ressources

- Complete tutorials  
    - [Github 1 using SDK](https://github.com/carlosftm/RPi-Pico-Baremetal)  
    - [Github 2 without SDK](https://github.com/dwelch67/raspberrypi-pico)
    - [Official Getting Started](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)

- Raspberry Pi Pico Documentation
    - [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
    - [RPi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf)

- ARM Documentation
    - [Armv6-M Ref Manual](https://developer.arm.com/documentation/ddi0419/latest/)
    - [Cortex-M0+ Ref Manual](https://developer.arm.com/documentation/ddi0484/latest/)

- [U2F File format](https://github.com/Microsoft/uf2)

## Debug using flipper zero

Install app [insert app] in flipper store

Run the app and select pin `12, 13` as the UART pin

`sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000"`

