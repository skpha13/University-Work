.data
	nr: .long 0
	n: .long 0
	v: .space 100
	aux: .long 0
	fs: .asciz "%ld"
	fs1: .asciz "%ld\n"

.text

perfect:
	pushl %ebp
	mov %esp,%ebp
	
	movl 8(%ebp),%eax
	mov $2,%ecx
	mov $0,%edx
	div %ecx
	mov $1,%ecx
	mov %eax,%ebx
	
	sub $4,%esp
	movl $0,-4(%ebp)
	
	loop:
		cmp %ebx,%ecx
		jg verif
		
		movl 8(%ebp),%eax
		mov $0,%edx		
		div %ecx
		cmp $0,%edx
		je adunare
				
		add $1,%ecx
		jmp loop
		
	adunare:
		add %ecx,-4(%ebp)
		
		add $1,%ecx
		jmp loop
	verif:
		mov 8(%ebp),%ebx
		cmp -4(%ebp),%ebx
		je return
		
		mov $0,%eax
		jmp iesire
	
	return:	
		mov $1,%eax
		jmp iesire
	
	iesire: 
		addl $4,%esp
		popl %ebp
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
	jmp loop_vector

loop_vector:
	cmp n,%ecx
	je afisare
	
	movl (%edi,%ecx,4),%edx
	
	pushl %ecx
	pushl %eax
	pushl %edx
	call perfect
	popl %ebx
	popl %ecx
	popl %ecx
	
	cmp $1,%eax
	je add
	
	add $1,%ecx
	jmp loop_vector
	
add:
	mov nr,%eax
	add $1,%eax
	mov %eax,nr
	add $1,%ecx
	jmp loop_vector
	
afisare:
	pushl nr
	pushl $fs1
	call printf
	popl %ebx
	popl %ebx
	
	jmp exit

exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
