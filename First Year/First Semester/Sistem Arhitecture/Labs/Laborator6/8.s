.data
	x: .long 0
	fs: .asciz "%ld"
	fs1: .asciz "%ld\n"

.text

factorial:
	push %ebp
	mov %esp,%ebp
	
	cmpl $0,8(%ebp)
	jbe caz_special
	
	cmpl $1,8(%ebp)
	je salt
	
	mull 8(%ebp)
	decl 8(%ebp)
	
	pushl 8(%ebp)
	call factorial
	addl $4,%esp
	
	salt:
		pop %ebp
		ret
		
	caz_special:
		mov $1,%eax
		pop %ebp
		ret

.global main

main:
	pushl $x
	pushl $fs
	call scanf
	addl $8, %esp
	
	mov $1,%eax
	pushl x
	call factorial
	addl $4, %esp
	
	pushl %eax
	pushl $fs1
	call printf
	addl $8, %esp
	
exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
