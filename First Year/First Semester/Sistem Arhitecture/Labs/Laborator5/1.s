.data
	nr: .long 0
	n: .long 0
	v: .space 100
	fs: .asciz "%ld"
	fs1: .asciz "%ld\n"

.text

perfect:
	
	ret
	
.globl main

main:
	pushl $n
	pushl $fs
	call scanf
	popl %ebx
	popl %ebx
	
	mov $0,%ecx
	lea v,%edi
	
citire_loop:
	cmp n,%ecx
	je program
	
	pusha
	pushl $aux
	pushl $fs
	call scanf
	popl %ebx
	popl %ebx
	popa
	
	movl aux,%eax
	movl %eax,(%edi,%ecx,4)
	
	add $1,%ecx
	jmp citire_loop
	
program: 
	mov $0,%ecx
	jmp loop

loop:
	
	
	
afisare:
	pushl nr
	pushl $fs1
	call printf
	popl %ebx
	popl %ebx

exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
