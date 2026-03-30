bits 32
org 0x7E00

global _start
_start:

	mov ax, 0x0010
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov sp, 0x81FF

	mov ebx, 0x000B8000
	mov byte [ebx], 'O'

	jmp $

times 0x200 - ($ - $$) db 0x00
