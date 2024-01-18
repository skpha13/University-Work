.data
	x: .space 4
	n: .space 4
	v: .space 100
	aux: .space 4
	fs: .asciz "%ld"
	fs2: .asciz "%ld " 
	newLine: .asciz "\n"
	
.text
.globl main

main:
	pushl $x
	pushl $fs
	call scanf
	popl %ebx
	popl %ebx
	
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
	cmp n,%ecx
	je exit
	
	movl (%edi,%ecx,4),%eax
	movl x,%ebx
	mov $0,%edx
	div %ebx
	
	cmp $0,%edx
	je afisare
	
	add $1,%ecx
	jmp loop
	
afisare:
	movl (%edi,%ecx,4),%eax
	add $1,%ecx
	movl %ecx,aux
	
	pusha
	pushl %eax
	pushl $fs2
	call printf
	popl %ebx
	popl %ebx
	popa
	
	pushl $0
	call fflush
	popl %ebx

	movl aux,%ecx
	jmp loop
exit:
	mov $4,%eax
	mov $1,%ebx
	mov $newLine,%ecx
	mov $1,%edx
	int $0x80
	
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
