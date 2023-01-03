.data
    nr: .long 0
    fs1: .asciz "%ld"
    fs2: .asciz "%ld\n"
    n: .space 4

.text

f:
    push %ebp
    mov %esp,%ebp
    push %ebx

    # n = 8(%ebp)

    addl $1,nr

    cmpl $1,8(%ebp)
    je iesire

    subl $4,%esp
    movl 8(%ebp),%eax
    movl %eax,-4(%ebp)

    andl $1,-4(%ebp)
    cmpl $0,-4(%ebp)
    je par

    addl $4,%esp
    movl 8(%ebp),%eax
    movl $3,%ebx
    mull %ebx
    addl $1,%eax

    push %eax
    call f
    addl $4,%esp

    jmp iesire

    par:
        addl $4,%esp
        movl $0,%edx

        movl 8(%ebp),%eax
        movl $2,%ebx
        divl %ebx

        pushl %eax
        call f
        addl $4,%esp

        jmp iesire

    iesire:
        pop %ebx
        pop %ebp
        ret
    
.global main

main:
    pushl $n
    pushl $fs1
    call scanf
    addl $8,%esp

    pushl n
    call f
    addl $4,%esp

    subl $1,nr

    pushl nr
    pushl $fs2
    call printf
    addl $8,%esp

exit:
    mov $1,%eax
    xor %ebx,%ebx
    int $0x80