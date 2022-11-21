pushl $0
call fflush
popl %ebx

.data
	x: .long 23
	formatString: .asciz "Numarul de afisat este: %ld"
	newLine: .asciz "\n%s"
.text
.globl main

main:
	pushl x
	pushl $formatString
	
	call printf
	popl %ebx
	popl %ebx
	popl %ebx

	pushl $0
	call fflush
	popl %ebx
	
	movl $4, %eax
	movl $1, %ebx
	movl $newLine, %ecx
	movl $2, %edx
	int $0x80

	movl $1,%eax
	xorl %ebx,%ebx
	int $0x80
