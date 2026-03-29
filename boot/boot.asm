bits 16
org 0x7C00

global _start
_start:

	xor ax, ax
	mov ds, ax
	mov ah, 0x0E
	mov si, msg
	cld
loop:
	lodsb
	test al, al
	jz end
	int 0x10
	jmp loop

end:
	jmp end

msg:
	db 0x0D, 0x0A
	db 'OriginOS'
	db 0x0D, 0x0A
	db 0x00

times 0x1FE - ($ - $$) db 0x00
dw 0xAA55
