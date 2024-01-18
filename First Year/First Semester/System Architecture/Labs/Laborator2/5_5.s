.data
	x: .long 23
.text

.globl main

main:
	mov x,%ebx
	mov $0,%ecx
	
loop:
	cmp $0,%ebx
	je exit
	
	mov %ebx,x
	and $1,%ebx
	cmp $1,%ebx
	je add

	mov x,%ebx	
	shr $1,%ebx

	jmp loop
	
add:
	add $1,%ecx
	mov x,%ebx
	shr $1,%ebx
	jmp loop

exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
