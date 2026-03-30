bits 16
org 0x7E00

global _start
_start:

	xor ax, ax
	mov ds, ax
	mov ah, 0x0E
	mov bx, 0x0007
	mov si, msg
	cld
loop:
	lodsb
	test al, al
	jz end
	int 0x10
	jmp loop
end:

	jmp $

msg:
	db 0x0D, 0x0A
	db 'OriginOS'
	db 0x0D, 0x0A
	db 0x00

times 0x200 - ($ - $$) db 0x00
