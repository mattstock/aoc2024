	.section ".rodata"

foo:	.asciz "ABCDEF\n"
	
	.section ".text"

	.align 4
	.global main
main:
	save %sp, -96, %sp
	set foo, %o0
	call printf
	nop
	mov 0, %i0
	ret
	restore
	
