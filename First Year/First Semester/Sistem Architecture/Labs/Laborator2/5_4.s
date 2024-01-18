.data
	x: .long 23
.text

.globl main

main:
	mov x,%eax
	mov $0,%ecx
	mov $2,%ebx
	jmp impartire

impartire:
	cmp $1,%eax
	je exit

	mov $0,%edx
	div %ebx
	
	add $1,%ecx
	
	jmp impartire
exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
