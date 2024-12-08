	.section ".rodata"
	.section ".bss"
	.section ".data"
	.section ".text"

	! %i0 - left side
	! %i1 - right side
	.global glue
glue:
	save %sp, -176, %sp
	! find the number of digits in %i1
	clr %l0
	mov %i1, %l1
.l0:	udivx %l1, 10, %l1
	mulx %i0, 10, %i0
	tst %l1
	bnz .l0
	nop
	add %i0, %i1, %i0
	ret
	restore
	
	! %i0 - goal total
	! %i1 - total so far
	! %i2 - number of values
	! %i3 - pointer to value list
	.global consider
consider:
	save %sp, -176, %sp

	! base case
	tst %i2
	bne .recurse
	nop
	cmp %i0, %i1
	bne .fail
	nop
.suc:   mov 1, %i0
	ba .done
	nop
.fail:  clr %i0
	ba .done
	nop
.recurse:	
	! try add
	ld [%i3], %l0
	add %i1, %l0, %o1
	mov %i0, %o0
	sub %i2, 1, %o2
	add %i3, 4, %o3
	call consider
	nop
	tst %o0
	bne .suc
	nop

	! try mul
	ld [%i3], %l0
	mulx %i1, %l0, %o1
	mov %i0, %o0
	sub %i2, 1, %o2
	add %i3, 4, %o3
	call consider
	nop
	tst %o0
	bne .suc
	nop

	! try concat
	ld [%i3], %o0
	mov %i1, %o1
	call glue
	nop
	mov %o0, %o1
	mov %i0, %o0
	sub %i2, 1, %o2
	add %i3, 4, %o3
	call consider
	nop
	tst %o0
	bne .suc
	nop
	
	ba .fail
	nop
.done:	ret
	restore
