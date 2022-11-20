#long v[5] = {1,2,3,4,5}
#long n = 5
#long s = 0
#for (long i=0;i<n;i++)
# 	s += v[i];

.data
	v: .long 1,2,3,4,5
	n: .long 5
	s: .long 0
	
.text

.globl main

main:
	mov $v,%esi
	mov $0,%ecx
	
et_loop:
	cmp n,%ecx
	je et_exit
	
	mov (%esi,%ecx,4), %eax
	add %eax,s
	inc %ecx
	
	jmp et_loop
	
et_exit:
	mov $1,%eax
	xor %ebx,%ebx
	int $0x80	
