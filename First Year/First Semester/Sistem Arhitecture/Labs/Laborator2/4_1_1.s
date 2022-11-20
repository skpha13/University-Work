.data

.text

.globl main

main:
	mov $15,%eax
	mov $3,%ebx
	
	xor %ebx,%eax
	xor %eax,%ebx
	xor %ebx,%eax
	
exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
