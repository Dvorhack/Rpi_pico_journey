

all: compile

upload: compile makeuf2
	cargo objcopy --bin blink_rust -- -O binary bin/main.bin
	./bin/makeuf2 bin/main.bin bin/binary.uf2
	./upload.sh bin/binary.uf2

compile:
	cargo build

makeuf2:
	gcc -o bin/makeuf2 src/makeuf2.c
