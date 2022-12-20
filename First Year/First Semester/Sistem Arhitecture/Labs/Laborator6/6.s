.data
	x: .long 4
	fs1: .asciz "\n"
	fs2: .asciz "%ld "
	
.text
	
proc:
	push %ebp
	mov %esp,%ebp
	
	pushl 8(%ebp)
	pushl $fs2
	call printf
	add $8,%esp
	
	cmpl $0, 8(%ebp)
	je salt
	
	mov 8(%ebp), %eax
	dec %eax
	
	push %eax
	call proc
	add $4,%esp
	
	salt:
		pop %ebp
		ret

.global main

main:
	pushl x
	call proc
	addl $4,%esp
	
	pushl $fs1
	call printf

exit:
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80
