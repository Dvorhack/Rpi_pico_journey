First : Power On Sequence (Hardware init)  
Then the to cpu boots and exec the Bootrom (boot sequence / first stage bootloader)

Loads the first 256 bytes from flash and check the last 4 bytes as a CRC32