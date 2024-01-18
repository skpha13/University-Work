pushl $0
call fflush
popl %ebx

.data 
	n: .long 7
	v: .long -21,2,3,4,5,23,654
	x: .long 3
	aux: .long 0
	poz: .long 0
	formatString: .asciz "Pozitie: %ld"
	newLine: .asciz "\n"
.text
.globl main

main:
	lea v,%edi
	mov $0,%ebx
	mov n,%ecx
	sub $1,%ecx
loop:
	cmp %ebx,%ecx
	jl exit2
	
	mov $0,%eax
	add %ebx,%eax
	add %ecx,%eax
	mov $0,%edx
	mov %ebx,aux
	mov $2,%ebx
	div %ebx
	mov aux,%ebx
	
	movl (%edi,%eax,4),%edx
	movl %eax,poz
	movl x,%eax
	
	cmp %edx,%eax
	jg st
	
	cmp %edx,%eax
	jl dr
	
	jmp exit

st:
	mov poz,%ebx
	add $1,%ebx
	jmp loop

dr:
	mov poz,%ecx
	sub $1,%ecx
	jmp loop
	
exit:
	pushl poz
	pushl $formatString
	call printf
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
	
exit2:
	mov $0,%eax
	sub $1,%eax
	mov %eax,poz
	
	pushl poz
	pushl $formatString
	call printf
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
