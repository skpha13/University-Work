.data 
	n: .long 6
	v: .long 5,23,1,654,3,0
.text
.globl main

main:
	lea v,%edi
	mov $0,%ecx
	mov $0,%ebx
	mov n,%eax
	sub $1,%eax
	mov %eax,n
	
loop:
	cmp n,%ecx
	je calcul
	
	add (%edi,%ecx,4),%ebx
			
	add $1,%ecx
	jmp loop

calcul:
	mov $0,%edx
	mov %ebx,%eax
	mov n,%ebx
	div %ebx
	jmp exit

exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
