	.section ".rodata"
	.section ".bss"
	.section ".data"
	.section ".text"

	.global digit_counts
	! %i0 - unsigned long value
	! return int of number of digits base 10
digit_counts:
	save %sp, -176, %sp
	mov 1, %l0
.dc01:	udivx %i0, 10, %i0
	tst %i0
	bz .dc02
	nop
	ba .dc01
	inc %l0
.dc02:  mov %l0, %i0
	ret
	restore

