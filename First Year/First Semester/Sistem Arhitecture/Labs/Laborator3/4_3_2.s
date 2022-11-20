.data 
	n: .long 10
	s: .asciz "dafafdadfa\n"
	t: .space 11

.text
.globl main

main:
	mov n,%eax
	sub $1,%eax
	mov %eax,n
	lea s,%edi
	mov n,%ecx
	
loop:
	cmp $0,%ecx
	jl afisare
	
	mov n,%eax
	sub %ecx,%eax
	
	movb (%edi,%ecx,1), %bl
	movb %bl,t(,%eax,1)
			
	sub $1,%ecx
	jmp loop
	
afisare:
	mov n,%eax
	add $1,%eax
	movb (%edi,%eax,1),%bl
	movb %bl,t(,%eax,1)
	mov $4,%eax
	mov $1,%ebx
	mov $t,%ecx
	mov $11,%edx
	int $0x80
	
exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
