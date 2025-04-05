global outb
global inb
global io_wait

outb:
    push ebp
    mov ebp, esp
    mov edx, [ebp + 8] ; port
    mov al, [ebp + 12] ; val
    out dx, al
    pop ebp
    ret

inb:
    push ebp
    mov ebp, esp
    mov edx, [ebp + 8] ; port
    in al, dx
    pop ebp
    ret

io_wait:
    mov dx, 0x80 ; 0x80 -- unused port
    out dx, al
    ret