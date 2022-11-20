.data 
	n: .long 20
	d: .long 0
	prim: .asciz "Prim\n"
	nprim: .asciz "Nu e prim\n"
.text

.globl main

main:
	mov $1,%ecx
	
loop:
	cmp n,%ecx
	ja test
	
	mov $0,%edx
	
	mov n,%eax
	mov %ecx,%ebx
	div %ebx
	
	cmp $0,%edx
	je adauga
	
next:
	add $1,%ecx
	jmp loop
	
adauga:
	mov d,%eax
	add $1,%eax
	mov %eax,d
	jmp next
	
pr:
	mov $4,%eax
	mov $1,%ebx
	mov $prim,%ecx
	mov $6,%edx
	int $0x80
	
	jmp exit
	
npr:
	mov $4,%eax
	mov $1,%ebx
	mov $nprim,%ecx
	mov $11,%edx
	int $0x80
	
	jmp exit
	
test:
	mov d,%eax
	cmp $2,%eax
	je pr
	
	jmp npr
	
exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
