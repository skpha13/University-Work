.data
	x: .long 32
	y: .long 2
.text

.globl main

main:
	mov $16,%eax
	mov y,%ebx
	imul %ebx
	mov %eax,y
	
	mov x,%eax
	mov $16,%ebx
	idiv %ebx
	mov %eax,x
	
	mov $0,%eax
	mov x,%eax
	add y,%eax
	jmp exit
exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
