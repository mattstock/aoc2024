	.section ".rodata"

	.section ".bss"


	.section ".data"
	.align 4
teststr:	.asciz "col = %d, row = %d\n";

	.align 4
	.global cols
xmax:	
cols:	.skip 4
	.global rows
ymax:	
rows:	.skip 4

	.section ".text"

	! map holds the map of the antennas
	! paint holds the position of all of the antinodes
	! mapsize gives us the total size of the map, including
	! newlines.

	.global xoff
	! %i0 - start address
	! %i1 - end address
	! return xoffset
xoff:
	save %sp, -176, %sp
	sub %i1, %i0, %l0
	set cols, %l1
	ld [%l1], %l1
	inc %l1  ! for the newline
	! integer division is rows
	udivx %l0, %l1, %l2
	mulx %l2, %l1, %l3
	sub %l0, %l3, %l4
	! offset if the start address isn't the base of the map
	set map, %l5
	ldx [%l5], %l5
	cmp %l5, %i0
	be .xl01
	nop
	mov %i0, %o1
	mov %l5, %o0
	call xoff
	nop
	sub %o0, %l4, %l4
.xl01:	mov %l4, %i0
	ret
	restore

	.global yoff
	! %i0 - start address
	! %i1 - end address
	! return yoffset
yoff:
	save %sp, -176, %sp
	sub %i1, %i0, %l0
	set cols, %l1
	ld [%l1], %l1
	inc %l1  ! for the newline
	! integer division is rows
	udivx %l0, %l1, %l2
	
	! offset if the start address isn't the base of the map
	set map, %l5
	ldx [%l5], %l5
	cmp %l5, %i0
	be .yl01
	nop
	mov %i0, %o1
	mov %l5, %o0
	call yoff
	nop
	sub %o0, %l2, %l2
	
.yl01:	mov %l2, %i0
	ret
	restore
	
	! measure the map and initialize paint
cartographer:	
	save %sp, -176, %sp
	clr %l0
	clr %l6
	clr %l7
	set mapsize, %l1
	ld [%l1], %l1
	set map, %l2
	ldx [%l2], %l2
	set paint, %l3
	ldx [%l3], %l3
.l01:   cmp %l0, %l1
	beq .l02
	nop
	! init paint pos
	ldub [%l2], %l5
	stb %l5, [%l3]
	! check if newline
	cmp %l5, '\n'
	bne .l05
	nop
	! increment row count
	inc %l6
	stb %l5, [%l3]
	! have we set the col size yet?
	tst %l7
	bnz .l05
	nop
	mov %l0, %l7
.l05:	inc %l2
	inc %l3
	ba .l01
	inc %l0
.l02:   set cols, %l2
	st %l7, [%l2]
	set rows, %l2
	st %l6, [%l2]
	ret
	restore

	.global painter
	! %i0 - col offset
	! %i1 - row offset
	! %i2 - map index for the antenna
painter:
	save %sp, -176, %sp
	! get the absolute offset for the antenna

	set map, %l0
	ldx [%l0], %o0
	call xoff
	mov %i2, %o1

	! are we in bounds in x?
	add %o0, %i0, %l0  ! abs x

	set cols, %l1
	ld [%l1], %l1
	tst %l0
	bl .lp01
	nop

	cmp %l0, %l1
	bge .lp01
	nop

	! check bounds y
	set map, %l2
	ldx [%l2], %o0
	mov %i2, %o1
	call yoff
	nop
	
	add %o0, %i1, %l2 ! abs y

	set rows, %l4
	ld [%l4], %l4
	tst %l2
	bl .lp01
	nop
	
	cmp %l2, %l4
	bge .lp01
	nop

	! paint the target
	! paint + (roff*(cols+1)+coff)
	add %l1, 1, %l4    ! cols+1
	mulx %l2, %l4, %l5 ! roff * (cols+1)
	add %l0, %l5, %l5  ! roff * (cols+1) + coff)
	set paint, %l6
	ldx [%l6], %l6

	add %l5, %l6, %l6 
	mov '#', %l4
	stb %l4, [%l6]	
.lp01:	ret
	restore
	
	.global antiseek
antiseek:
	save %sp, -192, %sp
	! space for 4 words in local stack
	
	call cartographer
	nop

	! %l0 - index to find the first tower
	! %l1 - index to find the matching towers
	! %l2 - index for end of map
	! %l3 - first tower value
	! we seek linearly until we hit a tower on %l0, and then continue using
	! %l1 until we find all of the matching towers.  For each match,
	! we get the distance and see if the anti is within the bounds and
	! mark paint.
	set map, %l0
	ldx [%l0], %l0
	set mapsize, %l2
	ld [%l2], %l2
	add %l2, %l0, %l2
.al01:	cmp %l2, %l0
	beq .done
	ldub [%l0], %l3
	cmp %l3, '\n'
	beq .al03
	nop
	cmp %l3, '.'
	beq .al03
	nop
	! got a tower
	mov %l0, %l1
.al02:  inc %l1  ! go to the next pos after the first tower
	cmp %l2, %l1
	beq .al03
	nop
	ldub [%l1], %l4

	cmp %l4, %l3
	bne .al02
	nop

	! got a match


	! need to get the coordinates for the offsets
	set map, %l7
	ldx [%l7], %o0
	call xoff
	mov %l0, %o1
	mov %o0, %l5 ! a x offset

	set map, %l7
	ldx [%l7], %o0
	call xoff
	mov %l1, %o1 ! b x offset
	
	sub %o0, %l5, %l5 ! b-a x offset
	
	set map, %l7
	ldx [%l7], %o0
	call yoff
	mov %l0, %o1 ! a y offset
	mov %o0, %l6 

	set map, %l7
	ldx [%l7], %o0
	call yoff
	mov %l1, %o1 ! b y offset

	sub %o0, %l6, %l6 ! b-a y offset
	
	! subtract them for the first antenna
	! add them for the second antenna
	! paint the position if it's valid
	mov %l5, %o0
	mov %l6, %o1
	call painter
	mov %l1, %o2

	mov %l0, %o2
	neg %o0
	call painter
	neg %o1

	
	ba .al02
	nop
.al03:  ba .al01
	inc %l0  ! sweet use of delay slot
	
.done:	ret
	restore
