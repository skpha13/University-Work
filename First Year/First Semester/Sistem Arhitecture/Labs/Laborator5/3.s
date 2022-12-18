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
	movl $0,12(%ebp)
	movl $0,%eax
	
	sub $4,%esp
	
	lea 8(%ebp),%edi
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
		
		movl $-1,%eax
		jmp iesire2
		
		add $1,%ecx
		jmp loop
		
	cond1:
		cmp $'9',%dl
		jle cond2
		
		movl $-1,%eax
		jmp iesire2
	
	cond2:
		mov $10,%ebx
		mul %ebx
		movb (%edi,%ecx,1),%dl
		sub $'0',%dl
		add %edx,%eax
		
		add $1,%ecx
		jmp loop
		
	iesire:	
		movl -4(%ebp),%ebx 
		cmp $1,%ebx
		je semn
		
	iesire2:	
		add $4,%esp
		popl %ebp
		ret
	
	semn:
		movl $-1,%ebx
		imul %ebx
		jmp iesire2

.globl main

main:
	pushl $s
	pushl $fs
	call scanf
	popl %ebx
	popl %ebx
	
	pushl %eax
	pushl s
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
