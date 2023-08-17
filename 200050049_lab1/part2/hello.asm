mov ah, 0x0e
mov al, 'h'
int 0x10
mov al, 't'
int 0x10
mov al, 'g'
int 0x10
mov al, '_'
int 0x10
mov al, 's'
int 0x10
mov al, 'e'
int 0x10
mov al, 'n'
int 0x10
mov al, 's'
int 0x10
mov al, 'e'
int 0x10
mov al, 'i'
int 0x10

times 510 -( $ - $$ ) db 0	; When compiled, our program must fit 
			        ; into 512 bytes, with the last two bytes 
				; being the magic number, so here, tell our 
				; assembly compiler to pad out our program 
				; with enough zero bytes (db 0) to bring us 
				; to the 510th byte

dw 0xaa55			; Last two bytes (one word) form the magic 
				; number, so BIOS knows we are a boot sector
