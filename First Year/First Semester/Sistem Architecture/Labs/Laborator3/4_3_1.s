.data
	n: .long 5
	v: .long 10,5,-3,10,2

.text
.globl main

main:
	mov $1,%edx
	lea v,%edi
	mov $0,%ecx
	
	movl (%edi,%ecx,4),%eax
	add $1,%ecx
	
loop:
	cmp n,%ecx
	je exit
	
	mov (%edi,%ecx,4),%ebx
	cmp %ebx,%eax
	jl interschimba
	
	cmp %ebx,%eax
	je egale
	
	add $1,%ecx
	jmp loop
	
egale:
	add $1,%edx
	add $1,%ecx
	jmp loop
	
interschimba:
	mov $1,%edx
	mov %ebx,%eax
	add $1,%ecx
	jmp loop
	
exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
