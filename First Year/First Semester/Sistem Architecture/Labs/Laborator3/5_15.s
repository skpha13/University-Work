.data 
	n: .long 7
	v: .long 1245,342,543523, 342, 4234, 1245, 543523
.text
.globl main

main:
	lea v,%edi
	mov $0,%ecx
	movl (%edi,%ecx,4),%eax
	mov $1,%ecx
	
loop:
	cmp n,%ecx
	je exit
	
	movl (%edi,%ecx,4),%ebx
	xor %ebx,%eax
			
	add $1,%ecx
	jmp loop

exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
