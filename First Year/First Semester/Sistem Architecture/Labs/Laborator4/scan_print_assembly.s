

.data
	grupa: .space 4
	nota: .space 4
	nume: .space 100
	fs1: .asciz "%ld %d\n"
	fs2: .asciz "Studnetul %s de la grupa %ld a obtinut nota %d\n"
	fs3: .asciz "%ld\n"
	
.text
.globl main

main:
	pusha

	pushl $nota
	pushl $grupa
	pushl $fs1
	call scanf
	popl %ebx
	popl %ebx
	popl %ebx
	
	popa
	
	pushl $nume
	call gets
	popl %ebx
	
	pushl nota
	pushl grupa
	pushl $nume
	pushl $fs2
	call printf
	popl %ebx
	popl %ebx
	popl %ebx
	popl %ebx
	
	pushl %ebx
	pushl $fs3
	call printf
	popl %ebx
	popl %ebx
	
	pushl $0
	call fflush
	popl %ebx
	
exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
