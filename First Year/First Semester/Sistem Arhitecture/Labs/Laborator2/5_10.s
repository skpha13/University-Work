.data
.text
.globl main
main:
	mov $0,%eax
	mov $14,%al
	mov $9,%ah
	
	mov $1,%eax
	mov $0,%ebx
	int $0x80
