.data 
	n: .long 7
	v: .long 5,23,1,654,3,0,-21
.text
.globl main

main:
	lea v,%edi
	mov $0,%ecx
	movl (%edi,%ecx,4),%eax
	mov $1,%ecx
	movl (%edi,%ecx,4),%ebx
	mov $2,%ecx
	
	cmp %ebx,%eax
	jg schimba
	
loop:
	cmp n,%ecx
	je exit
	
	movl (%edi,%ecx,4),%edx
	
	cmp %edx,%ebx
	jg swap
	
	cmp %edx,%eax
	jg swap2
			
	add $1,%ecx
	jmp loop

swap:
	mov %ebx,%eax
	mov %edx,%ebx
	add $1,%ecx
	jmp loop
	
swap2:
	mov %edx,%eax
	add $1,%ecx
	jmp loop

schimba:
	xor %ebx,%eax
	xor %eax,%ebx
	xor %ebx,%eax
	
exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
