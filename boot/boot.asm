bits 16
org 0x7C00

global _start
_start:

	mov ax, 0x8000
	mov ss, ax
	mov sp, 0x0000

	xor ax, ax
	mov es, ax
	mov ax, 0x0201
	mov bx, 0x7E00
	mov cx, 0x0002
	mov dx, 0x0080
	int 0x13
	jc error
	jmp 0x0000:0x7E00

error:

	push ax

	xor ax, ax
	mov ds, ax
	mov ah, 0x0E
	mov bx, 0x0007
	cld

	mov si, error_msg_0
loop_0:
	lodsb
	test al, al
	jz end_0
	int 0x10
	jmp loop_0
end_0:

	pop ax

	xor bh, bh
	mov bl, ah
	shr bl, 0x04
	mov al, hex[bx]
	int 0x10
	mov bl, ah
	and bl, 0x0F
	mov al, hex[bx]
	int 0x10

	mov si, error_msg_1
loop_1:
	lodsb
	test al, al
	jz end_1
	int 0x10
	jmp loop_1
end_1:

	jmp $

error_msg_0:
	db 0x0D, 0x0A
	db 'Booting error: 0x'
	db 0x00

error_msg_1:
	db '.'
	db 0x0D, 0x0A
	db 0x00

hex:
	db '0123456789ABCDEF'

times 0x1FE - ($ - $$) db 0x00
dw 0xAA55
