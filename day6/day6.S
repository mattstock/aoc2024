	.section ".rodata"

	.section ".bss"
cols:	.skip 4
	.global rows
rows:	.skip 4
	.global pos
pos:	.skip 4
	
	.section ".data"
	
	.section ".text"

	! search for the first newline to figure out how many columns and
	! rows there are
	! %l0 - current index
	! %l1 - current byte address in map
	! %l2 - current map byte
	! %l3 - current rows value
findbits:
	save %sp, -96, %sp
	clr %l0
	clr %l3
.l01:	add %l0, %g2, %l1
	ldub [%l1], %l2
	cmp %l2, '\n'
	bne .l04
	nop
	tst %l3
	bnz .l02	
	nop
	set cols, %l4
	st %l0, [%l4]
.l02:	inc %l3
	ba .l03
	nop
.l04:	cmp %l2, '^'
	bne .l05
	nop
	set pos, %l4
	st %l0, [%l4]
	ba .l03
	nop
.l05:	tst %l2 ! null
	be .l06
	nop
.l03:	inc %l0
	ba .l01
	nop
.l06:	set rows, %l4
	st %l3, [%l4]
	ret
	restore

	! determine offset of next step
	! %i0 = position index
	! %i1 = cols
	! %i2 = rows
	! up = -cols+1
	! down = cols+1
	! left = -1
	! right = 1
calcoff:	
	! evaluate a direction,
	! choose offset in array based on the symbol at the pos location
	! %l0 - pos index
	! %l1 - map offset
	! %l2 - pos char
	! %l3 - cols
	.global checkstep
checkstep:
	save %sp, -96, %sp
	set pos, %l0
	ld [%l0], %l0
	add %l0, %g2, %l1
	ld [%l1], %l2
	set cols, %l3
	ld [%l3], %l3

	cmp %l2, '^'
	bne .cl0
	nop
	! new map position
	sub %l1, %l3, %l4
	dec %l4
	! new pos index
	sub %l0, %l3, %l5
	dec %l5
	
.cl0:
	cmp %l2, 'v'
	bne .cl1
	nop

.cl1:
	cmp %l2, '>'
	bne .cl2
	nop
	
.cl2:
	dec %l0
	
	
	ret
	restore

	! main calling function
	.align 4
	.global guard
guard:
	save %sp, -96, %sp
	! Set %g2 to hold the map pointer
	set map, %l0
	ld [%l0], %g2
	! determine the size of the grid and the current position
	call findbits
	nop

	clr %l2
.step01:	
	! action the next step
	call checkstep
	nop
	tst %o0
	bz .step01
	inc %l2

	mov %l2, %i0
	! put the number of steps in %i0 to return
	ret
	restore
	
