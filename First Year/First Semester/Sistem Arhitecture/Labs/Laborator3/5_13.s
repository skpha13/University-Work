.data
	n: .space 4
	prod: .space 4
	fs: .asciz "%ld"
	fs2: .asciz "%ld\n"
.text
.globl main

main:
	pushl $n
	pushl $fs
	call scanf
	popl %ebx
	popl %ebx
	
	mov $2,%ecx
	mov $1,%eax

loop:
	cmp n,%ecx
	jg afisare
	
	mul %ecx
	
	add $1,%ecx
	jmp loop
	
afisare:
	mov %eax,prod
	
	pushl prod
	pushl $fs2
	call printf
	popl %ebx
	popl %ebx
	
	jmp exit

exit:	
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
