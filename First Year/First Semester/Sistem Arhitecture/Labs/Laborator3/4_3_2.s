.data 
	n: .long 11
	s: .asciz "dafafdadfa\n"
	t: .space 11

.text
.globl main

main:
	mov n,%eax
	sub 1,%eax
	mov %eax,n
	lea s,%edi
	mov n,%ecx
	
loop:
	cmp $0,%ecx
	jb afisare
	
	mov n,%eax
	sub %ecx,%eax
	
	movb (%edi,%ecx,1), %ebx
	movb %ebx,t(,%eax,1)
			
	sub $1,%ecx
	jmp loop
	
afisare:
	mov $4,%eax
	mov $1,%ebx
	mov $t,%ecx
	mov $11,%edx
	int $0x80
	
exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
