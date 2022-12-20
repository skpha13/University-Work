.data
	x: .long 0
	fs: .asciz "%ld"
	fs1: .asciz "%ld\n"
.text

f:
	push %ebp
	mov %esp,%ebp
	push %ebx
	
	pushl 8(%ebp)
	call g
	addl $4,%esp
	
	movl $2,%ebx
	imul %ebx
	
	pop %ebx
	pop %ebp
	ret
	
g:
	push %ebp
	mov %esp,%ebp
	
	addl $1,8(%ebp)
	movl 8(%ebp),%eax
	
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
	call f
	addl $4, %esp
	
	pushl %eax
	pushl $fs1
	call printf
	addl $8, %esp
exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
