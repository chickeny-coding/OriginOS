.SUFFIXES: .c .asm .bin

all: hd.img

hd.img: boot/boot.bin kernel/kernel.bin
	cat $^ > $@

.asm.bin:
	nasm -f bin $^ -o $@

kernel/kernel.bin: kernel/kernel.c kernel/io.c
	clang -m32 -nostdlib -ffreestanding -Wl,--oformat=binary -Iinclude -fno-pic -O0 -Wl,-T,ld.ld $^ -o $@

clean:
	rm boot/boot.bin kernel/kernel.bin hd.img

qemu:
	qemu-system-x86_64 -drive file=hd.img,format=raw -no-reboot
