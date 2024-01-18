#char s[7] = "Hello\";
#char t[7];
#long n = 7;
#for (i=0;i<n;i++)
#	t[i] = s[i];

#for (i=n;i>=1;i--)
#	t[i-1] = s[i-1];

.data
	n: .long 7
	s: .asciz "Hello\n"
	t: .space 7

.text

.globl main

main:
	mov $t,%edi
	mov $s,%esi
	mov n,%ecx
	
et_loop:
	mov %ecx,%edx
	dec %edx
	mov (%esi,%edx,1), %bl
	mov %bl, (%edi,%edx,1)
	loop et_loop	

mov $4,%eax
mov $1,%ebx
mov $t,%ecx
mov $7,%edx
int $0x80

mov $1,%eax
xor %ebx,%ebx
int $0x80
