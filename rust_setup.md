
```bash
sudo apt update
curl https://sh.rustup.rs -sSf | sh

cargo install cargo-binutils

# Add the cross-compiler for target architecture
rustup target add thumbv6m-none-eabi

rustup component add llvm-tools-preview
```

## Compile and upload
```bash
cargo build
cargo objcopy --bin blink_rusp -- -O binary main.bin
./makeuf2 main.bin binary.uf2
```