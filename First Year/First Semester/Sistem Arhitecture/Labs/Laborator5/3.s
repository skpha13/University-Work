.data
	s: .space 100
	fs: .asciz "%s"
	fs1: .asciz "%ld\n"
	aux: .long 0
	
.text

atoi:
	pushl %ebp
	mov %esp,%ebp
	
	movl $0,%ecx
	lea 8(%ebp),%edi
	movl $0,12(%ebp) 
	
	sub $4,%esp
	
	movb (%edi,%ecx,1),%dl
	cmp $'-',%dl
	je intreg
	
	jmp loop
	
	intreg:
		movl $1,-4(%ebp)
		add $1,%ecx
		
	loop:
		movb (%edi,%ecx,1),%dl
		cmp $0,%dl
		je iesire
		
		cmp $'0',%dl
		jge cond1
		
		add $1,%ecx
		jmp loop
		
	cond1:
		cmp $'9',%dl
		jle cond2
	
	cond2:
		mov $10,%ebx
		mul %ebx
		sub %dl,'0'
		
		add %dl,%eax
		add $1,%ecx
		jmp loop
		
	iesire:	
		add $4,%esp
		popl %ebp
		ret
		


.globl main

main:
	pushl $s
	pushl $fs
	call scanf
	popl %ebx
	popl %ebx
	
	movl $-1,%eax
	pushl %eax
	pushl $s
	call atoi
	popl %ebx
	
	pushl %eax
	pushl $fs1
	call printf
	popl %ebx
	popl %ebx

exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
