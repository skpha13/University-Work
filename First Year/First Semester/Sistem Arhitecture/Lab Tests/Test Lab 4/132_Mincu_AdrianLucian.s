.data
	s: .space 201
	fs: .asciz "%s"
	fs2: .asciz "%s\n"

.text
.globl main

main:
	lea s,%edi
	mov $0,%ecx

citire:
	pusha
	pushl $s
	pushl $fs
	call scanf
	popl %ebx
	popl %ebx
	popa
loop:
	movb (%edi,%ecx,1),%bl
	cmp $0,%bl
	je afisare
	
	cmp $'z',%bl
	je caz_special
	
	add  $1,%bl
	movb %bl,(%edi,%ecx,1)
	
	add $1,%ecx
	jmp loop

caz_special:
	movb $'a',%bl
	movb %bl,(%edi,%ecx,1)
	add $1,%ecx
	jmp loop
	
afisare:
	pushl $s
	pushl $fs2
	call printf
	popl %ebx
	popl %ebx
	
	jmp exit

exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
