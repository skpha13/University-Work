.data
	x: .long 59
	l: .long 0
	lmax: .long 0
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

	mov $0,%eax
	mov %eax,l

	mov x,%ebx	
	shr $1,%ebx

	jmp loop
	
add:
	mov l,%eax
	add $1,%eax
	mov %eax,l
	
	add $1,%ecx
	mov x,%ebx
	shr $1,%ebx
	
	cmp lmax,%eax
	ja lungime
	
	jmp loop
	
lungime:
	mov %eax,lmax
	jmp loop

exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
