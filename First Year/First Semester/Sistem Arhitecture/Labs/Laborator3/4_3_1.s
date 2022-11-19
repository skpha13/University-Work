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
	
loop:
	cmp n,%ecx
	je exit
	
	movl (%edi,%ecx,4),%ebx
	cmp %ebx,%eax
	jl swap
			
	add $1,%ecx
	jmp loop

swap:
	mov %ebx,%eax
	add $1,%ecx
	jmp loop
	
exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
