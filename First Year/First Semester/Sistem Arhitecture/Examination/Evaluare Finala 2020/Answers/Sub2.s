.data
    n: .long 5
    m: .long 100
    formatPrintf: .asciz "%d "

.text
f:
    pushl %ebp
    movl %esp, %ebp
    # salvam %ebx, nu produce eroare dar asa este corect, nu produce eroare
    pushl %ebx

    # punem 0 in %edx inainte de impartire, altfel nu imparte corect
    mov $0,%edx
    # era gresita ordinea operanzilor la mov
    movl 8(%ebp),%ecx 
    movl 12(%ebp),%eax 

    divl %ecx
    pushl %eax

    f_for:
        # salvam %ecx ca dupa functia printf iese modificat
        pushl %ecx

        pushl %ecx
        pushl $formatPrintf
        call printf
        popl %ebx
        popl %ebx

        pushl $0
        call fflush
        popl %ebx
        
        popl %ecx
        loop f_for

    f_exit:
        popl %eax
        popl %ebx
        popl %ebp
        ret


.global main

main:
    movl n, %edx
    decl %edx

    pushl m
    pushl %edx
    call f
    popl %ebx
    popl %ebx

    pushl %eax
    pushl $formatPrintf
    call printf
    popl %ebx
    popl %ebx
    
    pushl $0
    call fflush
    popl %ebx

et_exit:
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80

# afiseaza 4 3 2 1 25 fara \n
# fflush trebuie utilizat ptc formatPrintf nu contine \n la final si in consecinta nu afiseaza nimic
# se foloseste pushl %eax si popl %eax pentru a salva valoarea lui %eax, ca sa nu iasa modificata dupa apelarea lui printf

