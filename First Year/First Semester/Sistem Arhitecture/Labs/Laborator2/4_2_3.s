.data
	a: .long 15
	b: .long 3
	c: .long 29	
	min: .space 4
.text

.globl main

main:
	mov a,%eax
	mov b,%ebx
	cmp %ebx,%eax
	jb second_test
	
	mov b,%eax
	mov c,%ebx
	cmp %eax,%ebx
	jb third_test
	
	mov %eax,min
		
	jmp exit
	
second_test:
	mov a,%eax
	mov c,%ebx
	cmp %eax,%ebx
	jb third_test
	mov %eax,min
	jmp exit
	
third_test:
	mov %ebx,min
	jmp exit
	
exit:
	mov $1,%eax
	mov $0,%ebx
	int $0x80
