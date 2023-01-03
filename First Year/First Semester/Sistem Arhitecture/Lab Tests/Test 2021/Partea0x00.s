.data
    nr: .long 0
    fs1: .asciz "%ld"
    fs2: .asciz "%ld\n"
    n: .space 4

.text

.global main

main:
    pushl $n
    pushl $fs1
    call scanf
    addl $8,%esp

    pushl n
    pushl $fs2
    call printf
    addl $8,%esp

    
exit:
    mov $1,%eax
    xor %ebx,%ebx
    int $0x80