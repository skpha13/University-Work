.data

.text
f:
    call f
    ret

.global main

main:
    call f

exit:
    mov $1,%eax
    xor %ebx,%ebx
    int $0x80