.SUFFIXES: .asm .bin

all: hd.img

hd.img: boot/boot.bin kernel/kernel.bin
	cat $^ > $@

.asm.bin:
	nasm -f bin $^ -o $@

clean:
	rm boot/boot.bin kernel/kernel.bin hd.img

qemu:
	qemu-system-x86_64 -drive file=hd.img,format=raw -no-reboot
