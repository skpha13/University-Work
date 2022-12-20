.data
	n1: .long 5
	n2: .long 6
	k: .long 3
	fs: .asciz "%ld\n"	
.text

rest:
	pushl %ebp
	mov %esp,%ebp
	
	pushl %ebx
	
	mov 8(%ebp), %eax
	mov 12(%ebp), %ebx
	mov $0,%edx
	div %ebx
	
	#intoarce in %eax catul
	#intoarce in %edx restul
	
	mov %edx,%eax
	
	pop %ebx
	pop %ebp
	ret

proc:
	pushl %ebp
	mov %esp,%ebp
	
	sub $4,%esp
	
	mov 8(%ebp), %eax
	add 12(%ebp), %eax
	
	mov %eax,-4(%ebp)
	
	pushl 16(%ebp)
	pushl -4(%ebp)
	call rest
	addl $8, %esp
	#rest intoarce rezultatul in %eax
	
	addl $4,%esp
	pop %ebp
	ret

.global main

main:
	pushl k
	pushl n2
	pushl n1
	call proc
	#pop %ebx
	#pop %ebx
	#pop %ebx
	addl $12,%esp
	
	
	push %eax
	pushl $fs
	call printf
	#pop %ebx
	#pop %ebx
	addl $8,%esp
	
exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80
	
#in loc de pop-uri se poate adauga in %esp nr_pop-uri * 4
