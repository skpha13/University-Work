.data
	x: .long 0
	poz: .asciz "Pozitiv\n"
	neg: .asciz "Negativ\n"
	z: .asciz "Zero\n"
	
.text
.globl main

main:
	mov $15,%eax
	cmp x,%eax
	js negativ
	ja pozitiv
	
	jmp zero


pozitiv:
	mov $4,%eax
	mov $1,%ebx
	mov $poz,%ecx
	mov $9,%edx
	int $0x80
	jmp exit

negativ:
	mov $4,%eax
	mov $1,%ebx
	mov $neg,%ecx
	mov $9,%edx
	int $0x80
	jmp exit

zero:
	mov $4,%eax
	mov $1,%ebx
	mov $z,%ecx
	mov $9,%edx
	int $0x80
	jmp exit

exit:
	mov $1, %eax
	mov $0, %ebx
	int $0x80
