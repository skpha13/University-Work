.data
	s: .space 100
	fs2: .asciz "%s"
	fs: .asciz "Numar Vocale: %ld\n"
	x: .long 0
.text
.globl main

main:
	mov $0,%ecx
	mov $0,%eax

citire:
	pusha
	pushl $s
	pushl $fs2
	call scanf
	popl %ebx
	popl %ebx
	popa
loop:
	lea s,%edi
	movb (%edi,%ecx,1),%dl
	cmp $0,%dl
	je afisare
	
	cmp $'a',%dl
	je add
	
	cmp $'e',%dl
	je add
	
	cmp $'i',%dl
	je add
	
	cmp $'o',%dl
	je add
	
	cmp $'u',%dl
	je add
	
	add $1,%ecx
	jmp loop
	
add:
	add $1,%eax
	add $1,%ecx
	jmp loop
	
afisare:
	mov %eax,x
	pushl x
	pushl $fs
	call printf
	popl %ebx
	popl %ebx
	
	jmp exit
	
exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
