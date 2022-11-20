.data
	x: .long 256
	y: .long 1
	str1: .asciz "pass\n"
	str2: .asciz "fail\n"
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
	
	mov x,%eax
	mov y,%ebx
	cmp %ebx,%eax
	je pass
	
	jmp fail
	
pass:
	mov $4,%eax
	mov $1,%ebx
	mov $str1,%ecx
	mov $6,%edx
	int $0x80
	jmp exit
	
fail:
	mov $4,%eax
	mov $1,%ebx
	mov $str2,%ecx
	mov $6,%edx
	int $0x80
	jmp exit
	
exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
