.data
	x: .long 9
	copie: .long 0
	palindrom: .asciz "palindrom\n"
	npalindrom: .asciz "nu e palindrom\n"
.text

.globl main

main:
	mov x,%ebx
	mov %ebx,copie
	mov $0,%eax
	
loop:
	cmp $0,%ebx
	je verifica
	
	shl $1,%eax
	mov %ebx,x
	and $1,%ebx
	cmp $1,%ebx
	je schimba

	mov x,%ebx	
	shr $1,%ebx

	jmp loop
	
schimba:
	xor $1,%eax
	mov x,%ebx
	shr $1,%ebx
	jmp loop

verifica:
	mov copie,%ebx
	cmp %ebx,%eax
	je afis1
	
	jmp afis2

afis1:
	mov $4,%eax
	mov $1,%ebx
	mov $palindrom,%ecx
	mov $11,%edx
	int $0x80
	jmp exit

afis2:
	mov $4,%eax
	mov $1,%ebx
	mov $npalindrom,%ecx
	mov $16,%edx
	int $0x80
	jmp exit

exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
