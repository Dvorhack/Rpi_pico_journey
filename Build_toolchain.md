# How to build an ARM toolchain on Linux
Rpi Pico is based on Armv6, so we'll need a toolchain in order to compile our code for this architecture 

## Easy way  
Get a pre-built one: 
- From packages 
    - Debin based: `sudo apt-get -y install gcc-arm-none-eabi binutils-arm-none-eabi`
    - Arch base: `sudo pacman -S arm-none-eabi-gcc arm-none-eabi-binutils`
- From internet: https://launchpad.net/gcc-arm-embedded

## Manual way
```bash
# Setup vars
export TARGET=arm-none-eabi
export PREFIX=/opt/toolchains/arm
export PATH=$PATH:$PREFIX/bin
export JN='-j 12'

# Select the versions of GCC and Binutils you want
export GCCVER=13.1.0
export BINUVER=2.40

rm -rf build-*
rm -rf gcc-*
rm -rf binutils-*

# Get archives
wget https://ftp.gnu.org/gnu/binutils/binutils-$BINUVER.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-$GCCVER/gcc-$GCCVER.tar.gz

# Extract archives
tar xf binutils-$BINUVER.tar.gz
tar xf gcc-$GCCVER.tar.gz

# may have to touch this from time to time
ln -s binutils-$BINUVER binutils-patch
patch -p0 < arm-patch

# Build binutils
mkdir build-binutils
cd build-binutils
../binutils-$BINUVER/configure --target=$TARGET --prefix=$PREFIX
echo "MAKEINFO = :" >> Makefile
make $JN all
sudo make install

# Build GCC
mkdir ../build-gcc
cd ../build-gcc
../gcc-$GCCVER/configure --target=$TARGET --prefix=$PREFIX --without-headers --with-newlib  --with-gnu-as --with-gnu-ld --enable-languages='c' --enable-frame-pointer=no
make $JN all-gcc
sudo make install-gcc

# Build libgcc.a
make $JN all-target-libgcc CFLAGS_FOR_TARGET="-g -O2"
sudo make install-target-libgcc
```

## Ressources
Based on [this repo](https://github.com/dwelch67/build_gcc)

[Toolchain Guide](https://embeddedinventor.com/a-complete-beginners-guide-to-the-gnu-arm-toolchain-part-1/)