.data
.text
.globl main
main:
	movl $0, %eax
	mov $1, %al
	
	mov $1, %eax
	mov $0, %ebx
	int $0x80
