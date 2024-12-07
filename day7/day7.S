	.section ".rodata"
	.section ".bss"
	.section ".data"
	.section ".text"

	! %i0 - goal total
	! %i1 - total so far
	! %i2 - number of values
	! %i3 - pointer to value list
	.global consider
consider:
	save %sp, -96, %sp

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
	mov %i0, %o0
	umul %i1, %l0, %o1
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

