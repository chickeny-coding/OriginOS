.SUFFIXES: .asm .bin .img

all: hd.img

hd.img: boot/boot.bin
	cat $^ > $@

.asm.bin:
	nasm -f bin $^ -o $@

clean:
	rm boot/boot.bin hd.img

qemu:
	qemu-system-x86_64 -drive file=hd.img,format=raw
