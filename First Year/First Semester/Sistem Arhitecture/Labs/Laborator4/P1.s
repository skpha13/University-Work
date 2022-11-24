.data
	a: .space 4
	formatString: .asciz "%ld"
	formatString2: .asciz "%ld\n"
	x: .long 0
.text
.globl main

main:
	pushl $a
	pushl $formatString
	call scanf
	popl %ebx
	popl %ebx
	
	mov $1,%ecx
	
loop:
	cmp a,%ecx
	jg exit
	
	mov $0,%edx
	mov a,%eax
	div %ecx
	
	cmp $0,%edx
	je numarare
	
	add $1,%ecx
	jmp loop
	
numarare:
	mov %ecx,x
	pusha
	pushl x
	pushl $formatString2
	call printf
	popl %ebx
	popl %ebx
	
	pushl $0
	call fflush
	popl %ebx
	
	popa
	
	add $1,%ecx
	jmp loop
	
exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
